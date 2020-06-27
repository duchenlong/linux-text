#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <poll.h>

using namespace std;

int main()
{
	//创建一个struct pollfd结构体，关心0号文件描述符，标准输入
	//监视可读事件
    struct pollfd poll_fd;
    poll_fd.fd = 0;
    poll_fd.events = POLLIN;
	
	//轮询遍历
    while(1)
    {
        int ret = poll(&poll_fd,1,1000);
        if(ret < 0)//poll出错
        {
            perror("poll");
            sleep(3);
            continue;
        }
        else if(ret == 0)//监控超时
        {
            cout<<"poll timeout"<<endl;
            continue;
        }
        else if(poll_fd.revents == POLLIN)//当发送的事件时可读事件时
        {
			//读取数据
            char buf[1024] = {'\0'};
            read(0,buf,sizeof(buf) - 1);
            cout<<"input : "<<buf<<endl;
        }
    }

    return 0;
}
