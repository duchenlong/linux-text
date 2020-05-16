#include "tcpser.hpp"
#include <signal.h>
#include <sys/wait.h>

//信号触发的回调函数
void sigcallback(int signo)
{
    (void)signo;
    while(1)
    {
        //-1 等待任何子进程退出，没有限制,waitpid 和 pid的作用一样
        //NULL 表示父进程不关心子进程的终止状态
        //WHONANG 表示子进程如果没有改变，就不阻塞，直接返回0
        waitpid(-1,NULL,WNOHANG);
    }
}


int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        cout<<"请输入正确的参数 [./ser] [ip] [port]"<<endl;
        return 0;
    }
    
    signal(SIGCHLD,sigcallback);

    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpClass ts;

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

    //监听
    if(!ts.Listen(10))
    {
        return 0;
    }

    while(1)
    {
        TcpClass new_ts;
        struct sockaddr_in new_addr;
        //等待连接
        if(!ts.Accept(new_ts,&new_addr))
        {
            continue;
        }

        //成功建立连接
        cout<<"有一个新的连接 ["<<inet_ntoa(new_addr.sin_addr)<<"] ["<<ntohs(new_addr.sin_port)<<"] "<<endl;

        //创建子进程，让子进程进行通信
        int pid = fork();
        if(pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if(pid == 0)
        {
            //child
            while(1)
            {
                //接收客户端的信息
                string buf;
                new_ts.Recv(buf);
                cout<<"客户端说 : "<<buf<<endl;

                cout<<"给客户端回话 : ";
                fflush(stdout);
                cin>>buf;
                new_ts.Send(buf);
            }

            new_ts.Close();
            exit(1);//退出当前进程，
        }
        else 
        {
            //father
            new_ts.Close();
        }
    }
    return 0;
}
