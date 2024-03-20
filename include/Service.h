#pragma once
#include "Msg.h"
#include <queue>
#include <memory>
extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

using namespace std;



class Service{
    public:
        //  服务id
        uint32_t id;
        //  服务类型
        shared_ptr<string> type;
        //  队列
        queue<shared_ptr<BaseMsg>> msgQueue;

        //  锁
        pthread_spinlock_t queueLock;

        bool isExiting;

        bool inGlobal;
        pthread_spinlock_t inGlobalLock;
    private:
        lua_State* lua_state;

    public:
        Service();
        ~Service();
        void OnInit();
        void OnMsg(shared_ptr<BaseMsg> msg);
        void OnExit();
    public:
        void pushMsg(shared_ptr<BaseMsg> msg);
        bool processMsg();
        bool processMsgs(int num);
        void send(uint32_t toSid,shared_ptr<BaseMsg> msg);
        void setInGlobal(bool inGlobal);

    private:
        shared_ptr<BaseMsg> popMsg();

        void OnServiceMsg(shared_ptr<ServiceMsg> m);
        void OnAcceptMsg(shared_ptr<SocketAcceptMsg> m);


        void OnSocketData(int fd,char buff[],int len);
        void OnSocketWritable(int fd);
        void OnSocketClose(int fd);
};