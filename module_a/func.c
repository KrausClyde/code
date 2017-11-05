#include <stdio.h>
#include "func.h"
#include "../pub.h"
#include "convert.h"

#pragma pack(2)

extern char g_str[30];
//extern int fprintFunc();
extern void funCall();

typedef struct pack
{
    char a;
	unsigned short b;
	int c;
	char d;
}stPack;

void test();

void func()
{
    int arry[10] = {1,2,3,4,5,6,7,8,9,0};
    int *p = arry;
	char *str = (char *)malloc(sizeof(char) * 8);
	stPack stPack_table[5] = {0};
	stPack stPack_temp = {0};
	printf("stPack_Table = %p\n",stPack_table);
	printf("stPack_Table + 1 = %p\n",stPack_table + 1);
	printf("stPack_Table[0] + 1 = %p\n",&stPack_table[0] + 1);
	printf("stPack_temp = %p\n", &stPack_temp);
	printf("stPack_temp +1 = %p\n", &stPack_temp + 1);
    printf("MEMBER2STRUCT (stPack_temp, stPack, c) = %p\n",MEMBER2STRUCT(&(stPack_temp.c), stPack, c) );
//    printf("(&(stPack *)0)->c = %p\n", ((stPack *)0)->c);
    printf("arry[1] = %d, p[1] = %d, 0[p+1] = %d\n", arry[1], p[1], 0[p+1]);
    printf("convert(34) = %s\n", convert(34));
    printf("convert(16) = %s\nconvert(77) = %s\n",convert(16), convert(77));

    //fprintFunc();
    funCall();
	
    sprintf(g_str, "%s", "Mem");

    test();
}

char *getMemory()
{
    char p[] = "hello world";
    printf("p = %p, %s\n", p, p);
    return p;
}
char *getMemory1(char *p)
{
    p = (char *)malloc(100);
}
void getMemory2(char **p, int num)
{
    *p = (char *)malloc(num);
}
void test()
{
    char *str = NULL;
    str = getMemory();
    printf("getMemory: %p %s\n",str, str);

    getMemory1(str);
    strcpy(str, "hello world");
    printf("getMemory1: %p %s\n", str, str);

    getMemory2(&str, 100);
    strcpy(str, "hello world");
    printf("getMemory2: %p %s\n", str, str);
}
#pragma pack()
