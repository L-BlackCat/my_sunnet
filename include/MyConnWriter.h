#pragma once
#include <memory>
#include <list>

using namespace std;
class WriteObject{
    public:
        streamsize start;
        shared_ptr<char> buff;
        streamsize len;
};

class MyConnWriter{
    public:
        //  双向链表
        int fd;
        list<shared_ptr<WriteObject>> writeObjs;
    private:
        bool EntireFront();
        void EntireWithEmpty(shared_ptr<char> buff,streamsize len);
        void EntireWithNoEmpty(shared_ptr<char> buff,streamsize len);
    public:
        void OnWriteable();
        void EntireWrite(shared_ptr<char> buff,streamsize len);
    
};