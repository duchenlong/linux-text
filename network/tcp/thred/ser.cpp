#include "tcpser.hpp"
#include <pthread.h>

void* ThreadStart(void* arg)
{
    pthread_detach(pthread_self());
    tcpClass* ts = (tcpClass*)arg;

    while(1)
    {
        string buf;
        ts->Recv(buf);
        cout<<"客户端发来请求，说 ："<<buf<<endl;

        cout<<"给客户端回话 ： ";
        fflush(stdout);
        cin>>buf;
        ts->Send(buf);
    }
    ts->Close();
    delete ts;

    return NULL;
}

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        cout<<"请输入正确的参数 [./ser] [ip] [port]"<<endl;
        return 0;
    }

    string ip = argv[1];
    uint16_t port =  atoi(argv[2]);

    tcpClass ts;

    //创建套接字
    if(!ts.CreateSocket())
    {
        return 0;
    }

    //绑定地址信息
    if(!ts.Bind(ip,port))
    {
        return 0;
    }

    //建立监听
    if(!ts.Listen(10))
    {
        return 0;
    }

    while(1)
    {
        tcpClass* new_ts = new tcpClass();
        struct sockaddr_in peeraddr;
        if(!ts.Accept(new_ts,peeraddr))
        {
            continue;
        }

        cout<<"有一个新的连接 "<<inet_ntoa(peeraddr.sin_addr)<<' '<<ntohs(peeraddr.sin_port)<<endl;

        pthread_t tid;
        int ret = pthread_create(&tid,NULL,ThreadStart,(void*)new_ts);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }

    return 0;
}
