#include <stdio.h>
#include <string.h>
#include "pub.h"
#include "func.h"
#include "lua_func.h"

extern char g_str[30];
int fprintFunc()
{
	printf("fprintFunc decleration in main\n");
    return 0;
}
int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
//	fprintfFunc();
    if(argv[1] != NULL && strcmp(argv[1], "lua") == 0)
		call_lua(argv[2]);
	func();
    printf("g_str = %s\n", g_str);
}
