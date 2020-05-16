#include "tcpser.hpp"

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        cout<<"请输入正确的参数 [./cli] [ip] [port]"<<endl;
        return 0;
    }

    string ip = argv[1];
    uint16_t post = atoi(argv[2]);

    tcpClass tc;

    //创建套接字
    if(!tc.CreateSocket())
    {
        return 0;
    }

    //建立连接
    if(!tc.Connect(ip,post))
    {
        return 0;
    }
    
    while(1)
    {
        cout<<"向服务端发送的数据 : ";
        fflush(stdout);
        string buf;
        cin>>buf;
        tc.Send(buf);

        tc.Recv(buf);
        cout<<"服务端回话说 : "<<buf<<endl;
    }
    tc.Close();
    return 0;
}
