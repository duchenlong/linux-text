#include "Tcpsvr.hpp"
#include <cstdlib>
int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        cout<<"请输入正确的参数 [./client] [ip] [port]"<<endl;
        return 0;
    }

    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    Tcpsvr tcp;
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
        buf.clear(); 
        //等待接收数据
        
        if(!tcp.Recv(buf))
        {
            cout<<"我方程序退出"<<endl;
            break;
        }
        cout<<"服务端说 ： "<<buf<<endl;
    }
    tcp.Close();

    return 0;
}
