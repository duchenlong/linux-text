#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_start(void* arg)
{
  while(1)
  {
    printf("i am new thread ~~~~\n");
    sleep(1);
  }
}

int main()
{
  pthread_t tid;
  int ret = pthread_create(&tid,NULL,thread_start,NULL);
  
  if(ret < 0)
  {
    printf("pthread_create error \n");
    return 0;
  }

  while(1)
  {
    printf("i am main thread~~~\n");
    sleep(1);
  }
  return 0;
}
