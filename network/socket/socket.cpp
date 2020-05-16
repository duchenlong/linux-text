#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    //ipv4  udp  端口 17
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    std::cout<<"sockfd = "<<sockfd<<std::endl;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("172.17.9.190");
    int ret = bind(sockfd, (struct sockaddr*)&addr,sizeof(addr));
    std::cout<<ret<<std::endl;
    while(1)
    {
        sleep(1);
    }

    return 0;
}
