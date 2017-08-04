#include <stdio.h>
//#include "pub.h"
//#include "func.h"

extern char g_str[30];

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    func();
    printf("g_str = %s\n", g_str);
}
