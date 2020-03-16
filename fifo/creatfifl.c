#include <stdio.h>
#include <sys/stat.h>

int main()
{
  int ret = mkfifo("./cfifo",0664);
  if(ret < 0)
  {
    perror("mkfifo error~\n");
    return 0;
  }
  //open
  //read
  //write
  //close

  return 0;
}
