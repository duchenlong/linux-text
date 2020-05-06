#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <string>
#include <pthread.h>
#include <iostream>

using std::cout;
using std::vector;
using std::string;
using std::endl;

volatile int ticket = 1000;
pthread_rwlock_t rwlock;

struct ThreadAttr
{
    pthread_t tid;
    size_t id;
};

void init_rwlock(int state)
{
    //read priority
    if(state == 0)
    {
        pthread_rwlockattr_t attr;
        pthread_rwlockattr_init(&attr);
        pthread_rwlockattr_setkind_np(&attr,PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
        pthread_rwlock_init(&rwlock,&attr);
        pthread_rwlockattr_destroy(&attr);
    }
    else //read priority  && write hunger
    {
        pthread_rwlock_init(&rwlock,nullptr);
    }
}

void join_threads(vector<ThreadAttr>& vec)
{
    for(auto& eoch : vec)
    {
        pthread_join(eoch.tid,nullptr);
    }
}

void* readStart(void* arg)
{
    ThreadAttr* info = (ThreadAttr*)arg;
    while(1)
    {
        pthread_rwlock_rdlock(&rwlock);
        if(ticket <= 0)
        {
            pthread_rwlock_unlock(&rwlock);
            break;
        }
        cout<<"thread reader: "<<info->id<<" : "<<ticket<<endl;
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
    return nullptr;
}

void* writeStart(void* arg)
{
    ThreadAttr* info = (ThreadAttr*) arg;
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        if(ticket <= 0)
        {
            pthread_rwlock_unlock(&rwlock);
            break;
        }
        cout<<"thread write "<<info->id<<" : "<<--ticket<<endl;
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
    return nullptr;
}

int main()
{
    const size_t reader_nr = 1000;
    const size_t writer_nr = 2000;

    vector<ThreadAttr> readers(reader_nr); 
    vector<ThreadAttr> writers(writer_nr);

    init_rwlock(0);//0-->read priority 1--> write priority
    for(size_t i = 0; i < readers.size(); i++)
    {
        readers[i].id = i;
        pthread_create(&readers[i].tid,nullptr,readStart,(void*)&readers[i]);
    }

    for(size_t i = 0; i < writers.size(); i++)
    {
        writers[i].id = i;
        pthread_create(&writers[i].tid,nullptr,writeStart,(void*)&writers[i]);
    }

    //thread wait 
    join_threads(writers);
    join_threads(readers);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}
