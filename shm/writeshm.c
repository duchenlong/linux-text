#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

#define shm_key 0x9999999

#define ERR_EXIT(m)\
do\
{\
  perror(m);\
  exit(EXIT_FAILURE);\
}while(0)

int main()
{
  int shmid = shmget(shm_key,1024,IPC_CREAT | 0664);
  if(shmid < 0)
    ERR_EXIT("shmget error");

  void* lp = shmat(shmid,NULL,0);
  if(!lp)
    ERR_EXIT("shmat error");

 //sprintf((char*)lp,"%s-%d","hello linux",66);
 
  int i = 0;
  while(1)
  {
    sprintf((char*)lp,"%s-%d","hello linux",i);
    sleep(1);
    i++;
  }
  //shmdt(lp);
  //shmctl(shmid,IPC_RMID,NULL);
}
