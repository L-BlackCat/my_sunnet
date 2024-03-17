
#include<iostream>
#include "MySunnet.h"
#include <sys/epoll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>


MySunnet* MySunnet::inst;

MySunnet::MySunnet(){
    inst = this;
}

void MySunnet::Start(){
    cout<< "Hello MySunnet"<< endl;

    pthread_rwlock_init(&serviceMapLock,NULL);
    pthread_spin_init(&globalQLock,PTHREAD_PROCESS_PRIVATE);
    pthread_rwlock_init(&connLock,NULL);

    startSocketWorker();
    startWroker();
    
}


void MySunnet::Wait(){
    if(my_worker_threads[0]){
        my_worker_threads[0]->join();
    }
}


void MySunnet::startWroker(){
    for (int i = 0; i < WORKER_NUM; i++)
    {
        cout << "start worker thread："<<i<<endl;
        Worker* worker = new Worker();
        worker->worker_id = i;
        worker->each_num = 2 << i;
        my_workers.push_back(worker);
        thread* workerThread = new thread(*worker);
        my_worker_threads.push_back(workerThread);
    }
}



uint32_t MySunnet::NewService(shared_ptr<string> type){
    auto service = make_shared<Service>();
    service->type = type;
    pthread_rwlock_wrlock(&serviceMapLock);
    {
        service->id = max_service_id;
        max_service_id++;
        serviceMap.emplace(service->id,service);
    }
    pthread_rwlock_unlock(&serviceMapLock);
    service->OnInit();
    return service->id;
}

shared_ptr<Service> MySunnet::GetService(uint32_t id){
    shared_ptr<Service> service = NULL;
    pthread_rwlock_wrlock(&serviceMapLock); 
    {
        if(!serviceMap.empty()){
            unordered_map<uint32_t,shared_ptr<Service>>::iterator iter = serviceMap.find(id);
            if(iter != serviceMap.end()){
                service = iter->second;
            }
        }
    }
    pthread_rwlock_unlock(&serviceMapLock);
    return service;
}

void MySunnet::KillService(uint32_t id){
    shared_ptr<Service> service = GetService(id);
    if(!service){
        return;
    }
    service->OnExit();
    //  为避免删除服务的时候，另一个服务向此服务发送消息，插入到消息队列中，需要设置一个标志，表示当前服务已经关闭
    service->isExiting = true;
    pthread_rwlock_wrlock(&serviceMapLock); 
    {
        if(!serviceMap.empty()){
            serviceMap.erase(id);
        }
    }
    pthread_rwlock_unlock(&serviceMapLock);

}


void MySunnet::PushGlobalService(shared_ptr<Service> service){
    pthread_spin_lock(&globalQLock);
    {
        globalQueue.push(service);
        globalLen++;
    }
    pthread_spin_unlock(&globalQLock);
}

shared_ptr<Service> MySunnet::PopGlobalService(){
    shared_ptr<Service> ret = NULL;
    pthread_spin_lock(&globalQLock);
    {
        if(!globalQueue.empty()){
            ret = globalQueue.front();
            globalQueue.pop();
            globalLen--;
        }
    }
    pthread_spin_unlock(&globalQLock);
    return ret;
}


shared_ptr<BaseMsg> MySunnet::MakeMsg(uint32_t source,char* buff,int len){
    auto msg = make_shared<ServiceMsg>();
    msg->type = BaseMsg::TYPE::SERVICE_MSG;
    msg->source = source;
    msg->buff = shared_ptr<char>(buff);
    msg->size = len;

    return msg;
}


void MySunnet::send(uint32_t toSid,shared_ptr<BaseMsg> msg){
    shared_ptr<Service> toService = MySunnet::inst->GetService(toSid);
    if(!toService){
        cout << "send fail,toSrv not exist toId:"<<toSid<<endl;
        return;
    }
    toService->pushMsg(msg);
    bool hasPush = false;

    //  检查并放入全局队列
    pthread_spin_lock(&toService->inGlobalLock);
    {
        if(!toService->inGlobal){
            MySunnet::inst->PushGlobalService(toService);
            toService->inGlobal = true;
            hasPush = true;
        }
    }
    pthread_spin_unlock(&toService->inGlobalLock);

    if(hasPush){
        CheckAndWake();
    }
}


