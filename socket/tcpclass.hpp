#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <iostream>
using namespace std;

class tcpClass {
    public:
        tcpClass() {
            _fd = -1;
        }

        bool CreateSocket() {
            // AF_INET ipv4
            // SOCK_STREAM 面向数据流
            // IPPROTO_TCP tcp协议
            _fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(_fd < 0) {
                perror("socket");
                return false;
            }
            return true;
        }

        bool Bind(const string& ip,const uint16_t port) {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            if(bind(_fd,(struct sockaddr*)&addr,sizeof(addr)) < 0) {
                perror("bind");
                return false;
            }
            return true;
        }

        bool Listen(int backlog = 10) {
            if(listen(_fd,backlog) < 0) {
                perror("listen");
                return false;
            }
            return true;
        }

        bool Accept(struct sockaddr_in* cliAddr,tcpClass* tp) {
            socklen_t addrlen = sizeof(struct sockaddr_in);
            int serfa = accept(_fd,(struct sockaddr*)cliAddr,&addrlen);
            if(serfa < 0) {
                perror("accept");
                return false;
            }
            tp->_fd = serfa;   
            return true;
        }

        bool Connect(const string& ip,const uint16_t port) {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            if(connect(_fd,(struct sockaddr*)&addr,sizeof(addr)) < 0) {
                perror("connect");
                return false;
            }
            return true;
        }

        bool Send(const string& data) {
            if(send(_fd,data.c_str(),data.size(),0) < 0) {
                perror("send");
                return false;
            }
            return true;
        }

        bool Recv(string* data) {
            char buf[1024] = {'\0'};
            int datasize = recv(_fd,buf,sizeof(buf) - 1,0);
            if(datasize < 0) {
                perror("recv");
                return false;
            } else if(datasize == 0) {
                cout << " 对方已关闭 " << endl;
                return false;
            }

            *data = buf;
            return true;
        }

        void Close() {
            close(_fd);
            _fd = -1;
        }
    private:
        int _fd;
};