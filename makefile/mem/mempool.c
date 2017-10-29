#include <stdio.h>
#include "mempool.h"

#pragma pack(4)

#define MEMORY_BLOCK_SIZE  1024
#define MEMORY_UINT_NUM    32
#define MEMORY_UINT_SIZE   (MEMORY_BLOCK_SIZE / MEMORY_UINT_NUM)

static inline int BIT_MAX_COUNT_NUM(number) 
{
    unsigned int count = 0;          
    for(int i = 0; i < 32; i++)       
    { 
		count += number & 1; 
		number = number >> 1; 
    } 
    return count; 
}

//static inline 
int BIT_FIX_COUNT_NUM(unsigned int number, int memSize) 
{
    unsigned int count = 0; 
	int position = 0; 
    for(int i = 0; i < 32; i++)       
    { 
		if((number & 1) == 1)
		{
		    count = 0;
			position = i + 1;
		}
		count += ((number & 1) ^ 1); 
		number = number >> 1;
		if(count * MEMORY_UINT_SIZE >= memSize)
		{
			return position;
		}
    } 
    return -1; 
}

typedef struct MemoryBlock
{
    struct MemoryBlock *next;
	unsigned int  bitMemoryMap;
	unsigned char memorySize[32];
	char address[0];
}stMemoryBlock;

stMemoryBlock *g_MemPool = NULL;

void* memPoolMalloc(int size)
{
    stMemoryBlock *pstMemPool;
	stMemoryBlock stMemPoolPre = {0};
	int count = 0;

	if(g_MemPool == NULL)
    {
        if(size >= MEMORY_BLOCK_SIZE)
        {
            return malloc(size);
        }
        else
        {
            g_MemPool = malloc(sizeof(stMemoryBlock) + MEMORY_BLOCK_SIZE);
			//g_MemPool->bitMemoryMap  = size / MEMORY_UINT_SIZE;
			for(int i = 0; i < size / MEMORY_UINT_SIZE + (size % MEMORY_UINT_SIZE != 0); i++)
			{
				g_MemPool->bitMemoryMap  = 1 << i;
			}
			g_MemPool->memorySize[0] = size / MEMORY_UINT_SIZE;
			g_MemPool->next = NULL;
            return g_MemPool->address;
        }
    }

	stMemPoolPre.next = g_MemPool;
	while(stMemPoolPre.next)
    {
        pstMemPool = stMemPoolPre.next ;
        if((count = BIT_FIX_COUNT_NUM(pstMemPool->bitMemoryMap, size)) >= 0)
        {
            pstMemPool->memorySize[count] = size / MEMORY_UINT_SIZE;
            return (pstMemPool->address + count * MEMORY_UINT_SIZE);
        }
        stMemPoolPre.next = pstMemPool->next;
    }
	pstMemPool->next = malloc(sizeof(stMemoryBlock) + MEMORY_BLOCK_SIZE);
	//pstMemPool->next->bitMemoryMap = size / MEMORY_UINT_SIZE;
	for(int i = 0; i < size / MEMORY_UINT_SIZE + (size % MEMORY_UINT_SIZE != 0); i++)
	{
		pstMemPool->bitMemoryMap  = 1 << i;
	}
	pstMemPool->memorySize[0] = size / MEMORY_UINT_SIZE;
	pstMemPool->next->next = NULL;
}

void memPoolFree(void *ptr)
{
    unsigned int memorySize = 0, flag = 0;
	stMemoryBlock *pstMemPool;
	stMemoryBlock stMemPoolPre = {0};
	stMemPoolPre.next = g_MemPool;
    while(stMemPoolPre.next)
    {
        pstMemPool = stMemPoolPre.next ;
        if(pstMemPool->address <= ptr <= (pstMemPool->address + MEMORY_BLOCK_SIZE - MEMORY_UINT_SIZE))
    	{
    	    memorySize = (ptr - (void *)pstMemPool->address) / MEMORY_UINT_SIZE;
			
			for(unsigned int i = 0; i < pstMemPool->memorySize[memorySize]; i++)
			{
				flag += 1 << (memorySize + i);
			}
			pstMemPool->memorySize[memorySize] = 0;
			pstMemPool->bitMemoryMap -= flag;
    	}
        stMemPoolPre.next = pstMemPool->next;
    }
}


void main()
{
    int count = 0;
	unsigned int number = (unsigned int)0xffffff00;

	do{
    count = 0;
    while(number)
    {
    	if(number)
    	{
    		count += number & 1;
    		number = number >> 1;
    	}
    }
   }while(0);
   printf("BIT_MAX_COUNT_NUM(1) = %d, number = %d\n",count, number);

   
    count = 0;
	number = 0xffffff00;
    count = BIT_MAX_COUNT_NUM((unsigned int)number);
    printf("BIT_MAX_COUNT_NUM(24) = %u, number = %u\n",count, number);

	number = 0xffffff00;
    count = BIT_FIX_COUNT_NUM(number, 42);
    printf("BIT_FIX_COUNT_NUM(24) = %u, number = %u\n",count, number);


 //   printf("BIT_COUNT_NUM(0xffffff00) = %d\n", BIT_COUNT_NUM((unsigned int)0xffffff00) );
}

#pragma pack()
