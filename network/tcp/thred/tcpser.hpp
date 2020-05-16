#pragma once 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;
using std::endl;

class tcpClass
{
    public:
        tcpClass()
        {
            _socket = -1;
        }

        //创建套接字
        bool CreateSocket()
        {
            _socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(_socket < 0)
            {
                perror("socket");
                return false;
            }
            return true;
        }

        //绑定地址信息
        bool Bind(string& ip,uint16_t post)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(post);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret = bind(_socket,(struct sockaddr*)&addr,sizeof(struct sockaddr_in));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        //建立监听
        bool Listen(int bocklog = 10)
        {
            int ret = listen(_socket,bocklog);
            if(ret < 0)
            {
                perror("listen");
                return false;
            }
            return true;
        }

        //接收连接
        bool Accept(tcpClass* tc,struct sockaddr_in& addr)
        {
            socklen_t addrlen = sizeof(struct sockaddr_in);
            
            int ret = accept(_socket,(struct sockaddr*)&addr,&addrlen);
            if(ret < 0)
            {
                perror("accept");
                return false;
            }
            tc->_socket = ret;
            return true;
        }

        //建立连接
        bool Connect(string& ip,uint16_t post)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(post);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret = connect(_socket,(struct sockaddr*)&addr,sizeof(struct sockaddr_in));
            if(ret < 0)
            {
                perror("connect");
                return false;
            }
            return true;
        }

        //接收数据
        bool Recv(string& date)
        {
            char buf[1024] = {'\0'};
            int ret = recv(_socket,buf,sizeof(buf)-1,0);
            if(ret < 0)
            {
                perror("recv");
                return false;
            }
            else if(ret == 0)
            {
                cout<<"对端已经关闭连接"<<endl;
                return false;
            }

            date.assign(buf,ret);
            return true;
        }

        //发送数据
        bool Send(string& buf)
        {
            int ret = send(_socket,buf.c_str(),sizeof(buf)-1,0);
            if(ret < 0)
            {
                perror("send");
                return false;
            }
            return true;
        }

        //关闭连接
        void Close()
        {
            close(_socket);
            _socket = -1;
        }
    private:
        int _socket;
};
