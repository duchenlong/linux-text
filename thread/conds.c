#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADCONSUM 2 //两个消费者线程
#define THREADPRODUCE 2 //两个生产者线程

//0 -- 表示没有临界资源  1 -- 表示有临界资源
int g_resource = 0; //定义一个临界资源

//定义互斥锁和条件变量
pthread_mutex_t lock;//互斥锁
pthread_cond_t consum_cond;//消费者条件变量
pthread_cond_t product_cond;//生产者条件变量

void* ConsumeStart(void* arg)
{
  (void*)arg;
  //写一个死循环，让消费者执行流一直消费
  while(1)
  {
    //上锁
    pthread_mutex_lock(&lock);
    while(g_resource == 0)//如果没有临界资源
    {
      //进行阻塞等待
      //阻塞等待的过程
      //1.把该线程的PCB放到PCB等待队列中 
      //2.取消该线程加的锁
      //3.等待进程被唤醒
      pthread_cond_wait(&consum_cond,&lock);
    }
    g_resource--;//此时进行消费，每次-1
    printf("i am consum pthread [%p], now g_resource = [%d]\n",pthread_self(),g_resource);
    pthread_mutex_unlock(&lock);//解锁
    pthread_cond_signal(&product_cond);//消费者线程通知生产者PCB等待队列
  }
  return NULL;
}

void* ProductStart(void* arg)
{
  (void*)arg;
  while(1)//生产者线程运作
  {
    pthread_mutex_lock(&lock);//互斥条件，上锁
    while(g_resource == 1)//如果有资源，生产者不生产，进行等待
    {
      pthread_cond_wait(&product_cond,&lock);
    }
    g_resource++; //生产一个资源
    printf("i am Product thread [%p], now g_resource = [%d]\n",pthread_self(),g_resource);
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&consum_cond);//生产者通知消费者PCB等待队列
  }
  return NULL;
}

int main()
{
  //初始化互斥锁和条件变量
  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&consum_cond,NULL);
  pthread_cond_init(&product_cond,NULL);
  
  pthread_t Consum_tid[THREADCONSUM];//消费者线程
  pthread_t Producer_tid[THREADPRODUCE];//生产者线程
  int ret = 0;
  int i = 0;
  for(i = 0; i < THREADCONSUM; i++)
  {
    //消费者线程
    ret = pthread_create(&Consum_tid[i],NULL,ConsumeStart,NULL);
    if(ret < 0)
    {
      perror("Consume pthread_create error");
      return 0;
    }
  }
  
  for(i = 0; i < THREADPRODUCE; i++)
  {
    //生产者者线程
    ret = pthread_create(&Producer_tid[i],NULL,ProductStart,NULL);
    if(ret < 0)
    {
      perror("Product pthread_create error");
      return 0;
    }
  }
  //线程进行等待
  for(i = 0; i < 2; i++)
  {
    pthread_join(Consum_tid[i],NULL);
    pthread_join(Producer_tid[i],NULL);
  }

  //销毁互斥锁和条件变量
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&consum_cond);
  pthread_cond_destroy(&product_cond);
  return 0;
}

