#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "thread.h"

#pragma pack(4)

void *thread_func(int signo, void *arg);
pthread_t tid;
void *status;

void main()
{
    pthread_t thread_id;
    int count = 0;

	thread_id = pthread_self();//返回调用线程的线程ID
	printf("function: %s thread id :%u.\n",__FUNCTION__, thread_id);

    if(pthread_create(&tid, NULL, thread_func, NULL) != 0)
    {
    	printf("create thread error!\n");
		exit(1);
    }
	sleep(1);

	signal(SIGINT, thread_func);
	signal(SIGQUIT, thread_func);

	pthread_join(tid, &status);

	pause();
	pause();
	
    printf("create thread function, PID:%u, TID:%u\n",getpid(), tid);
 //   pthread_exit(NULL);
	//if(pthread_equal(thread_id, pthread_self()))
}

void *thread_func(int signo, void *arg)
{
    FILE *file;
	char line[200] = {0};
    printf("thread function created, PID:%u, TID:%u\n",getpid(),pthread_self());
	
	if(signo == SIGHUP)
	{
		printf("catch signal SIGHUP\n");
	}
	else if(signo == SIGINT)
	{
		printf("catch signal SIGINT\n");
	}
	else if(signo == SIGQUIT)
	{
		printf("catch signal SIGQUIT\n");
	}
    printf("thread function created, PID:%u, TID:%u\n",getpid(),pthread_self());

	if((file = popen("ls -l", "r")) != NULL)
	{
		while(fgets(line, 200, file) != NULL)
		{
			printf("line = %s\n", line);
		}
	}
	pclose(file);
	pthread_exit(NULL);
}
#pragma pack()
