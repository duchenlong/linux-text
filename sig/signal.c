#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction oldact;

void sigcallback(int signo)
{
  printf("signo = [%d]\n",signo);
  sigaction(2,&oldact,NULL);//按第二次ctrl + c使程序结束
}

int main()
{
  struct sigaction newact;
  newact.sa_handler = sigcallback;
  //给位图的接口都初始化为0
  sigemptyset(&newact.sa_mask);
  newact.sa_flags = 0;

  sigaction(2,&newact,&oldact);

  while(1)
  {
    sleep(1);
  }

  return 0;
}
