#include <stdio.h>
#include "func.h"
//#include "pub.h"

extern char g_str[30];

void func()
{
    fprintFunc();
	
	sprintf(g_str, "%s", "Mem");
}
