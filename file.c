#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{

  //关闭标准输入
  close(0);
  int fd = open("./tmp.txt",O_RDWR | O_CREAT | O_APPEND,0664);
  if(fd < 0)
  {
    perror("open\n");
    return 0;
  }
  
  //write
  int ret = write(fd,"hello linux\n ",11);
  if(ret < 0)
  {
    perror("write error\n");
    return 0;
  }

  lseek(fd,5,SEEK_SET);
  //read
  char buf[1024] = {'\0'};
  ret = read(fd,buf,sizeof(buf)-1);

  if(ret < 0)
  {
    perror("read error\n");
    return 0;
  }
  else if(ret == 0)
  {
    printf("read size [%d]\n",ret);
  }

  printf("fd:[%d]\n",fd);
/*
  while(1)
  {
    printf("I'm pausing here\n");
    sleep(1);
  }
*/
  printf("%s\n",buf);
  close(fd);
  return 0;
}
