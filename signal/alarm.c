#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    alarm(3);//一个三秒的闹钟   
    int sec = 1;
    while(1)
    {
      printf("当前为第 [%d] 秒\n",sec);
      sec++;
      sleep(1);                     
    }
    return 0;
}
