#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

void* memPoolMalloc(int size);
void memPoolFree(void *ptr);

#endif
