#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int count = 0;
void sigcallback(int signo)
{
 // count++;
  printf("i recv sig no is [%d],and count = [%d]\n",signo,count);
}

int main()
{
  signal(2,sigcallback);

  while(count < 20)
  {
    count++;
    printf("i am main thread : [%d]\n",count);
    sleep(1);
  }
}