void MySunnet::CheckAndWake(){
    /**
     * 这里没有上锁
     * 严格来说，多少线程同时访问sleepcount的时候，需要对sleepCount进行加锁保障安全
     * 但是由于插入服务是一个频繁的操作，给sleepCount上锁的话，与不上锁造成的影响相对比  ——>不上锁的代价更小
     * 不上锁会导致，sleepCount的数大了或者小了，不过无伤大雅。
     * 大的话，会在不该唤醒时唤醒->就当线程空转一次，小的话会在需要唤醒的时候没有唤醒-》等待下一次唤醒即可
     * 
    */
    if(sleepCount == 0){
        return;
    }
    if(WORKER_NUM - sleepCount <= globalLen){
        cout<<"wake"<<endl;
        pthread_cond_signal(&sleepCond);
    }

}


void MySunnet::startSocketWorker(){
    my_socket_worker = new SocketWorker();
    my_socket_worker->onInit();

    my_socket_worker_thread = new thread(*my_socket_worker);
}


void MySunnet::AddConn(int fd,uint32_t service_id,uint8_t type){
    pthread_rwlock_wrlock(&connLock);
    {
        auto conn = make_shared<Conn>();
        conn->type = type;
        conn->fd = fd;
        conn->service_id = service_id;
        conns.emplace(fd,conn);
    }
    pthread_rwlock_unlock(&connLock);
}


void MySunnet::RemoveConn(int fd){
    if(conns.empty()){
        return;
    }
    pthread_rwlock_rdlock(&connLock);
    {
        conns.erase(fd);
    }
    pthread_rwlock_unlock(&connLock);
}


shared_ptr<Conn> MySunnet::getConn(int fd){
    shared_ptr<Conn> ret = NULL;
    pthread_rwlock_rdlock(&connLock);
    {
        if(!conns.empty()){
            unordered_map<int,shared_ptr<Conn>>::iterator iter = conns.find(fd);
            if(iter != conns.end()){
                ret = iter->second;
            }
        }
    }
    pthread_rwlock_unlock(&connLock);
    return ret;
}


int MySunnet::Listen(int port,uint32_t service_id){
    //  创建套接字
    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if(listen_fd <= 0){
        cout << "listen err,listen_fd:"<<listen_fd<<endl;
        return -1;
    }
    //  设置非阻塞
    fcntl(listen_fd,F_SETFL,O_NONBLOCK);
    //  配置套接字的网络和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // addr.sin_addr.s_addr = inet_addr("47.103.195.188");

    int r = bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));

    if(r == -1){
        cout << "listen error,bind fail"<<endl;
        return -1;
    }
    
    r = listen(listen_fd,64);
    if(r < 0){
        return -1;
    }

    //  添加自定义Socket
    AddConn(listen_fd,service_id,Conn::MY_CONN_TYPE::listen);

    //  添加事件到epoll
    my_socket_worker->addEvent(listen_fd);

    return listen_fd;
}   



void MySunnet::CloseConn(int fd){
    //  删除自定义写缓存区
    RemoveConnWriteObj(fd);

    //  删除自定义socket
    RemoveConn(fd);

    close(fd);

    //  删除epoll中的时间监听
    my_socket_worker->removeEvent(fd);
}


void MySunnet::AddConnWriteObj(int fd){
    auto m = make_shared<ConnWriter>();
    m->fd = fd;
    pthread_rwlock_wrlock(&connWriterLock);
    {
        connWriterMap.emplace(fd,m);
    }
    pthread_rwlock_unlock(&connWriterLock);
}

void MySunnet::RemoveConnWriteObj(int fd){
    cout << "remove conn write obj ,fd:"<<fd<<endl;
    pthread_rwlock_wrlock(&connWriterLock);
    {
        connWriterMap.erase(fd);
    }
    pthread_rwlock_unlock(&connWriterLock);
}
        
shared_ptr<ConnWriter> MySunnet::GetConnWriteObj(int fd){ 
    return connWriterMap[fd];
}

void MySunnet::ModifyEvent(int fd,bool out){
    my_socket_worker->modifyEvent(fd,out);
}
