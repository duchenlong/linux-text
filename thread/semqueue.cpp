#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <vector>

using std::vector;

#define SIZE 1
#define THREADCOUNT 1

class LoopQueue
{
public:
  LoopQueue()
    : _arr(SIZE)
  {
    _Producer = 0;
    _Consumer = 0;
    _Capacity = SIZE;
    //同步生产者，信号量计数器的值和数组的容量一样大
    sem_init(&_SemProducter,0,_Capacity);
    //同步消费者，一开始并没有一个有效元素,所以初始化为0,
    sem_init(&_SemConsumer,0,0);

    //互斥，初始化资源数为1，只能有一个线程同时访问资源
    sem_init(&_Lock,0,1);
  }

  //操作的是生产者
  void Push(int& Data)
  {
    sem_wait(&_SemProducter);

    sem_wait(&_Lock);
    _arr[_Producer] = Data;
    _Producer = (_Producer + 1) % _Capacity;
    sem_post(&_Lock);
    sem_post(&_SemConsumer);
  }
  
  //操作的是消费者
  void Pop(int* Data)
  {
    sem_wait(&_SemConsumer);

    sem_wait(&_Lock);
    *Data = _arr[_Consumer];
    _Consumer = (_Consumer + 1) % _Capacity;
    sem_post(&_Lock);

    sem_post(&_SemProducter);
  }

  ~LoopQueue()
  {
    sem_destroy(&_SemConsumer);
    sem_destroy(&_SemProducter);
    sem_destroy(&_Lock);
  }

private:
  vector<int> _arr;
  size_t _Capacity;
  // Double pointer
  int _Consumer;
  int _Producer;

  //同步
  sem_t _SemProducter;
  sem_t _SemConsumer;

  //互斥
  sem_t _Lock;
};

void* Consumer_start(void* arg)
{
  LoopQueue* que = (LoopQueue*) arg;

  int Data;
  while(1)
  {
    que->Pop(&Data);
    printf("_Consumer [%p]--> [%d]\n",pthread_self(),Data);
  }
  return NULL;
}

void* Producer_start(void* arg)
{
  LoopQueue* que = (LoopQueue*) arg;
  int Data = 1;
  while(1)
  {
    que->Push(Data);
    printf("_Producer [%p] --> [%d]\n",pthread_self(),Data);
    Data++;
  }
  return NULL;
}

int main()
{
  LoopQueue* que = new LoopQueue();
  pthread_t com_tid[THREADCOUNT],pro_tid[THREADCOUNT];

  for(int i = 0; i < THREADCOUNT; i++)
  {
    int ret = pthread_create(&com_tid[i],NULL,Consumer_start,(void*)que);
    if(ret < 0)
    {
      perror("pthread_create consumer");
      return 0;
    }

    ret = pthread_create(&pro_tid[i],NULL,Producer_start,(void*)que);
    if(ret < 0)
    {
      perror("pthread_create Producter");
      return 0;
    }
  }

  for(int i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(com_tid[i],NULL);
    pthread_join(pro_tid[i],NULL);
  }

  delete que;
  que = NULL;

  return 0;
}
