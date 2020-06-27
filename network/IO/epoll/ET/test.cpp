/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：test.cpp
*   创 建 者：dcl
*   创建日期：2020年06月20日
*   描    述：
*
================================================================*/

#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

inline void slove(struct epoll_event* fd_arr,int ret)
{
    for(int i = 0; i < ret; i++)
        if(fd_arr[i].data.fd == 0)
        {
            string ans = "";
            while(1)
            {
                char buf[3] = {'\0'};
                ssize_t readsize = read(0,buf,sizeof(buf) - 1);
                if(readsize < 0)
                {
                    //说明数据读完了
                    if(errno == EAGAIN || errno == EWOULDBLOCK)
                        break;
                    
                    perror("read");
                    break;
                }

                ans += buf;
                break;
                if(readsize < (ssize_t)sizeof(buf) - 1)
                   break; //数据读完了
            }

            if(ans != "")   cout<<"read data: "<<ans<<endl;
        }

}

int main()
{
    //设置文件描述符属性为非阻塞
    //int fcntl(int fd, int cmd, ... /* arg */ );
    int flag = fcntl(0,F_GETFL);
    fcntl(0,F_SETFL,flag | O_NONBLOCK);

    //创建epoll操作句柄
    int epoll_fd = epoll_create(10);
    if(epoll_fd < 0)
    {
        perror("epoll_create");
        return 0;
    }

    //添加文件描述符
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = 0;
    int ret = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,0,&ev);
    if(ret < 0)
    {
        perror("epoll_ctl");
        return 0;
    }

    while(1)
    {
        struct epoll_event fd_arr[10];
        ret = epoll_wait(epoll_fd,fd_arr,sizeof(fd_arr) / sizeof(fd_arr[0]),-1);
        if(ret < 0)
        {
            perror("epoll_wait");
            continue;
        }

        slove(fd_arr,ret);

    }


    return 0;
}

