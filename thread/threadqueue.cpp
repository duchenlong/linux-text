#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <queue>

using std::queue;

#define CAPACITY 1 // queue start capacity 
#define THREADCOUNT 2 //thread number

//thread safe queue
class BlockQueue
{
public:
  BlockQueue(size_t Capacity = CAPACITY)
  {
    _Capacity = Capacity;
    pthread_mutex_init(&_Lock, NULL);
    pthread_cond_init(&_ConsumeCond, NULL);
    pthread_cond_init(&_ProductCond, NULL);
  }
  
  //push == Producer 
  void Push(int& Data)
  {
    pthread_mutex_lock(&_Lock);
    //判断queue是否满了
    while(IsFull())
    {
      pthread_cond_wait(&_ProductCond,&_Lock);
    }

    _Queue.push(Data);
    pthread_mutex_unlock(&_Lock);
    pthread_cond_signal(&_ConsumeCond);
  }
  
  //pop == consumer
  void Pop(int* Data)
  {
    pthread_mutex_lock(&_Lock);

    while(_Queue.empty())
    {
      pthread_cond_wait(&_ConsumeCond, &_Lock); 
    } 

    *Data = _Queue.front();
    _Queue.pop();
    pthread_mutex_unlock(&_Lock);
    pthread_cond_signal(&_ProductCond);
  }

  ~BlockQueue()
  {
    pthread_mutex_destroy(&_Lock);
    pthread_cond_destroy(&_ConsumeCond);
    pthread_cond_destroy(&_ProductCond);
  }
private:
  bool IsFull()
  {
    if(_Queue.size() == _Capacity)
      return true;
    return false;
  }
private:
  queue<int> _Queue;
  size_t _Capacity; // queue max capacity 
  //互斥
  pthread_mutex_t _Lock;//mutex
  //同步
  pthread_cond_t _ConsumeCond; // consume cond 
  pthread_cond_t _ProductCond; // product _ProductCond 
};

void* Consumer_start(void* arg)
{
  BlockQueue* que = (BlockQueue*)arg;
  while(1)
  {
    int Data;
    que->Pop(&Data);
    printf("\n\n######################################\n");
    printf("Consumer_thread :  [%p]\n", pthread_self());
    printf("i consume resource [%d]\n", Data);
    printf("######################################\n");
  }
  return NULL;
}

void* Producter_start(void* arg)
{
  BlockQueue* que = (BlockQueue*)arg;
  int resource = 1;
  while(1)
  {
    que->Push(resource);
    resource++;
    printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("Producter_thread : [%p]\n",pthread_self());
    printf("i product resource [%d]\n",resource - 1);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
  }
  return NULL;

}

int main()
{
  BlockQueue* que = new BlockQueue();
  pthread_t com_tid[THREADCOUNT], pro_tid[THREADCOUNT];
  int ret = 0;
  for(int i = 0; i < THREADCOUNT; i++)
  {
    ret = pthread_create(&com_tid[i],NULL,Consumer_start,(void*)que);
    if(ret < 0)
    {
      perror("pthread_create Consumer error");
      return 0;
    }

    ret = pthread_create(&pro_tid[i],NULL,Producter_start,(void*)que);
    if(ret < 0)
    {
      perror("pthread_create Producter error");
    }
  }

  //thread wait 
  for(int i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(com_tid[i],NULL);
    pthread_join(pro_tid[i],NULL);
  }

  //释放new出来空间的资源
  delete que;
  que = NULL;
  return 0;
}


