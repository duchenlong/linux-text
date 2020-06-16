#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

void SetNoBlock(int fd)
{
    //获得文件描述符的状态标识
    int ret = fcntl(fd,F_GETFL);
    if(ret < 0)
    {
        perror("fcntl");
        return ;
    }
    //设置文件描述符的状态，并加上一个非阻塞状态
    fcntl(fd,F_SETFL,ret | O_NONBLOCK);
}

int main()
{
    SetNoBlock(0);//0 -- 标准输入描述符

    while(1)
    {
        char buf[1024] = {'\0'};
        ssize_t read_size = read(0,buf,sizeof(buf) - 1);
        if(read_size < 0)
        {
            perror("read");
            sleep(3);

            continue;
        }

        cout<<"输入了 ： "<<buf<<endl;
    }

    return 0;
}
