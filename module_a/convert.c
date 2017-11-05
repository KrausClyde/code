#include <stdio.h>
#include "convert.h"

#pragma pack(4)

char *convert(unsigned long Value)
{
    static char buffer[sizeof(unsigned long) * 2 + 1] = {0};
    for(int i = sizeof(unsigned long) * 2 - 1; i >= 0; --i)
    {
        buffer[i] = "0123456789ABCDEF"[Value % 16];
        Value = Value / 16;
    }
    
    return buffer;
}

#pragma pack()
