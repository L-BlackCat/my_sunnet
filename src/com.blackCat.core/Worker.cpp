#include<iostream>
#include "Worker.h"
#include "MySunnet.h"
#include <unistd.h>

void Worker::operator()(){
    while(true){
        // cout << "do Working..." << worker_id << endl;
        // usleep(1000000);
        shared_ptr<Service> service = MySunnet::inst->PopGlobalService();
        if(service){
            service->processMsgs(each_num);
            checkAndPopGlobal(service);
        }else{
            //  没有可处理的服务消息，休眠0.1秒
            /**
             * 休眠是一个不能够准确适应线上工作环境
             * 时间太短，频繁的唤醒（CPU唤醒线程，上下文切换开销）、检测全局队列，会带来性能损耗
             * 时间太长，工作线程不能及时完成全局任务
             * 
             * 》早期的skynet设置了0.1秒的等待时间，以求达到效率和性能之间的平衡    只适用于对延迟要求不高的场合，例如：MMORPG          不适合应对延迟要求低的RTS（即时战略）-》魔兽争霸3    FPS（第一人称射击游戏）
             * 》后期Skynet版本改用条件变量（pthread_cond_init）的设计来降低延迟
             * 
             * 条件变量会做3件事：解锁->线程休眠->等待->唤醒->加锁                    加锁-》xxx->等待-xxx->解锁
             * 条件变量唤醒：pthread_cond_signal    随机唤醒一个条件变量中等待唤醒的线程
             * 条件唤醒有一定的性能开销，为提高效率，在调用之前它 会做两个判定
             * 1）是否有陷入休眠的线程。如果所有线程都在工作，不做处理
             * 2）正在工作的线程是否足够。如果有两个服务需要处理，而服务开启了5个线程，只有一个线程在睡眠状态，足够出来了，也不做处理
             * 
             * 优化方式：
             *  1.工作线程暂时没有可处理的服务，就进入休眠状态
             *  2.当向全局队列中插入服务后，唤醒正在休眠的工作线程
            */
            // usleep(100);
            MySunnet::inst->waitWorker();
        }
    }
}


void Worker::checkAndPopGlobal(shared_ptr<Service> service){
    if(service->isExiting){
        return;
    }
    /**
     * 无锁情况下：
     *  第一次进入消息处理完成了，正在设置为false时，正好这时候接受到了另一个服务发送过来的消息，获取锁后插入
     * 但是由于已经不在全局消息队列中，工作线程不会获取到消息处理，这个服务的消息就被搁置了
    */
    pthread_spin_lock(&service->queueLock);
    if(!service->msgQueue.empty()){
        MySunnet::inst->PushGlobalService(service);
    }else{
        service->setInGlobal(false);
    }
    pthread_spin_unlock(&service->queueLock);
}