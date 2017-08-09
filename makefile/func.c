#include <stdio.h>
#include "func.h"
#include "pub.h"

#pragma pack(2)

extern char g_str[30];
extern int fprintFunc();

typedef struct pack
{
    char a;
	unsigned short b;
	int c;
	char d;
}stPack;

void func()
{
	stPack stPack_table[5] = {0};
	stPack stPack_temp = {0};
	printf("stPack_Table = %p\n",stPack_table);
	printf("stPack_Table + 1 = %p\n",stPack_table + 1);
	printf("stPack_Table[0] + 1 = %p\n",&stPack_table[0] + 1);
	printf("stPack_temp = %p\n", &stPack_temp);
	printf("stPack_temp +1 = %p\n", &stPack_temp + 1);
    printf("MEMBER2STRUCT (stPack_temp, stPack, c) = %p\n",MEMBER2STRUCT(&(stPack_temp.c), stPack, c) );
//    printf("(&(stPack *)0)->c = %p\n", ((stPack *)0)->c);
	fprintFunc();
	
	sprintf(g_str, "%s", "Mem");
}
#pragma pack()
