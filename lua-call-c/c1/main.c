#include <stdio.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#if !defined(lua_writestringerror)
#define lua_writestringerror(s, p) \
    (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

static void l_message(const char* pname, const char* msg) {
    if(pname) lua_writestringerror("%s:", pname);
    lua_writestringerror("%s\n", msg);
}

static int msghandler (lua_State *L) {
  const char *msg = lua_tostring(L, 1);
  if (msg == NULL) {  /* is error object not a string? */
    if (luaL_callmeta(L, 1, "__tostring") &&  /* does it have a metamethod */
        lua_type(L, -1) == LUA_TSTRING)  /* that produces a string? */
      return 1;  /* that is the message */
    else
      msg = lua_pushfstring(L, "(error object is a %s value)",
                               luaL_typename(L, 1));
  }
  luaL_traceback(L, L, msg, 1);  /* append a standard traceback */
  return 1;  /* return the traceback */
}

void handle_init(lua_State* L, const char* script_path) {
    luaL_openlibs(L);
    luaL_dofile(L, script_path);
}

int handle_script(lua_State* L) {
    int status = 0;
    int err_func = 0;

    lua_pushcfunction(L, &msghandler);
    err_func = lua_gettop(L);

    const char* fname = "test_other";
    lua_getglobal(L, fname);
    status = lua_pcall(L, 0, 0, err_func);
    if(status != LUA_OK) {
        const char* err_msg = lua_tostring(L, -1);
        l_message("handle_script", err_msg);
        lua_pop(L, 1);
        return 0;
    }

    return 1;
}

static int pmain(lua_State* L) {
    int status = 0;
    const char* lua_script_path = "test.lua";

    handle_init(L, lua_script_path);

    status = handle_script(L);
    if(status)
        lua_pushboolean(L, 1);
    else
        lua_pushboolean(L, 0);

    return 1;
}

int main(void) {
    int status = 0;
    int result = 0;

    lua_State* L = luaL_newstate();
    if(L == NULL) {
        l_message("main", "cannot create state!");
        return 1;
    }

    lua_pushcfunction(L, &pmain);
    status = lua_pcall(L, 0, 1, 0);
    if(status != LUA_OK) {
        const char* err_msg = lua_tostring(L, -1);
        l_message("main", err_msg);
        lua_pop(L, 1);
    }
    else{
        result = lua_toboolean(L, -1);
        printf("result: %d\n", result);
    }

    lua_close(L);
    return (status == LUA_OK && result)?0:1;
}
