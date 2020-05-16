#include "tcpClass.hpp"

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        cout<<"请输入正确的参数 [./server] [ip] [port]"<<endl;
        return 0;
    }

    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    tcpClass tcp;
    //创建套接字
    if(!tcp.CreateSocket())
    {
        return 0;
    }
    
    //绑定地址信息 ip port 
    if(!tcp.Bind(ip,port))
    {
        return 0;
    }

    //建立监听
    if(!tcp.Listen())
    {
        return 0;
    }

    tcpClass ser_tcp;//新创建出来的socket
    
    struct sockaddr_in client_addr;
    //成功建立连接
    if(!tcp.Accept(&client_addr,&ser_tcp))
    {
       return 0;
    }

    while(1)
    {
        string buf;
        ser_tcp.Recv(buf);
        cout<<"服务端有话说 ： "<<buf<<endl;

        cout<<"给客户端回话 ： "<<endl;
        fflush(stdout);
        cin>>buf;
        ser_tcp.Send(buf);
    }
    ser_tcp.Close();
    tcp.Close();
    return 0;
}
