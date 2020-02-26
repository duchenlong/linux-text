/* 1.父进程从标准输入中读取用户输入的命令
 * 2.需要创建一个子进程，让子进程执行命令程序
 * 3.父进程需要等待，等待子进程的退出，然后循环去获取命令
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <stdlib.h>


char command[1025] = {'\0'};

int get_command()
{
  memset(command,'\0',sizeof(command));
  printf("[duchenlong@localhost ~]$ ");
  fflush(stdout);

  if(fgets(command,sizeof(command)-1,stdin) == NULL)
  {
    printf("fgets error\n");
    return 0;
  }
  
  printf("command : %s\n",command);
  return 1;
}

void execute(char* argv[])
{
  if(!argv[0])
  {
    printf("execute error!\n");
    return ;
  }
  
  pid_t pid = fork();
  if(pid < 0)
  {
    printf("fork pid error!\n");
  }
  else if(pid == 0)
  {
    //child 进程程序替换
    execvp(argv[0],argv);
    exit(0);
  }
  else
  {
    //father 进程等待
    waitpid(pid,NULL,0);
  }
}

void my_split(char* str)
{
  if(!str || (*str == '\0'))
  {
    printf("command error!\n");
    return ;
  }

  char* argv[1025] = {0};
  int len = 0;
  while(*str)
  {
    char* src = str;
    while(*str && !isspace(*str))
    {
      str++;
    }
    if(*str)
    {
      *str = '\0';
      str++;
    }
    //printf("src = %s ",src);
    argv[len++] = src;
    //printf("argv[%d] = %s \n",len-1,argv[len-1]);
  }

  argv[len] = NULL;

  execute(argv);
}

int main()
{
  printf("Welcome to minishell!\n");
  printf("quit plase input : Q\n");
  while(1)
  {
    if(get_command() == 0)
    {
      continue;
    }
    
    if(command[0] == 'Q')
    {
      printf("The forthcoming minishell!\n");
      break;
    }
    my_split(command);
  }

  return 0;
}
