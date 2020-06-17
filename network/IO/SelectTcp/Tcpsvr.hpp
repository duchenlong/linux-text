#pragma once 

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <iostream>
#include <string>

using namespace  std;

class Tcpsvr 
{
    public:
        Tcpsvr()
            :_sockfd(-1)
        {}

        //创建套接字
        bool CreateSocket()
        {
            int ret = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(ret < 0)
            {
                perror("socket");
                return false;
            }
            _sockfd = ret;

            //解决地址复用问题
            int  i = 1;
            setsockopt(_sockfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(int));
            return true;
        }

        //绑定地址信息
        bool Bind(const string& ip,uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret = bind(_sockfd,(struct sockaddr*)&addr,sizeof(struct sockaddr_in));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        //建立监听
        bool Listen(int backlog = 5)
        {
            int ret = listen(_sockfd,backlog);
            if(ret < 0)
            {
                perror("listen");
                return false;
            }
            return true;
        }

        //获取连接
        bool Accept(struct sockaddr_in* addr,Tcpsvr& ts)
        {
            //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

            socklen_t addrLen = sizeof(struct sockaddr_in);
            int serFd = accept(_sockfd,(struct sockaddr*)addr,&addrLen);
            if(serFd < 0)
            {
                perror("accept");
                return false;
            }

            ts._sockfd = serFd;
            return true;
        }

        //发起连接
        bool Connect(string& ip,uint16_t port)
        {
            //int connect(int sockfd, const struct sockaddr *addr,
            //                   socklen_t addrlen);
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret = connect(_sockfd,(struct sockaddr*)&addr,sizeof(addr));
            if(ret < 0)
            {
                perror("connect");
                return false;
            }
            return true;
        }

        //发送数据
        bool Send(string& data)
        {
            // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
            ssize_t ret  = send(_sockfd,data.c_str(),data.size(),0);
            if(ret == 0)
            {
                perror("send");
                return false;
            }
            return true;
        }

        //接收数据
        bool Recv(string& data)
        {
            // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
            char buf[1024] = {'\0'};
            ssize_t ret = recv(_sockfd,buf,sizeof(buf) - 1,0);
            if(ret < 0)
            {
                perror("recv");
                return false;
            }
            else if (ret == 0)
            {
                cout<<"对方关闭了连接"<<endl;
                return false;
            }

            //ret 就是所接收数据的大小
            data.assign(buf,ret);
            return true;
        }

        //关闭套接字
        void Close()
        {
            close(_sockfd);
            _sockfd = -1;
        }

        //设置套接字
        inline void SetFd(int fd)
        {
            _sockfd = fd;
        }

        //获得套接字
        inline int GetFd()
        {
            return _sockfd;
        }
    private:
        int _sockfd;
};
