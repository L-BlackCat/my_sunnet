#include "Service.h"
#include <iostream>

#include "MySunnet.h"

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "LuaApi.h"


// class MySunnet;

Service::Service(){
    //  初始化锁
    pthread_spin_init(&queueLock,PTHREAD_PROCESS_PRIVATE);
    pthread_spin_init(&inGlobalLock,PTHREAD_PROCESS_PRIVATE);
}

Service::~Service(){
    //  删除锁
    pthread_spin_destroy(&queueLock);
    pthread_spin_destroy(&inGlobalLock);
}


void Service::OnInit(){
    cout << '[' << *type << "-" << id << "] OnInit()" << endl;
    
    // MySunnet::inst->Listen(8888,id);         //  测试用

    //  增加lua_state指针，用于创建管理虚拟机

    lua_state = luaL_newstate();

    luaL_openlibs(lua_state);
    string path = get_current_dir_name();
    string filename = "../service/" + *type + "/init.lua";

    //  lua_state编译并执行lua文件
    int isok = luaL_dofile(lua_state,filename.data());
    if(isok == 1){ //成功返回值为0，失败则为1.
         cout << "run lua fail:" << lua_tostring(lua_state, -1) << endl;
    }else{
        cout << "success lua file "<< *type << id << endl;
    }

    //  注册MySunnet系统API
    LuaApi::OnRegister(lua_state);

    //  把全局变量 name 里的值压栈，返回该值的类型。
    lua_getglobal(lua_state,"OnInit");

    lua_pushinteger(lua_state,id);

    isok = lua_pcall(lua_state,1,0,0);

    if(isok != 0){
        cout << "service call lua is fail,err:" << lua_tostring(lua_state,-1) << endl;
    }

}


void Service::OnMsg(shared_ptr<BaseMsg> msg){
    if(msg->type == BaseMsg::TYPE::SERVICE_MSG){
        auto m = dynamic_pointer_cast<ServiceMsg>(msg);
        OnServiceMsg(m);
    }else if(msg->type == BaseMsg::TYPE::SOCKER_ACCEPT){
        auto m = dynamic_pointer_cast<SocketAcceptMsg>(msg);
        OnAcceptMsg(m);
    }else if(msg->type == BaseMsg::TYPE::SOCKER_RW){

        auto m = dynamic_pointer_cast<SocketRWMsg>(msg);
        int fd = m->fd;
        if(m->isReadable){
            const int BUFF_SIZE = 1024;
            char buff[BUFF_SIZE];
            int len;
            /**
             * 1.   可读-》读取成功-》可写
             * 2.   可读-》读取失败-》可写
             * 3.   可读-》读取成功
             * 4.   可读-》可写
             * 5.   可读-》读取失败
            */
            do{
                len = read(fd,&buff,BUFF_SIZE);
                if(len > 0){
                    OnSocketData(fd,buff,len);
                }
            }while(len == BUFF_SIZE);

            /**
             * 假设收到4条指令，在第2条指令的时候，关闭了conn，后面两条read会失败，再次触发OnSocketEroor
             * 这不是我们想看到的结果->我们希望关闭后不在重复执行关闭操作
             * 解决思路：在关闭时，进行一次conn检测 （会多一次读锁的消耗）
             * 
            */
            if(len <= 0 && errno != EAGAIN){
                if(MySunnet::inst->getConn(fd)){
                    //  报错
                    OnSocketClose(fd);
                }
            }
        }

        if(m->isWritable){
            if(MySunnet::inst->getConn(fd)){
                OnSocketWritable(fd);
            }
        }
    }else{
        cout << '[' << *type << "-" << id << "] OnMsg()" << endl; 
    }
}


void Service::OnExit(){
    cout << '[' << *type << "-" << id << "] OnExit()" << endl; 

    lua_getglobal(lua_state,"OnExit");
    int ret = lua_pcall(lua_state,0,0,0); 
    if(ret != 0){
        cout << "service call lua is fail,err:" << lua_tostring(lua_state,-1) << endl;
    }
    lua_close(lua_state);

}

