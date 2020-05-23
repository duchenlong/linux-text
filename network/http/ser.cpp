#include "tcpClass.hpp"
#include <cstring>
#include <sstream>

using std::stringstream;
using std::endl;

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        cout<<"请输入正确的参数 [./ser] [ip] [port]"<<endl;
        return 0;
    }

    string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    TcpClass ts;

    if(!ts.CreateSocket())
    {
        return 0;
    }

    if(!ts.Bind(ip, port))
    {
        return 0;
    }

    if(!ts.Listen())
    {
        return 0;                        
    }

    TcpClass ser_ts;

    while(1)
    {
        struct sockaddr_in cli_addr;
        if(!ts.Accept(cli_addr,ser_ts))
        {
            return 0;
        }
        
        string buf;
        ser_ts.Recv(buf);
        cout<<"chrom say: "<<buf<<endl;
        
        string body = "<html><h1>hello world</h1></html>";

          
        stringstream ss;
        //200
        ss << "HTTP/1.1 200 OK\r\n";                                                                   
        //302
        //ss << "HTTP/1.1 302 Found\r\n";
        //404
        //ss << "HTTP/1.1 404 Page Not Found\r\n";
        //502
        //ss << "HTTP/1.1 502 Bad Gateway\r\n";
        ss << "Content-Type: text/html\r\n";
        ss << "Content-Length: " << body.size() << "\r\n";
        ss << "\r\n";
        string header = ss.str();

        ser_ts.Send(header);
        ser_ts.Send(body);
    }
    return 0;
}
