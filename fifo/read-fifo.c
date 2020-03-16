#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#define ERR_EXIT(m)\
do\
{\
  perror(m);\
  exit(EXIT_FAILURE);\
}while(0)

int main(int argc,char* argv[])
{
  int outfifo = open("abc.bak",O_WRONLY | O_CREAT | O_TRUNC,0644);
  if(outfifo == -1)
    ERR_EXIT("open file");

  int infifo = open("cfifo",O_RDONLY);
  if(infifo == -1)
    ERR_EXIT("open fifo");

  char buf[1024] = {'\0'};
  int n;
  while((n = read(infifo,buf,1024)) > 0)
  {
    write(outfifo,buf,n);
  }
  close(infifo);
  close(outfifo);
  unlink("cfifo");

  return 0;
}