void Service::pushMsg(shared_ptr<BaseMsg> msg){
    pthread_spin_lock(&queueLock);
    {
        msgQueue.push(msg);
    }
    pthread_spin_unlock(&queueLock);
}


bool Service::processMsg(){
    shared_ptr<BaseMsg> ret = popMsg();
    if(ret){
        OnMsg(ret);
        return true;
    }
    return false;
}

bool Service::processMsgs(int num){
    for (int i = 0; i < num; i++)
    {
        /* code */
        bool succ = processMsg();
        if(!succ){
            return false;
        }
    }
    return true;
}

shared_ptr<BaseMsg> Service::popMsg(){
    shared_ptr<BaseMsg> ret = NULL;
    pthread_spin_lock(&queueLock);
    {
        if(!msgQueue.empty()){
            ret = msgQueue.front();
            msgQueue.pop();
        }
    }
    pthread_spin_unlock(&queueLock);
    return ret;
}


void Service::setInGlobal(bool inGlobal){
    pthread_spin_lock(&inGlobalLock);
    {
        this->inGlobal = inGlobal;
    }
    pthread_spin_unlock(&inGlobalLock);
}


void Service::OnServiceMsg(shared_ptr<ServiceMsg> m){
        // cout << '[' << *type << "-" << id << "] OnMsg: "<< m->buff << endl; 

        // auto msgRet = MySunnet::inst->MakeMsg(id,new char[9999999]{'p','i','n','g','\0'},9999999);
        

        // MySunnet::inst->send(m->source,msgRet);

        lua_getglobal(lua_state,"OnServiceMsg");
        lua_pushinteger(lua_state,m->source);
        lua_pushlstring(lua_state,m->buff.get(),m->size);

        int ret = lua_pcall(lua_state,2,0,0);
        if(ret != 0){
            cout <<"call lua OnServiceMsg fail id:" << id << " to:"<< m->source << " "<< lua_tostring(lua_state,-1)<<endl; 
        }

        if(isExiting){
            lua_close(lua_state);
        }
}


void Service::OnAcceptMsg(shared_ptr<SocketAcceptMsg> m){
    cout << m->client_fd << " success ping " << id;
    MySunnet::inst->AddConnWriteObj(m->client_fd);
}


void Service::OnSocketData(int fd,char buff[],int len){
    cout << "fd:"<< fd << " socketData buff:"<< buff << endl;
    // char writeBuff[6] = {'w','e','l','l','o','w'};
    // write(fd,&writeBuff,6);
    // usleep(15000000);
    // char writeBuff2[2] = {'h','i'};
    // int r = write(fd,&writeBuff2,2);
    // cout << "write2 r:" << r << " "<< strerror(errno) << endl;
    // usleep(20000);
    // char writeBuff3[3] = {'t','h','e'};
    // r = write(fd,&writeBuff3,3);
    // cout << "write3 r:" << r << " "<< strerror(errno) << endl;

    //  发送大量数据实验
    // char* writebuff = new char[4200000];
    // writebuff[4200000 - 1] = 'e';

    // int r = write(fd,writebuff,4200000);

    // cout << "send count:" << r << " "<< strerror(errno) << endl;

    //  写缓冲区
    char* writebuff = new char[4200000];
    writebuff[4200000 - 1] = 'e';

    auto writerObj = MySunnet::inst->GetConnWriteObj(fd);
    writerObj->EntireWrite(shared_ptr<char>(writebuff),4200000);
}

void Service::OnSocketWritable(int fd){
    cout << "fd:"<< fd << " writable"<<endl;
    auto writerObj = MySunnet::inst->GetConnWriteObj(fd);
    writerObj->OnWriteable();
}

void Service::OnSocketClose(int fd){
    cout << "close "<< fd << " "<< strerror(errno) << endl;
    MySunnet::inst->CloseConn(fd);
}