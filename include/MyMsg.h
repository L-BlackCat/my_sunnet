#pragma once 
#include <cstdint>
#include <memory>
using namespace std;

class MyBaseMsg{
    public:
        enum TYPE{
            SERVICE_MSG = 1,
            SOCKER_ACCEPT = 2,
            SOCKER_RW = 3,
        };
        uint8_t type;
        char load[999999]{};
        virtual ~MyBaseMsg(){};
};


class MyServiceMsg : public MyBaseMsg{
    public:
        uint32_t source;
        shared_ptr<char> buff;
        size_t size;
};

class MySocketAcceptMsg : public MyBaseMsg{
    public:
        int client_fd;
        int listen_fd;
};

class MySocketRWMsg : public MyBaseMsg{
    public:
        int fd;
        bool isReadable;
        bool isWritable;
};