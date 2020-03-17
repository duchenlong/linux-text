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
 
  struct shmid_ds buf;
  shmctl(shmid,IPC_STAT,&buf);
  printf("shmsize: [%ld]\n",buf.shm_segsz);

  void* lp = shmat(shmid,NULL,0);
  if(!lp)
    ERR_EXIT("shmat error");

  //printf("readshm read [%s]\n",(char*)lp);

  while(1)
  {
    printf("readshm read [%s]\n",(char*)lp);
    sleep(1);
  }

  shmdt(lp);
  shmctl(shmid,IPC_RMID,NULL);

  return 0;
}
