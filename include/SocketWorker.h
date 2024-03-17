#pragma once
#include "Conn.h"
#include <memory>
#include <sys/epoll.h>
using namespace std;

class SocketWorker{
    public:
        int epoll_fd;


    public:
        void operator()();
        void onInit();
    
        void addEvent(int fd);
        void modifyEvent(int fd,bool epollOut);
        void removeEvent(int fd);

        void onEvent(epoll_event ev);
        void onAccept(shared_ptr<Conn> conn);
        void onSocketRW(shared_ptr<Conn> conn,bool isReadable,bool isWritable);

};