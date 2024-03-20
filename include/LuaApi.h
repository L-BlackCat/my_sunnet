#pragma once
#include <iostream>
extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
using namespace std;
class LuaApi{
    public:
        static void OnRegister(lua_State* lua_state);

        static int NewService(lua_State* lua_state);
        static int KillService(lua_State* lua_stat);

        static void OnServiceMsg(lua_State* lua_state);

        static int Send(lua_State* lua_state);
};