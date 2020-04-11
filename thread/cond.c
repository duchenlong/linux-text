#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//0 -- 表示没有临界资源  1 -- 表示有临界资源
int g_resource = 0; //定义一个临界资源

//定义互斥锁和条件变量
pthread_mutex_t lock;//互斥锁
pthread_cond_t cond;//条件变量

void* ConsumeStart(void* arg)
{
  (void*)arg;
  //写一个死循环，让消费者执行流一直消费
  while(1)
  {
    //上锁
    pthread_mutex_lock(&lock);
    if(g_resource == 0)//如果没有临界资源
    {
      //进行阻塞等待
      //阻塞等待的过程
      //1.把该线程的PCB放到PCB等待队列中 
      //2.取消该线程加的锁
      //3.等待进程被唤醒
      pthread_cond_wait(&cond,&lock);
    }
    sleep(1);
    g_resource--;//此时进行消费，每次-1
    printf("i am consum pthread, now g_resource = [%d]\n",g_resource);
    pthread_mutex_unlock(&lock);//解锁
    pthread_cond_signal(&cond);
  }
  return NULL;
}

void* ProductStart(void* arg)
{
  (void*)arg;
  while(1)//生产者线程运作
  {
    pthread_mutex_lock(&lock);//互斥条件，上锁
    if(g_resource == 1)//如果有资源，生产者不生产，进行等待
    {
      pthread_cond_wait(&cond,&lock);
    }
    sleep(1);
    g_resource++; //生产一个资源
    printf("i am Product thread, now g_resource = [%d]\n",g_resource);
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
  }
  return NULL;
}

int main()
{
  //初始化互斥锁和条件变量
  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&cond,NULL);

  pthread_t tid[2];
  //消费者线程
  int ret = pthread_create(&tid[0],NULL,ConsumeStart,NULL);
  if(ret < 0)
  {
    perror("Consume pthread_create error");
    return 0;
  }

  //生产者者线程
  ret = pthread_create(&tid[1],NULL,ProductStart,NULL);
  if(ret < 0)
  {
    perror("Product pthread_create error");
    return 0;
  }
  int i = 0;
  //线程进行等待
  for(i = 0; i < 2; i++)
  {
    pthread_join(tid[i],NULL);
  }

  //销毁互斥锁和条件变量
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cond);
  return 0;
}

