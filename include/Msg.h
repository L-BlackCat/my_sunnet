#pragma once 
#include <cstdint>
#include <memory>
using namespace std;

class BaseMsg{
    public:
        enum TYPE{
            SERVICE_MSG = 1,
            SOCKER_ACCEPT = 2,
            SOCKER_RW = 3,
        };
        uint8_t type;
        char load[999999]{};
        virtual ~BaseMsg(){};
};


class ServiceMsg : public BaseMsg{
    public:
        uint32_t source;
        shared_ptr<char> buff;
        size_t size;
};

class SocketAcceptMsg : public BaseMsg{
    public:
        int client_fd;
        int listen_fd;
};

class SocketRWMsg : public BaseMsg{
    public:
        int fd;
        bool isReadable;
        bool isWritable;
};