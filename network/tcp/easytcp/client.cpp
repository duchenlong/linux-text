#include "tcpClass.hpp"

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        cout<<"请输入正确的参数 [./client] [ip] [port]"<<endl;
        return 0;
    }

    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    tcpClass tcp;
    if(!tcp.CreateSocket())
    {
        return 0;
    }

    if(!tcp.Connect(ip,port))
    {
        return 0;
    }

    while(1)
    {
        cout<<"请输入想给服务端说的话 ： ";
        fflush(stdout);
        string buf;
        cin>>buf;
        tcp.Send(buf);
        
        //等待接收数据
        //tcp.Recv(buf);
        //cout<<"服务端说 ： "<<buf<<endl;
    }
    tcp.Close();

    return 0;
}
