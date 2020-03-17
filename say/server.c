#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

#define ERR_EXIT(m)\
do\
{\
  perror(m);\
  exit(EXIT_FAILURE);\
}while(0)

int main()
{
  umask(0);
  if(mkfifo("cfifo",0644) < 0)
    ERR_EXIT("mkfifo error");

  int rfd = open("cfifo",O_RDONLY);
  if(rfd < 0)
    ERR_EXIT("open cfifo error");

  char buf[1024] = {'\0'};
  while(1)
  {
    buf[0] = 0;
    printf("please wait ....\n");
    ssize_t s = read(rfd,buf,sizeof(buf) - 1);
    if(s > 0)
    {
      buf[s - 1] = 0;
      printf("client say#  %s\n",buf);
    }
    else if(s == 0)
    {
      printf("client quit,exit now!\n");
      exit(EXIT_SUCCESS);
    }
    else
    {
      ERR_EXIT("read error");
    }
  }

  close(rfd);
  return 0;
}
