#pragma once 

#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> // 指定套接字所属的协议
#include <arpa/inet.h> //点分十进制转为长整型数据
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;

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
            addr.sin_port = htons(port);//小端字节序转为大端字节序
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            
            int ret = bind(_sockfd,(struct sockaddr*)&addr,sizeof(addr));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        //侦听
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

        //接收连接
        bool Accept(TcpClass& sock,struct sockaddr_in* addr)
        {
           // struct sockaddr_in peeraddr;
            socklen_t peerlen = sizeof(struct sockaddr_in);
            int ret = accept(_sockfd,(struct sockaddr*)&addr,&peerlen);
            if(ret < 0)
            {
                perror("accept");
                return false;
            }
            sock._sockfd = ret;

           // if(addr != NULL)
           // {
           //     memcpy(addr,&peeraddr,peerlen);
           // }
            return true;
        }

        //发起连接
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
        bool Send(string& date)
        {
            int ret = send(_sockfd,date.c_str(),date.size(),0);
            if(ret < 0)
            {
                perror("send");
                return false;
            }
            return true;
        }

        //接收数据
        bool Recv(string& date)
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
                cout<<"对端已经关闭了连接"<<endl;
                return false;
            }
        
            date.assign(buf,ret);
            return true;
        }

        //关闭
        void Close()
        {
            close(_sockfd);
            _sockfd = -1;
        }
    private:
        int _sockfd;
};
