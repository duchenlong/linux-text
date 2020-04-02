#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_start(void* arg)
{
  (void)arg;
  printf("i am new thread\n");
  sleep(5);
  
  //while(1);//此时在检测主线程退出的情况

  //printf("pthread_exit 函数\n");
  //谁调用谁退出
  //pthread_exit(NULL);
 
  printf("pthread_concel 函数 id = [%p]\n",pthread_self());
  pthread_cancel(pthread_self());
  
  while(1)
  {
    printf("出错了，我没有退出!!\n");
  }
  return NULL;
}

int main()
{
  pthread_t tid;
  pthread_create(&tid,NULL,thread_start,NULL);

  //主线程执行的任务
  
  //假设让主线程先退出,判断会出现什么情况
  //sleep(5);
  //pthread_exit(NULL);
  
  pthread_join(tid,NULL);//线程等待
  while(1)
  {
    printf("i am main thread\n");
    sleep(1);
  }
  return 0;
}
