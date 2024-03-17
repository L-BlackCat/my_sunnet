#pragma once
#include "MyMsg.h"
#include <queue>
#include <memory>

using namespace std;



class MyService{
    public:
        //  服务id
        uint32_t id;
        //  服务类型
        shared_ptr<string> type;
        //  队列
        queue<shared_ptr<MyBaseMsg>> msgQueue;

        //  锁
        pthread_spinlock_t queueLock;

        bool isExiting;

        bool inGlobal;
        pthread_spinlock_t inGlobalLock;

    public:
        MyService();
        ~MyService();
        void OnInit();
        void OnMsg(shared_ptr<MyBaseMsg> msg);
        void OnExit();
    public:
        void pushMsg(shared_ptr<MyBaseMsg> msg);
        bool processMsg();
        bool processMsgs(int num);
        void send(uint32_t toSid,shared_ptr<MyBaseMsg> msg);
        void setInGlobal(bool inGlobal);

    private:
        shared_ptr<MyBaseMsg> popMsg();

        void OnServiceMsg(shared_ptr<MyServiceMsg> m);
        void OnAcceptMsg(shared_ptr<MySocketAcceptMsg> m);


        void OnSocketData(int fd,char buff[],int len);
        void OnSocketWritable(int fd);
        void OnSocketClose(int fd);
};