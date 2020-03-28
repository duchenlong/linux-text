#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile int g_val = 1;

void sigcallback(int sigo)
{
  g_val = 0;
  printf("signal [%d],[%d]\n",sigo,g_val);
}

int main()
{
  signal(2,sigcallback);

  while(g_val)
  {
  }

  return 0;
}
