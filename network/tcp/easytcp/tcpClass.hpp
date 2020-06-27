#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class tcpClass
{
public:
    tcpClass()
    {
        _sock = -1;
    }

    //创建套接字
    bool CreateSocket()
    {
        //ipv4  面向数据流  TCP协议
        _sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(_sock < 0)
        {
            perror("socket error");
            return false;
        }
        //地址复用
        int i = 1;
        setsockopt(_sock,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(int));
        return true;
    }

    //绑定地址信息
    bool Bind(string& ip,uint16_t port)
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        
        //因为addr是结构体类型，所以可以直接sizeof求大小
        int ret = bind(_sock, (struct sockaddr*)&addr,
                sizeof(addr));
        if(ret < 0)
        {
            perror("bind error");
            return false;
        }
        return true;
    }

    //侦听
    bool Listen(int backlog = 10)
    {
        int ret = listen(_sock,backlog);
        if(ret < 0)
        {
            perror("listen error");
            return false;
        }
        return true;
    }

    //获取连接
    //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    bool Accept(struct sockaddr_in* cliAddr,tcpClass* tp)
    {
        socklen_t addrlen = sizeof(struct sockaddr_in);
        //函数返回值是客户端的sockfd,服务端需要这个sockfd
        int serfd = accept(_sock,(struct sockaddr*)cliAddr,&addrlen);
        if(serfd < 0)
        {
            perror("accept error");
            return false;
        }
        (*tp)._sock = serfd;
        return true;
    }

    //发起连接  client
    bool Connect(string& ip,uint16_t port)
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        int ret = connect(_sock,(struct sockaddr*)&addr,
                sizeof(addr));
        if(ret < 0)
        {
            perror("connect error");
            return false;
        }
        return true;
    }

    //发送数据
    bool Send(string& data)
    {
        int ret = send(_sock,data.c_str(),data.size(),0);
        if(ret < 0)
        {
            perror("send perror");
            return false;
        }
        return true;
    }

    //接收数据 data --> 接收的数据存放的地方
    bool Recv(string& data)
    {
        char buf[1024] = {'\0'};
        //预留一个'\0'的位置
        int datasize = recv(_sock,buf,sizeof(buf)-1,0);
        if(datasize < 0)
        {
            perror("recv error");
            return false;
        }
        else if(datasize == 0)
        {
            cout<<"另一个端口已经关闭了连接"<<endl;
            return false;
        }

        //正常接收到数据
        data.assign(buf,datasize);
        return true;
    }

    //关闭套接字
    void Close()
    {
        close(_sock);
        _sock = -1;
    }

private:
    int _sock;//套接字描述符
};
