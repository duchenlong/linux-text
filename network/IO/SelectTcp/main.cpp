#include "SelectSvr.hpp"

#define CHECK_RET(p) if(p != true) {return -1;}

int main()
{
    Tcpsvr listen_ts;//监听的对象
    CHECK_RET(listen_ts.CreateSocket());
    CHECK_RET(listen_ts.Bind("0.0.0.0",19998));
    CHECK_RET(listen_ts.Listen());
    
    //建立服务端
    SelectSvr ss;
    ss.AddFd(listen_ts.GetFd());

    while(1)
    {
        //监控
        vector<Tcpsvr> vec;
        if(!ss.SelectWait(vec))
            continue;
        
        for(size_t i = 0; i < vec.size(); i++)
        {
            //接收新连接
            if(listen_ts.GetFd() == vec[i].GetFd())
            {
                struct sockaddr_in addr;
                Tcpsvr peerts;
                listen_ts.Accept(&addr,peerts);

                cout<<"有一个新连接 ： ip = [" << inet_ntoa(addr.sin_addr)<<"] ";
                cout<<"port = ["<<ntohs(addr.sin_port)<<" ]"<<endl;

                //新创建的条件字 添加到select事件集合中
                ss.AddFd(peerts.GetFd());
            }
            else //接收数据
            {
                string data;
                bool ret = vec[i].Recv(data);

                //如果对端关闭连接，或者发送了错误
                //进行终止
                if(!ret)
                {
                    ss.DeleteFd(vec[i].GetFd());
                    vec[i].Close();
                    continue;
                }
                cout<<"客户端["<<vec[i].GetFd()<<  "]发送的数据是 ： "<<data<<endl;

                //给客户端回复数据
                fflush(stdout);
                cout<<"回复客户端[" <<vec[i].GetFd() <<"]数据 ： ";
                getline(cin,data);
                vec[i].Send(data);
            }
        }
    }
    return 0;
}
