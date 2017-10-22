#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pub.h"
#include "./module_a/func.h"
#include "lua_func.h"

#define BUFF_SIZE 8
extern char g_str[30];
extern void func();
 int fprintFunc()
{
	printf("fprintFunc decleration in main\n");
    return 0;
}
int main(int argc, char *argv[])
{
    int loop = 0, i = 0;

#ifdef MAKEFILE_MACRO
	printf("\r\ndefined makefile macro %s.\r\n", MAKEFILE_MACRO);
#endif
    for(i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    if(argv[1] != NULL && strcmp(argv[1], "lua") == 0)
		call_lua(argv[2]);
    fprintFunc();
    func();
    printf("g_str = %s\n", g_str);
}
