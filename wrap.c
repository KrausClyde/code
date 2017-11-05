#include <stdio.h>
#include <stdlib.h>

unsigned int g_MemoryCount = 0;

void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size)
{
    g_MemoryCount++;
    printf("__wrap_malloc called\n");
    return __real_malloc(size);
}

void __real_free(void* ptr);

void __wrap_free(void* ptr)
{
    g_MemoryCount--;
    printf("__wrap_free called\n");
    return __real_free(ptr);
}
