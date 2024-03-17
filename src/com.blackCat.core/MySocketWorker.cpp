#include "MySocketWorker.h"
#include <iostream>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "MySunnet.h"
#include <sys/socket.h>
#include <fcntl.h>
using namespace std;

void MySocketWorker::operator()(){

    while(true){
        // cout <<"MySocketWorker do..."<< endl;
        const int EVENT_SIZE = 4;
        struct epoll_event events[EVENT_SIZE];
        //  阻塞等待
        int eventCount = epoll_wait(epoll_fd,events,EVENT_SIZE,-1);
        for (int i = 0; i < eventCount; i++)
        {
            /* code */
            epoll_event event = events[i];

            onEvent(event);
        }
    }
}

void MySocketWorker::onInit(){
    cout << "MySocketWorker onInit()"<<endl;
    epoll_fd = epoll_create(1024);

    assert(epoll_fd > 0);
}

//  更改、增加、删除监听列表的监听列表
void MySocketWorker::addEvent(int fd){
    cout << "AddEvent "<<fd<< endl;
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ev) == -1){
        cout << "AddEvent epoll_ctrl fail:"<< strerror(errno) <<endl;
    }
}

void MySocketWorker::modifyEvent(int fd,bool epollOut){
    struct epoll_event ev;
    ev.data.fd = fd;
    if(epollOut){
        ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
    }else{
        ev.events = EPOLLIN | EPOLLET;
    }
        if(epoll_ctl(epoll_fd,EPOLL_CTL_MOD,fd,&ev) == -1){
        cout << "ModifyEvent epoll_ctrl fail:"<< strerror(errno) <<endl;
    }
}

void MySocketWorker::removeEvent(int fd){ 
    cout << "RemoveEvent "<< fd <<endl;
    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,fd,NULL);
}

void MySocketWorker::onEvent(epoll_event ev){
    cout << "MySocketWorker OnEvent()"<<endl;
    int fd = ev.data.fd;
    /**
     * 1.通过fd获取自定义套接字
     * 2.获取fd触发的事件，判定是可读、可写还是报错等
     * 3.根据自定义套接字的类型，处理事件
    */
    shared_ptr<MyConn> conn = MySunnet::inst->getConn(fd);
    if(!conn){
        cout << "socket worker get conn fail,fd:"<<fd<<endl;
        return;
    }

    bool isRead = ev.events & EPOLLIN;
    bool isWrite = ev.events & EPOLLOUT;
    bool isErr = ev.events & EPOLLERR;

    if(conn->type == MyConn::MY_CONN_TYPE::listen){
        if(isRead){
            onAccept(conn);
        }
        //  暂时没有监听服务套接字的可写事件
    }else{
        if(isRead || isWrite){
            onSocketRW(conn,isRead,isWrite);
        }
        if(isErr){
            cout<< "onEvent err,fd:"<< fd << " " <<strerror(errno)<<endl;
        }
    }
}

void MySocketWorker::onAccept(shared_ptr<MyConn> conn){
    cout << "onAccept fd:"<<conn->fd;
    int listen_fd = conn->fd;
    //  等待客户端连接
    int client_fd = accept(listen_fd,NULL,NULL);
    if(client_fd < 0){
        cout << "onAccept err, cient_fd:"<<client_fd<<endl;
        return;
    }
    //  设置用户非阻塞
    fcntl(client_fd,F_SETFL,O_NONBLOCK);

    //  设置写缓冲区大小（linux按需分配，不会直接分配这个大小）
    // unsigned long buffSize = 4294967295;
    // if(setsockopt(client_fd,SOL_SOCKET,SO_SNDBUFFORCE,&buffSize,sizeof(buffSize)) < 0){
    //     cout << "socketWorker onAccept fail "<< strerror(errno) << endl;
    // }


    //  添加自定义套接字
    MySunnet::inst->AddConn(client_fd,conn->service_id,MyConn::MY_CONN_TYPE::client);

    //  添加到epoll的等待队列中
    struct epoll_event ev;
    ev.data.fd = client_fd;
    ev.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_fd,&ev) == -1){
        cout << "onAccept AddEvent epoll_ctrl fail:"<< strerror(errno) <<endl;
    }

    //  通知服务
    auto msg = make_shared<MySocketAcceptMsg>();
    msg->type = MyBaseMsg::TYPE::SOCKER_ACCEPT;
    msg->client_fd = client_fd;
    msg->listen_fd = listen_fd;
    MySunnet::inst->send(conn->service_id,msg);
}


void MySocketWorker::onSocketRW(shared_ptr<MyConn> conn,bool isReadable,bool isWritable){
    cout << "SocektWorker onSockerRw fd:"<<conn->fd <<endl;
    //  网络模型只做事件分发，不处理事件
    auto msg = make_shared<MySocketRWMsg>();
    msg->type = MyBaseMsg::SOCKER_RW;
    msg->fd = conn->fd;
    msg->isReadable = isReadable;
    msg->isWritable = isWritable;
    MySunnet::inst->send(conn->service_id,msg);
}


