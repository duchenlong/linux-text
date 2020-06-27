/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：test.cpp
*   创 建 者：dcl
*   创建日期：2020年06月20日
*   描    述：
*
================================================================*/

#include <unistd.h>
#include <cstdio>
#include <sys/epoll.h>
#include <iostream>
using namespace std;

int main()
{
    int epollfd = epoll_create(10);
    if(epollfd < 0)
    {
        perror("epoll_create");
        return 0;
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;//可读事件
    ev.data.fd = 0;
    //int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    //添加一个文件描述符到红黑树中
    int ret = epoll_ctl(epollfd,EPOLL_CTL_ADD,0,&ev);
    if(ret < 0)
    {
        perror("epoll_ctl");
        return 0;
    }

    while(1)
    {
        struct epoll_event fd_arr[10];
        //int epoll_wait(int epfd, struct epoll_event *events,
        //                      int maxevents, int timeout);
        int ret = epoll_wait(epollfd,fd_arr,sizeof(fd_arr) / sizeof(fd_arr[0]),3000);
        if(ret < 0)
        {
            perror("epoll_wait");
            continue;
        }
        else if(ret == 0)
        {
            cout<<"timeout"<<endl;
            sleep(1);
            continue;
        }
        cout<<"---"<<ret<<endl;
        //文件描述符被触发
        for(int i = 0; i < ret; i++)
        {
            if(fd_arr[i].data.fd == 0)
            {
                char buf[3] = {'\0'};
                read(fd_arr[i].data.fd,buf,sizeof(buf) - 1);
                cout<<"input : "<<buf<<endl;
            }
        }
    }
    

    return 0;
}
