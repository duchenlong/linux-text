#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
  printf("i am finfshed\n");
  kill(getpid(),2);

  while(1)
  {
    printf("如果打印到这里，就说明有问题!\n");
    sleep(1);
  }

  return 0;
}
