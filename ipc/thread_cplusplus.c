#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

void* processTrace(void *ptr);

class Test
{
public:
    void init();
    void run();

private:
    int data;
};

void Test::init()
{
   cout<<"init..."<<endl;
    pthread_attr_t attr; 
   pthread_t tid;
   pthread_attr_init(&attr); 
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
   pthread_create(&tid, &attr, processTrace, NULL);
    cout<<"init  done"<<endl;
}

void Test::run()
{
    int loop = 10;
    while(loop--)
    {
        cout<<"run ...."<<endl;
        sleep(1);
    }
}

void* processTrace(void *ptr)
{
    while(1)
    {
        cout<<"process..."<<endl;
        sleep(1);
    }
}
Test *p = NULL;
int main()
{
    Test t;
    t.init();
    t.run();
cout<<"-----"<<endl;
    p = new Test;
    p->init();
    p->run();
    return 0;
}
