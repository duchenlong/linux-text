#include "tcpclass.hpp"
#include <sstream>

using namespace std;

int main(int argc,char* argv[]) {
    if(argc != 2) {
        cout << " 请输入端口号 "  << endl;
        return 0;
    }
    string ip = "192.168.137.128";
    uint16_t port = atoi(argv[1]);

    tcpClass tcp;
    // 创建套接字
    if(!tcp.CreateSocket())
        return 0;
    
    // 绑定地址信息
    if(!tcp.Bind(ip,port))
        return 0;
    
    // 建立监听
    if(!tcp.Listen())
        return 0;
    
    tcpClass ser_ts;
    int cnt = 1;
    while(1) {
        struct sockaddr_in cliaddr;
        // 得到连接客户端的套接字
        if(!tcp.Accept(&cliaddr,&ser_ts))
            return 0;
        
        string buf;
        ser_ts.Recv(&buf);

        char t[1024] = {'\0'};
        sprintf(t,"<html><h1>Nginx 192.168.137.128:%d, %d </h1></html>",port,cnt);
        cnt ++;

        string body = t;
        
        stringstream ss;
        ss << "HTTP/1.1 200 OK\r\n";
        ss << "Content-Type: text/html\r\n";
        ss << "Content-Length: " << body.size() << "\r\n";
        ss << "\r\n";
        string header = ss.str();

        ser_ts.Send(header);
        ser_ts.Send(body);
    }
    ser_ts.Close();
    tcp.Close();
    return 0;
}
