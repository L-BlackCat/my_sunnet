#pragma once
#include "MyConn.h"
#include <memory>
#include <sys/epoll.h>
using namespace std;

class MySocketWorker{
    public:
        int epoll_fd;


    public:
        void operator()();
        void onInit();
    
        void addEvent(int fd);
        void modifyEvent(int fd,bool epollOut);
        void removeEvent(int fd);

        void onEvent(epoll_event ev);
        void onAccept(shared_ptr<MyConn> conn);
        void onSocketRW(shared_ptr<MyConn> conn,bool isReadable,bool isWritable);

};