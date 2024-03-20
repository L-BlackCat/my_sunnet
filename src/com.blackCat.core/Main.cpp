#include<iostream>
#include "MySunnet.h"
#include <memory>
#include <unistd.h>
#include <assert.h>
#include <signal.h>
using namespace std;

void test(){
    auto ping = make_shared<string>("ping");
    uint32_t ping1 = MySunnet::inst->NewService(ping);
    uint32_t ping2 = MySunnet::inst->NewService(ping);
    uint32_t pong = MySunnet::inst->NewService(ping);

    auto msg1 = MySunnet::inst->MakeMsg(ping1,new char[3]{'h','i','\0'},3);
    auto msg2 = MySunnet::inst->MakeMsg(ping2,new char[6]{'h','e','l','l','o','\0'},6);

    MySunnet::inst->send(pong,msg1);
    MySunnet::inst->send(pong,msg2);

    
}

void testEpoll(){
    int fd = MySunnet::inst->Listen(8888,1);
    usleep(15 * 1000000);
    MySunnet::inst->CloseConn(fd);
}

void tesetEcho(){
    auto gateway = make_shared<string>("gateway");
    MySunnet::inst->NewService(gateway);
}

int main(){
    //  PIPE信号处理，避免因网络异常，导致TCP连接断开，服务端向客户端发送消息时，因为连接断开收到Broken PIPE信号，进程关闭的问题 
    signal(SIGPIPE,SIG_IGN);
    assert(true);
    // daemon(0,0); //以后台方式运行
    new MySunnet();
    MySunnet::inst->Start();
    //  开启一些系统逻辑
    // test();
    // testEpoll();
    // tesetEcho();

    MySunnet::inst->NewService(make_shared<string>("main"));
    MySunnet::inst->Wait();
    return 0;
}