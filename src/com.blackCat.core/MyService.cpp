#include "MyService.h"
#include <iostream>

#include "MySunnet.h"

#include <unistd.h>
#include <errno.h>
#include <string.h>

// class MySunnet;

MyService::MyService(){
    //  初始化锁
    pthread_spin_init(&queueLock,PTHREAD_PROCESS_PRIVATE);
    pthread_spin_init(&inGlobalLock,PTHREAD_PROCESS_PRIVATE);
}

MyService::~MyService(){
    //  删除锁
    pthread_spin_destroy(&queueLock);
    pthread_spin_destroy(&inGlobalLock);
}


void MyService::OnInit(){
    cout << '[' << *type << "-" << id << "] OnInit()" << endl;
    
    MySunnet::inst->Listen(8888,id);
}


void MyService::OnMsg(shared_ptr<MyBaseMsg> msg){
    if(msg->type == MyBaseMsg::TYPE::SERVICE_MSG){
        auto m = dynamic_pointer_cast<MyServiceMsg>(msg);
        OnServiceMsg(m);
    }else if(msg->type == MyBaseMsg::TYPE::SOCKER_ACCEPT){
        auto m = dynamic_pointer_cast<MySocketAcceptMsg>(msg);
        OnAcceptMsg(m);
    }else if(msg->type == MyBaseMsg::TYPE::SOCKER_RW){

        auto m = dynamic_pointer_cast<MySocketRWMsg>(msg);
        int fd = m->fd;
        if(m->isReadable){
            const int BUFF_SIZE = 1024;
            char buff[BUFF_SIZE];
            int len;
            /**
             * 1.   可读-》读取成功-》可写
             * 2.   可读-》读取失败-》可写
             * 3.   可读-》读取成功
             * 4.   可读-》可写
             * 5.   可读-》读取失败
            */
            do{
                len = read(fd,&buff,BUFF_SIZE);
                if(len > 0){
                    OnSocketData(fd,buff,len);
                }
            }while(len == BUFF_SIZE);

            /**
             * 假设收到4条指令，在第2条指令的时候，关闭了conn，后面两条read会失败，再次触发OnSocketEroor
             * 这不是我们想看到的结果->我们希望关闭后不在重复执行关闭操作
             * 解决思路：在关闭时，进行一次conn检测 （会多一次读锁的消耗）
             * 
            */
            if(len <= 0 && errno != EAGAIN){
                if(MySunnet::inst->getConn(fd)){
                    //  报错
                    OnSocketClose(fd);
                }
            }
        }

        if(m->isWritable){
            if(MySunnet::inst->getConn(fd)){
                OnSocketWritable(fd);
            }
        }
    }else{
        cout << '[' << *type << "-" << id << "] OnMsg()" << endl; 
    }
}


void MyService::OnExit(){
    cout << '[' << *type << "-" << id << "] OnExit()" << endl; 
}

void MyService::pushMsg(shared_ptr<MyBaseMsg> msg){
    pthread_spin_lock(&queueLock);
    {
        msgQueue.push(msg);
    }
    pthread_spin_unlock(&queueLock);
}


bool MyService::processMsg(){
    shared_ptr<MyBaseMsg> ret = popMsg();
    if(ret){
        OnMsg(ret);
        return true;
    }
    return false;
}

bool MyService::processMsgs(int num){
    for (int i = 0; i < num; i++)
    {
        /* code */
        bool succ = processMsg();
        if(!succ){
            return false;
        }
    }
    return true;
}

shared_ptr<MyBaseMsg> MyService::popMsg(){
    shared_ptr<MyBaseMsg> ret = NULL;
    pthread_spin_lock(&queueLock);
    {
        if(!msgQueue.empty()){
            ret = msgQueue.front();
            msgQueue.pop();
        }
    }
    pthread_spin_unlock(&queueLock);
    return ret;
}



// void MyService::send(uint32_t toSid,shared_ptr<MyBaseMsg> msg){
//     shared_ptr<MyService> toService = MySunnet::inst->getService(toSid);
//     if(!toService){
//         cout << "send fail,toSrv not exist toId:"<<toSid<<endl;
//         return;
//     }
//     toService->pushMsg(msg);
//     bool hasPush = false;

//     //  检查并放入全局队列
//     pthread_spin_lock(&inGlobalLock);
//     {
//         if(!toService->inGlobal){
//             MySunnet::inst->PushGlobalService(toService);
//             toService->inGlobal = true;
//             hasPush = true;
//         }
//     }
//     pthread_spin_unlock(&inGlobalLock);
// }

void MyService::setInGlobal(bool inGlobal){
    pthread_spin_lock(&inGlobalLock);
    {
        this->inGlobal = inGlobal;
    }
    pthread_spin_unlock(&inGlobalLock);
}


void MyService::OnServiceMsg(shared_ptr<MyServiceMsg> m){
        cout << '[' << *type << "-" << id << "] OnMsg: "<< m->buff << endl; 

        auto msgRet = MySunnet::inst->MakeMsg(id,new char[9999999]{'p','i','n','g','\0'},9999999);
        

        MySunnet::inst->send(m->source,msgRet);
}


void MyService::OnAcceptMsg(shared_ptr<MySocketAcceptMsg> m){
    cout << m->client_fd << " success ping " << id;
    MySunnet::inst->AddConnWriteObj(m->client_fd);
}


void MyService::OnSocketData(int fd,char buff[],int len){
    cout << "fd:"<< fd << " socketData buff:"<< buff << endl;
    // char writeBuff[6] = {'w','e','l','l','o','w'};
    // write(fd,&writeBuff,6);
    // usleep(15000000);
    // char writeBuff2[2] = {'h','i'};
    // int r = write(fd,&writeBuff2,2);
    // cout << "write2 r:" << r << " "<< strerror(errno) << endl;
    // usleep(20000);
    // char writeBuff3[3] = {'t','h','e'};
    // r = write(fd,&writeBuff3,3);
    // cout << "write3 r:" << r << " "<< strerror(errno) << endl;

    //  发送大量数据实验
    // char* writebuff = new char[4200000];
    // writebuff[4200000 - 1] = 'e';

    // int r = write(fd,writebuff,4200000);

    // cout << "send count:" << r << " "<< strerror(errno) << endl;

    //  写缓冲区
    char* writebuff = new char[4200000];
    writebuff[4200000 - 1] = 'e';

    auto writerObj = MySunnet::inst->GetConnWriteObj(fd);
    writerObj->EntireWrite(shared_ptr<char>(writebuff),4200000);
}

void MyService::OnSocketWritable(int fd){
    cout << "fd:"<< fd << " writable"<<endl;
    auto writerObj = MySunnet::inst->GetConnWriteObj(fd);
    writerObj->OnWriteable();
}

void MyService::OnSocketClose(int fd){
    cout << "close "<< fd << " "<< strerror(errno) << endl;
    MySunnet::inst->CloseConn(fd);
}