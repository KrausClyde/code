#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pub.h"
#include "./module_a/func.h"
#include "lua_func.h"

#define BUFF_SIZE 8
extern char g_str[30];
int fprintFunc()
{
	printf("fprintFunc decleration in main\n");
    return 0;
}
int main(int argc, char *argv[])
{
	char *str = (char *)malloc(sizeof(char) * BUFF_SIZE);
	printf("sizeof(str) = %d\n",sizeof(str));
	printf("str = %p\n",str);
	printf("*(str - sizeof(BUFF_SIZE)) = %d\n", *(str - sizeof(BUFF_SIZE)));
	for(int loop = 0; loop < BUFF_SIZE; loop++)
	{
		printf("*(str - %d) = %d\n", loop, *(str - loop));
		printf("*(str + %d) = %d\n", loop, *(str + loop));
	}
	printf("*(str + BUFF_SIZE) = %d\n",*(str + BUFF_SIZE));
	memset(str,g_str,3);

#ifdef MAKEFILE_MACRO
	printf("\r\ndefined makefile macro %s.\r\n", MAKEFILE_MACRO);
#endif
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
