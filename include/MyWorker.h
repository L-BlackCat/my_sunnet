#pragma once
#include <thread>
#include "MyService.h"



class MySunnet;
using namespace std;

class MyWorker{
    public:
        uint32_t worker_id;
        uint32_t each_num;
        void operator()();
    private:
        void checkAndPopGlobal(shared_ptr<MyService> service);
        void waitWorker();
};