#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>

void sigcallback(int signo)
{
  printf("i am SIGINT [%d] signal\n",signo);
  return ;
}


int main()
{
  signal(SIGINT,sigcallback);
  signal(SIGQUIT,sigcallback);

  while(1)
  {
    sleep(1);
  }

  return 0;
}
