#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <queue>

using std::queue;
using std::cout;
using std::endl;
//threadpool = thread safe queue + threads
//thread safe queue -->  data + function addresses

#define THREADCOUNT 5
#define CAPACITY 10

typedef void* (*Execute_Fun)(int);

//queue data 
class ThreadTask
{
public:
  ThreadTask(int data,Execute_Fun Function)
    :_data(data),
    _Function(Function)
  {}

  //处理数据
  void Run()
  {
    sleep(1);//执行任务耗时1秒
    _Function(_data);
  }
private:
  int _data;
  Execute_Fun _Function;
};

//threadpool
class ThreadPool
{
public:
  ThreadPool(int capacity = CAPACITY,int thread_capacity = THREADCOUNT)
    :_capacity(capacity),
    _thread_capacity(thread_capacity)
  {
    pthread_mutex_init(&_lock,NULL);
    pthread_cond_init(&_cond,NULL);
    
    //创建线程
    bool isCreate = ThreadCreate();
    if(!isCreate)
    {
      cout<<"threadpool create thread error"<<endl;
      _exit(1);
    }
    
    //创建线程成功，初始化状态为未离开，满容量
    _isExit = false;
    _thread_count = _thread_capacity;
  }

  bool push(ThreadTask* tt)
  {
    pthread_mutex_lock(&_lock);
    if(_isExit)
    {
      pthread_mutex_lock(&_lock);
      return false;
    }
    _que.push(tt);
    pthread_mutex_unlock(&_lock);

    //通知线程池中的线程调用消费者函数
    pthread_cond_signal(&_cond);
    return true;
  }

  bool pop(ThreadTask** tt)
  {
    *tt = _que.front();
    _que.pop();
    return true;
  }
  //线程等待
  void ThreadJoin()
  {
    for(size_t i = 0; i < _thread_count; i++)
    {
      pthread_join(_tid[i],NULL); 
    }
  }
  //线程退出时，清空线程池
  void ThreadPoolClear()
  {
    pthread_mutex_lock(&_lock);
    _isExit = true;
    pthread_mutex_unlock(&_lock);

    if(_thread_count > 0)
    {
      //移出PCB等待队列中的所有线程，让他们取消等待，执行退出函数
      pthread_cond_broadcast(&_cond);
    }
  }

private:
  //使用static 取消类中自带的this指针的干扰
  //调用函数只有一个参数，或者使用友元
  static void* ThreadStart(void* arg)
  {
    ThreadPool* tp = (ThreadPool*)arg;
    
    while(1)
    {
      //从队列中取资源必须是互斥的
      pthread_mutex_lock(&(tp->_lock));
      ThreadTask* tt;

      while(tp->_que.empty())
      {
        if(tp->_isExit)
        {
          //退出
          tp->_thread_count--;
          pthread_mutex_unlock(&(tp->_lock));
          pthread_exit(NULL);
        }

        pthread_cond_wait(&(tp->_cond),&(tp->_lock));
      }
      tp->pop(&tt);
      pthread_mutex_unlock(&(tp->_lock));

      //取到资源，调用处理数据的函数去执行该资源的操作
      tt->Run();
      //防止内存泄漏
      delete tt;
    }
  }

  bool ThreadCreate()
  {
    for(size_t i = 0; i < _thread_capacity; i++)
    {
      int ret = pthread_create(&_tid[i],NULL,ThreadStart,(void*)this);
      if(ret < 0)
      {
        perror("pthread_create");
        return false;
      }
    }
    return true;
  }

private:
  queue<ThreadTask*> _que;
  size_t _capacity;
  //互斥
  pthread_mutex_t _lock;
  //同步
  //仅仅是生产者的同步，消费者的功能在自己函数中自带
  pthread_cond_t _cond;

  size_t _thread_capacity;//线程池最大容量
  size_t _thread_count; //当前存在的线程数量
  size_t _tid[THREADCOUNT]; //线程标识符
  bool _isExit; //是否可以退出
};

void* DealData(int data)
{
  cout<<"consum data is [ "<<data<<" ]"<<endl;
  return NULL;
}

int main()
{
  ThreadPool* tp = new ThreadPool();

  for(int i = 1; i <= 50; i++)
  {
    ThreadTask* tt = new ThreadTask(i,DealData);
    tp->push(tt);
  }

  //等待线程退出
  sleep(20);//模拟20秒一定执行完
  tp->ThreadPoolClear();
  tp->ThreadJoin();
  delete tp;

  return 0;
}
