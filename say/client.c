#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define ERR_EXIT(m)\
do\
{\
  perror(m);\
  exit(EXIT_FAILURE);\
}while(0)

int main()
{
  int wfd = open("cfifo",O_WRONLY);
  if(wfd < 0)
    ERR_EXIT("open cfifo");

  char buf[1024] = {'\0'};
  while(1)
  {
    buf[0] = 0;
    printf("please enter# ");
    fflush(stdout);
    ssize_t s = read(0,buf,sizeof(buf) - 1);
    if(s > 0)
    {
      buf[s] = 0;
      write(wfd,buf,strlen(buf));
    }
    else if(s <= 0)
    {
      ERR_EXIT("read error");
    }
  }
  
  close(wfd);
  return 0;
}
