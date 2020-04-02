#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct thread_info
{
  int thread_num_;
  thread_info()
  {
    thread_num_ = -1;
  }
}THREADINFO;

void* thread_start(void* arg)
{
 // int *i = (int*)arg;
  THREADINFO* ti = (THREADINFO*)arg;
  while(1) 
  {
    printf("i am new thread ~~~~ i = [%d]\n",ti->thread_num_);
    sleep(1);
  }
  //对于传递的堆上开辟的内存
  //可以在入口函数结束的最后进行释放，可以避免内存泄漏
  delete ti;
  return NULL;
}

int main()
{
  pthread_t tid;
  int ret;
 //错误的传参方式
 // {
 //    int i = 10;
 //    ret = pthread_create(&tid,NULL,thread_start,(void*)&i);
 // }
  
  int i = 0;
  for(; i < 4; i++)
  {
    //给线程传递参数
    //从堆上开辟内存
    THREADINFO* threadinfo = new thread_info();
    threadinfo->thread_num_ = i;

    ret = pthread_create(&tid,NULL,thread_start,(void*)threadinfo);
   // sleep(1);
    if(ret < 0)
    {
      printf("pthread_create error \n");
      return 0;
    }

  }


  while(1)
  {
    printf("i am main thread~~~\n");
    sleep(1);
  }
  return 0;
}
