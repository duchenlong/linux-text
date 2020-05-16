#pragma once 
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class udpClass
{
public:
    //构造函数、
    udpClass()
    {
        _sock = -1;
    }

    //socket 创建套接字
    bool CreateSocket()
    {
        //int socket(int domain, int type, int protocol);
        //选择ipv4-->AF_INET  面向数据报--> SOCK_DGRAM UDP协议-->IPPROTO_UDP 
        _sock = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
        if(_sock < 0)
        {
            //创建套接字失败
            perror("socket error ");
            return false;
        }
        return true;
    }

    // bind 绑定Ip地址 端口信息
    bool Bind(string& ip,uint16_t port)
    {
        //int bind(int sockfd, const struct sockaddr *addr,
        //       socklen_t addrlen);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;//按照ipv4的格式进行解析
        addr.sin_port = htons(port);//小端字节序转为大端字节序，16位
        //inet_addr--> 点分十进制的ip转为uint32格式, 将主机字节序转为网络字节序
        //ip.c_str --> string 类型转为 char* 类型
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        int ret =  bind(_sock,(struct sockaddr*)&addr,sizeof(struct sockaddr_in));
        if(ret < 0)
        {
            perror("bind error ");
            return false;
        }
        return true;
    }

    //send 发送数据
    bool Send(string& data, struct sockaddr_in* addr)
    {
        //ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
        //       const struct sockaddr *dest_addr, socklen_t addrlen);
        int sendsize = sendto(_sock,data.c_str(),data.size(),0,
                (struct sockaddr*)addr,sizeof(struct sockaddr_in));
        if(sendsize < 0)
        {
            perror("send error ");
            return false;
        }
        return true;
    }

    //recvfrom 接收数据
    bool Recvfrom(string& buf,struct sockaddr_in* addr)
    {
        //ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
        //      struct sockaddr *src_addr, socklen_t *addrlen);
        char data[1024] = {'\0'};
        socklen_t addrlen = sizeof(struct sockaddr_in);
        int recvsize = recvfrom(_sock,data,sizeof(data),0,
                (struct sockaddr*)addr, &addrlen);
        if(recvsize < 0)
        {
            perror("recvfrom error ");
            return false;
        }
        //拷贝接收的数据i
        //从data数组中截取前recvsize个字符
        buf.assign(data,recvsize);
        
        return true;
    }

    //close
    void Close()
    {
        close(_sock);
        _sock = -1;
    }

private:
    int _sock;//套接字描述符
};
