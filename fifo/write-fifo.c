#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define ERR_EXIT(m)\
do\
{\
  perror(m);\
  exit(EXIT_FAILURE);\
}while(0);

int main(int argc,char* argv[])
{
  mkfifo("cfifo",0644);
  int incfifo = open("abc",O_RDONLY | O_CREAT);
  if(incfifo == -1)
  {
    ERR_EXIT("open file");
  }

  int outcfifo = open("cfifo",O_WRONLY);
  if(outcfifo == -1)
  {
    ERR_EXIT("open fifo");
  }

  char buf[1024] = {'\0'};
  int n;
  while((n = read(incfifo,buf,1024)) > 0)
  {
    write(outcfifo,buf,n);
  }

  close(incfifo);
  close(outcfifo);

  return 0;
}
