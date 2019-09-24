#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

// --------------------------------------------------------------
// Other lib
// --------------------------------------------------------------
static int OtherFoo(lua_State* L) {
    std::cout << "hello, otherfoo." << std::endl;
    return 0;
}

static const luaL_Reg otherlib[] = {
    {"Foo", OtherFoo},
    {NULL, NULL}
};

int luaopen_other(lua_State* L) {
    luaL_newlib(L, otherlib);
    return 1;
};
}
