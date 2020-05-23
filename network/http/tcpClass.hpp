#pragma once 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

class TcpClass
{
    public:
        TcpClass()
            :_sockfd(-1)
        {}

        //创建套接字
        bool CreateSocket()
        {
            _sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(_sockfd < 0)
            {
                perror("socket");
                return false;
            }
            return true;
        }

        //绑定地址信息
        bool Bind(string& ip,uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret = bind(_sockfd,(struct sockaddr*)&addr,sizeof(addr));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        //监听
        bool Listen(int backlog = 10)
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
        bool Accept(struct sockaddr_in& addr,TcpClass& ts)
        {
            socklen_t addrlen = sizeof(addr);
            int ret = accept(_sockfd,(struct sockaddr*)&addr,&addrlen);
            if(ret < 0)
            {
                perror("accept");
                return false;
            }
            ts._sockfd = ret;
            return true;
        }

        //发起连接，客户端
        bool Connect(string& ip,uint16_t port)
        {
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
            int ret = send(_sockfd,data.c_str(),data.size(),0);
            if(ret < 0)
            {
                perror("send");
                return false;
            }
            return true;
        }

        //接收数据
        bool Recv(string& data)
        {
            char buf[1024] = {'\0'};
            int ret = recv(_sockfd,buf,sizeof(buf)-1,0);
            if(ret < 0)
            {
                perror("recv");
                return false;
            }
            else if(ret == 0)
            {
                perror("对端关闭了连接");
                return false;
            }
            data.assign(buf,ret);
            return true;
        }

        void Close()
        {
            close(_sockfd);
            _sockfd = -1;
        }
    private:
        int _sockfd;
};
