#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcallback(int signo)
{
  printf("signal = [%d] \n",signo);
}

int main()
{
  signal(2,sigcallback);//可靠信号
  signal(40,sigcallback);//非可靠信号

  sigset_t set,oldset;
  sigemptyset(&set);//set初始化全为0
  sigemptyset(&oldset);//oldset初始化为0

  sigfillset(&set);//set全为1
  sigprocmask(SIG_BLOCK,&set,&oldset);//将所有信号置为阻塞状态
  getchar();//处理回车键，然后运行设置非阻塞的函数
  sigprocmask(SIG_UNBLOCK,&set,NULL);//将所有信号置为非阻塞状态

  while(1)
  {
    sleep(1);
  }
  return 0;
}
