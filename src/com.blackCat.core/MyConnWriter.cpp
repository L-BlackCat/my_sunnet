#include<iostream>
#include "MyConnWriter.h"
#include "MySunnet.h"
#include <sys/socket.h>
#include <unistd.h>


void MyConnWriter::OnWriteable(){
    auto conn = MySunnet::inst->getConn(fd);
    if(conn == NULL){ //连接已关闭
        return;
    }

    while(EntireFront()){
    }
    
    if(writeObjs.empty()){
        MySunnet::inst->ModifyEvent(fd,false);
    }
}

void MyConnWriter::EntireWrite(shared_ptr<char> buff,streamsize len){
    if(writeObjs.empty()){
        EntireWithEmpty(buff,len);
    }else{
        EntireWithNoEmpty(buff,len);
    }
}

bool MyConnWriter::EntireFront(){
    if(writeObjs.empty()){
        return false;
    }
    auto obj = writeObjs.front();

    //谨记：>=0, -1&&EAGAIN, -1&&EINTR, -1&&其他
    char* s = obj->buff.get() + obj->start;

    int newLen = obj->len - obj->start;

    int n = write(fd,s,newLen);


    cout<< "EntireWithFront fd:"<<fd <<" write n:"<<n<< " start:"<< obj->start<<endl;
    //  写失败-》阻塞操作被接收信号中断
    if(n < 0 && errno == EINTR){}

    if(n >= 0 && n == newLen){
        writeObjs.pop_front();
        return true;
    }


    if((n >= 0 && n < newLen) || (n <= 0 && errno == EAGAIN)){
        obj->start += n;
        //  写完，再次返回false，等待写缓存区可写
        return false;
    }

    cout << "EntireWrite write error " << endl;
}

void MyConnWriter::EntireWithEmpty(shared_ptr<char> buff,streamsize len){
    int n = write(fd,&buff,len);
    //  写失败-》阻塞操作被接收信号中断
    if(n < 0 && errno == EINTR){

    }

    cout<< "EntireWithEmpty fd:"<<fd <<" write n:"<<n<<endl;
    if(n >= 0 && n == len){
        return;
    }

    if((n >= 0 && n < len) || (n <= 0 && errno == EAGAIN)){
        auto obj = make_shared<WriteObject>();
        obj->start = n;
        obj->buff = buff;
        obj->len = len;
        writeObjs.push_back(obj);
        MySunnet::inst->ModifyEvent(fd,true);
        return;
    }

    cout<< "EntireWithEmpty is fail,fd:"<<fd<<endl;
}
void MyConnWriter::EntireWithNoEmpty(shared_ptr<char> buff,streamsize len){
    auto obj = make_shared<WriteObject>();
    obj->start = 0;
    obj->buff = buff;
    obj->len = len;
    writeObjs.push_back(obj);
}