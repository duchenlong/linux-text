#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigcallback(int sigo)
{
  printf(" recv signo is [%d]\n",sigo);
  wait(NULL);
}

int main()
{
  signal(SIGCHLD,sigcallback);
  signal(SIGCHLD,sigcallback);
  
  pid_t pid = fork();
  if(pid < 0)
  {
    printf("fork error\n");
    return 0;
  }
  else if(pid == 0)
  {
    //child
    sleep(3);
    printf("i am child, now exit\n");
    _exit(0);
  }
  else 
  {
    //father
    while(1)
    {
      sleep(1);
      printf("i am father\n");
    }
  }

  return 0;
}
