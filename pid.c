#include<stdio.h>
#include<unistd.h>

int main()
{

   //创建子进程
   //系统调用函数 fork()
   pid_t pid=fork();

  if(pid < 0)
  {  
    //没有内存时可能会导致此结果；
    //创建PCB 是需要消耗内存的
    perror("fork\n");
    return 0;
  }
  else if(pid == 0)
  {
    //child
    printf("i am child :[%d] - [%d]\n",getpid(),getppid());
  }
  else //pid > 0
  {
    //father
    printf("i am father :[%d] - [%d]\n",getpid(),getppid());
  }
  //获取当前进程的pid,使用getpid
  //获取当前进程的父进程的pid,使用getppid
  return 0;
}
