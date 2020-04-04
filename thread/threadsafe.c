#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADNUM 4   //4个线程来当做购票的窗口
int g_tickets = 100;  //100张票
pthread_mutex_t lock; //定义一个互斥锁变量

void* ThreadStart(void* arg)
{
  (void*)arg;

  while(1)
  {
    pthread_mutex_lock(&lock);
    if(g_tickets > 0)
    {
      g_tickets--; //总票数-1
      usleep(10000); //模拟一个
      printf("i am thread [%p],I'll sell ticket number [%d]\n",\
                pthread_self(),g_tickets + 1);
    }
    else 
    {
      //假设有一个执行流判断了g_tickets之后发现，g_tickets的值是小于等于0的
      //则会执行else逻辑，直接就被break跳出while循环
      //跳出while循环的执行流还加着互斥锁
      //所以在所有有可能退出线程的地方都需要进行解锁操作
      pthread_mutex_unlock(&lock);
      break;//没有票了，直接返回该线程
    }
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main()
{
  pthread_mutex_init(&lock,NULL);//创建线程之前进行初始化
  pthread_t tid[THREADNUM];//保存线程的标识符
  
  int  i = 0;
  for(i = 0; i < THREADNUM; i++)
  {
    int ret = pthread_create(&tid[i],NULL,ThreadStart,NULL);
    if(ret < 0)
    {
      perror("pthread_create error\n");
      return 0;
    }
  }
  sleep(1);
  for(i = 0; i < THREADNUM; i++)
  {
    //线程等待
    pthread_join(tid[i],NULL);
  }
  
  pthread_mutex_destroy(&lock);
  return 0;
}
