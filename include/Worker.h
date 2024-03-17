#pragma once
#include <thread>
#include "Service.h"



class MySunnet;
using namespace std;

class Worker{
    public:
        uint32_t worker_id;
        uint32_t each_num;
        void operator()();
    private:
        void checkAndPopGlobal(shared_ptr<Service> service);
        void waitWorker();
};