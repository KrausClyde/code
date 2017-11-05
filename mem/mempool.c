#include <stdio.h>
#include "mempool.h"

#pragma pack(4)

#define MEMORY_BLOCK_SIZE  1024
#define MEMORY_UINT_NUM    32
#define MEMORY_UINT_SIZE   (MEMORY_BLOCK_SIZE / MEMORY_UINT_NUM)

//内存片最大数量
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

//查找可用内存片位置
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
    void *ptr = NULL;
	stMemoryBlock *pstMemPool;
	stMemoryBlock stMemPoolPre = {0};
	int count = 0;

	if(g_MemPool == NULL)
    {
        if(size >= MEMORY_BLOCK_SIZE)
        {
            ptr = malloc(size);
			memset(ptr, 0, size);
			return ptr;
        }
        else
        {
            g_MemPool = malloc(sizeof(stMemoryBlock) + MEMORY_BLOCK_SIZE);
			memset(g_MemPool, 0, sizeof(stMemoryBlock) + MEMORY_BLOCK_SIZE);
			//g_MemPool->bitMemoryMap  = size / MEMORY_UINT_SIZE;
			for(int i = 0; i < size / MEMORY_UINT_SIZE + (size % MEMORY_UINT_SIZE != 0); i++)
			{
				g_MemPool->bitMemoryMap  += (1 << i);
			}
			g_MemPool->memorySize[0] = size / MEMORY_UINT_SIZE + (size % MEMORY_UINT_SIZE != 0);
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
            pstMemPool->memorySize[count] = size / MEMORY_UINT_SIZE + (size % MEMORY_UINT_SIZE != 0);
			for(int i = count; i < size / MEMORY_UINT_SIZE + (size % MEMORY_UINT_SIZE != 0) + count; i++)
			{
				pstMemPool->bitMemoryMap  += (1 << i);
			}
			printf("count = %d  pstMemPool->memorySize[count] = %d\n",count, pstMemPool->memorySize[count]);
            return (pstMemPool->address + count * MEMORY_UINT_SIZE);
        }
        stMemPoolPre.next = pstMemPool->next;
    }
	pstMemPool->next = malloc(sizeof(stMemoryBlock) + MEMORY_BLOCK_SIZE);
	memset(pstMemPool->next, 0, sizeof(stMemoryBlock) + MEMORY_BLOCK_SIZE);
	//pstMemPool->next->bitMemoryMap = size / MEMORY_UINT_SIZE;
	for(int i = 0; i < size / MEMORY_UINT_SIZE + (size % MEMORY_UINT_SIZE != 0); i++)
	{
		pstMemPool->next->bitMemoryMap  += (1 << i);
	}
	pstMemPool->next->memorySize[0] = size / MEMORY_UINT_SIZE + (size % MEMORY_UINT_SIZE != 0);
	pstMemPool->next->next = NULL;
	return (pstMemPool->next->address);
}

void memPoolFree(void *ptr)
{
    //内存片在内存块中的位置，内存片占据空间
    unsigned int memoryPos = 0, flag = 0;
	stMemoryBlock *pstMemPool;
	stMemoryBlock stMemPoolPre = {0};
	stMemoryBlock *pstMemPoolPre = &stMemPoolPre;
	pstMemPoolPre->next = g_MemPool;
    while(pstMemPoolPre->next)
    {
        flag = 0;
		pstMemPool = pstMemPoolPre->next ;
        if(pstMemPool->address <= ptr && ptr <= (pstMemPool->address + MEMORY_BLOCK_SIZE - MEMORY_UINT_SIZE))
    	{
    	    memoryPos = ((unsigned int)(ptr - (void *)pstMemPool->address)) / MEMORY_UINT_SIZE;
			
			for(unsigned int i = 0; i < pstMemPool->memorySize[memoryPos]; i++)
			{
				flag += (1 << (memoryPos + i));
			}
			pstMemPool->memorySize[memoryPos] = 0;
			pstMemPool->bitMemoryMap -= flag;
    	}
		if(pstMemPool->bitMemoryMap == 0)
		{
			pstMemPoolPre->next = pstMemPoolPre->next->next;			

			if(g_MemPool == pstMemPool)
			{
				g_MemPool = pstMemPoolPre->next;
			}
			free(pstMemPool);
		}
        else
        {
            pstMemPoolPre->next = pstMemPoolPre->next->next;
        }
    }
	if(flag == 0)
	{
		free(ptr);
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

    char *str = memPoolMalloc(104);
	char *str1 = memPoolMalloc(34);
	char *str2 = memPoolMalloc(64);
	char *str3 = memPoolMalloc(104);

	stMemoryBlock *pstMemPool = g_MemPool;
	while(pstMemPool != NULL)
	{
		printf("pstMemPool->bitMemoryMap = %u\n",pstMemPool->bitMemoryMap);	
		for(int j = 0; j <= 8; j++)
		{
			printf("pstMemPool->memorySize[%d] = %u \n",j, pstMemPool->memorySize[j]);
		}
		pstMemPool = pstMemPool->next;
	}
	printf("\n");
	memPoolFree(str1);
	pstMemPool = g_MemPool;
	int loop = 0;
	while(pstMemPool != NULL)
	{
	    loop++;
		printf("loop = %d\n pstMemPool->bitMemoryMap = %u\n",loop, pstMemPool->bitMemoryMap);
		for(int j = 0; j <= 8; j++)
		{
			printf("pstMemPool->memorySize[%d] = %u \n",j, pstMemPool->memorySize[j]);
		}
		pstMemPool = pstMemPool->next;
	}
}

#pragma pack()
