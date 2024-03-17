#pragma once
#include "MyService.h"
#include "MyMsg.h"
#include <unordered_map>
#include "MyWorker.h"
#include "MySocketWorker.h"
#include "MyConnWriter.h"
using namespace std;
class MySunnet{
    public:
        static MySunnet* inst;
        int sleepCount; //记录休眠的线程数目
        pthread_mutex_t sleepMutex; //睡眠锁
        pthread_cond_t sleepCond;   //条件变量


    public:
        //  构造函数
        MySunnet();
        void Start();
        void Wait();

        uint32_t NewService(shared_ptr<string> type);
        void KillService(uint32_t id);
        shared_ptr<MyService> GetService(uint32_t id);
        
        //  当服务收到消息时触发
        void PushGlobalService(shared_ptr<MyService> service);
        //  拥有工作线程抓取消息
        shared_ptr<MyService> PopGlobalService();

        shared_ptr<MyBaseMsg> MakeMsg(uint32_t source,char* buff,int len);

        void send(uint32_t toSid,shared_ptr<MyBaseMsg> msg);

        void CheckAndWake(); 
        
        void AddConn(int fd,uint32_t service_id,uint8_t type);
        void RemoveConn(int fd);
        shared_ptr<MyConn> getConn(int fd);

        int Listen(int port,uint32_t server_id);
        void CloseConn(int fd);

        void AddConnWriteObj(int fd);
        void RemoveConnWriteObj(int fd);
        shared_ptr<MyConnWriter> GetConnWriteObj(int fd);

        void ModifyEvent(int fd,bool out);
    private:
        int WORKER_NUM = 3;
        int max_service_id = 0;
        vector<thread*> my_worker_threads;
        vector<MyWorker*> my_workers;
        unordered_map<uint32_t,shared_ptr<MyService>> serviceMap;
        pthread_rwlock_t serviceMapLock;

        int globalLen;
        queue<shared_ptr<MyService>> globalQueue;
        pthread_spinlock_t globalQLock;

        unordered_map<int,shared_ptr<MyConn>> conns;
        pthread_rwlock_t connLock;
        MySocketWorker* my_socket_worker;
        thread* my_socket_worker_thread;
        int epoll_fd;

        unordered_map<int,shared_ptr<MyConnWriter>> connWriterMap;
        pthread_rwlock_t connWriterLock;
    private:
        void startWroker();
        void startSocketWorker();


};