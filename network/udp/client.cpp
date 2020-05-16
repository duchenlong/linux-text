#include "udpClass.hpp"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        //ip port 是服务端的ip port
        cout<<"参数错误 [./client] [ip] [port]"<<endl;
        return 0;
    }

    string ser_ip = argv[1];
    uint16_t ser_port = atoi(argv[2]);

    udpClass udp;
    //创建套接字
    if(!udp.CreateSocket())
        return 0;

    //服务端的地址信息
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(ser_port);
    ser_addr.sin_addr.s_addr = inet_addr(ser_ip.c_str());

    while(1)
    {
        //发送数据
        cout<<"client say : ";
        fflush(stdout);

        string buf;
        cin>>buf;
        udp.Send(buf,&ser_addr);

        //接收数据
        struct sockaddr_in dataaddr;
        udp.Recvfrom(buf,&dataaddr);
        cout<<"server say : "<<buf<<endl;
    }

    udp.Close();

    return 0;
}
