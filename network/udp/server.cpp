#include "udpClass.hpp"

int main(int argc, char* argv[])
{
    //所需要的三个参数  ./server ip port
    if(argc != 3)
    {
        cout<<"所输入的参数不正确，应该为：[./server] [ip] [port]"<<endl;
        return 0;
    }
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    udpClass udp;
    //创建套接字
    if(!udp.CreateSocket())
        return 0;

    //绑定ip和端口信息
    if(!udp.Bind(ip,port))
        return 0;

    while(1)
    {
        //接收数据
        string buf;
        struct sockaddr_in cliaddr;//对端地址信息
        udp.Recvfrom(buf,&cliaddr);

        cout<<"client say : "<<buf<<endl;

        //发送数据
        cout<<"server respond : ";
        fflush(stdout);//刷新缓冲区
        cin>>buf;
        udp.Send(buf,&cliaddr);
    }

    udp.Close();
    return 0;
}
