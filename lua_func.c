#include <lua.h>  
#include <lauxlib.h>  
#include <lualib.h>  
#include <string.h>  
#include <unistd.h>  
#include <stdio.h>  

int call_lua(char *func)
{
    int x = 0;
	    long int r;
	lua_State *pLua;

	printf("function call_lua called\n");

    //创建 Lua 库指针，并加载库 
	pLua = luaL_newstate();                     /* 创建Lua接口指针 */
	if(pLua == NULL)
        return 0;
    luaL_openlibs(pLua);/* 加载Lua库 */

	//读取 Lua 代码文件 
    if(luaL_loadfile(pLua, "lua.lua") != 0)    /* 读取lua源文件，仅载入内存而未编译 */
		return 0;
    lua_pcall(pLua, 0, LUA_MULTRET, 0);         /* 执行匿名函数，以编译源代码成二进制码 */
	                                                /* 并将全局变量压栈（函数名也是变量）。*/
	                                                /* 这句看似无用，但是不能省 */
	if(func != NULL) 
	    lua_getglobal(pLua, func);               /* 取全局变量，这里是待调用函数名 */
    else
		lua_getglobal(pLua, "NA");
		
    lua_pushnumber(pLua, x);                    /* 参数压栈。x 为事先定义的变量 */
    if(lua_pcall(pLua, 1, 1, 0) != 0)           /* 执行函数 */
    {
        printf("\nError running function 'func1' : %s\n", lua_tostring(pLua, -1));
        return 0;
    }
    r = lua_tonumber(pLua, -1);                 /* 取栈顶值，并转成数字格式。r 为事先定义的变量 */
    lua_pop(pLua, 1);                           /* 栈顶弹出一个元素，即清除返回值占用的栈空间 */

	//清理
	lua_close(pLua);
}

