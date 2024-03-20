#include "LuaApi.h"
#include "MySunnet.h"
#include <string.h>


 void LuaApi::OnRegister(lua_State* lua_state){
    static luaL_Reg lualibs[] = {
        {"NewService",NewService},
        {"KillService",KillService},
        {"Send",Send},
        {NULL,NULL}
    };
    luaL_newlib(lua_state,lualibs);
    //  将堆栈弹出一个值，并将其设置为局变量 name 的新值。
    lua_setglobal(lua_state,"my_sunnet");
}

int LuaApi::NewService(lua_State* lua_state){
    //  想让lua调用，从虚拟机栈中获取所需数据

    //  获取栈长度
    int num = lua_gettop(lua_state);
    if(num != 1){
        lua_pushinteger(lua_state,-1);
        cout << "lua stack is empty,err:"<<lua_tostring(lua_state,-1) << endl;
        return 1;
    }

    if(lua_isstring(lua_state,-1) == 0){
        lua_pushinteger(lua_state,-1);
        cout << "lua stack top is not string" <<endl;
        return 1;
    }

    size_t len = 0;
    //  获取服务类型
    const char* type = luaL_tolstring(lua_state,1,&len);
    char* newType = new char[len + 1];
    newType[len] = '\0';
    memcpy(newType,type,len);
    auto t = make_shared<string>(newType);
    uint32_t id = MySunnet::inst->NewService(t);
    //  将结果返压入lua栈顶
    lua_pushinteger(lua_state,id);
    return 1;
}

int LuaApi::KillService(lua_State* lua_state){
   int num = lua_gettop(lua_state);
    if(num != 1){
        lua_pushinteger(lua_state,-1);
        cout << "lua stack is empty,err:"<<lua_tostring(lua_state,-1) << endl;
        return 0;
    }
    
    if(lua_isinteger(lua_state,-1) == 0){
        lua_pushinteger(lua_state,-1);
        cout << "lua stack top is not integer" <<endl;
        return 0;
    }

    int id = lua_tointeger(lua_state,-1);

    MySunnet::inst->KillService(id);
    lua_pushinteger(lua_state,1);
    return 0;
}


int LuaApi::Send(lua_State* lua_state){
    int num = lua_gettop(lua_state);
    if(num != 3){
        cout << "[luaAPI] param num is fail:"<< lua_tostring(lua_state,1)<<endl;
        return 0;
    }
    if(lua_isinteger(lua_state,1) == 0){
        cout << "[luaAPI] send fail,arg1 err"<<endl;
        return 0;
    }

    int source = lua_tointeger(lua_state,1);

    if(lua_isinteger(lua_state,2) == 0){
        cout << "[luaAPI] send fail,arg2 err"<<endl;
        return 0;
    }
    int target = lua_tointeger(lua_state,2);
    
    if(lua_isstring(lua_state,3) == 0){
        cout << "[luaAPI] send fail,arg3 err"<<endl;
        return 0;
    }
    size_t len = 0;
    const char* buff = lua_tolstring(lua_state,3,&len);
    char* newBuff = new char[len];
    // newBuff[len] = '\0';
    memcpy(newBuff,buff,len);

    auto msg = make_shared<ServiceMsg>();
    msg->type = BaseMsg::TYPE::SERVICE_MSG;
    msg->source = source;
    msg->buff = shared_ptr<char>(newBuff);
    msg->size = len;

    MySunnet::inst->send(target,msg);

    return 0;
}


// void LuaApi::OnServiceMsg(lua_State* lua_state){

// }
