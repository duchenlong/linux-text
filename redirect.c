#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int fd = open("./tmp.txt",O_RDWR | O_CREAT,0664);
  if(fd < 0)
  {
    perror("open error\n");
    return 0;
  }
  
  //重定向
  //需求是通过重定向，将本应该输出在标准输出上的内容输出到文件中去
  dup2(fd,1);
  printf("hello linux\n");

  while(1)
  {
    printf("I'm pausing here\n");
    sleep(1);
  }

}
