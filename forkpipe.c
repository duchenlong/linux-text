#include <stdio.h>
#include <unistd.h>

int main()
{
  int fd[2];
  int ret = pipe(fd);
  if(ret < 0)
  {
    perror("pipe error!");
    return 0;
  }
  
  //创建一个子进程
  ret = fork();
  if(ret < 0)
  {
    perror("fork error!");
    return 0;
  }
  else if(ret == 0)
  {
    //child 读
   // sleep(5);

    char buf[1024] = {'\0'};
    //read(fd[0],buf,sizeof(buf) - 1);
     //printf("i am child i read buf = [%s]\n",buf);
    //1.管道中没有数据，read 就会阻塞
    //2.管道中的数据被拿走了
    read(fd[0],buf,sizeof(buf) - 1);
    
    while(1)
    {
      sleep(1);
    }
  }
  
  //father 写
  // sleep(60);
 // write(fd[1],"hello linux",11);
  
  //查看写多少字节可以写满
  int count = 0;
  while(1)
  {
    write(fd[1],"6",1);
    //int status =  write(fd[1],"6",1);
    //if(status != 1)
    //{
      //printf("write size status = [%d]\n",status);
      //break;
    //}
    count++;
    printf("count = [%d]\n",count);
  }

  close(fd[0]);
  close(fd[1]);
  return 0;
}
