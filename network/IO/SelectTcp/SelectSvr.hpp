#pragma once 

#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <vector>
#include <cstdio>

#include "Tcpsvr.hpp"

using namespace std;

class SelectSvr
{
    public:
        SelectSvr()
        {
            _maxFd = -1;
            FD_ZERO(&_readfds);
        }

        //添加文件描述符
        void AddFd(int fd)
        {
            FD_SET(fd,&_readfds);

            //更新最大 文件描述符 数值
            if(fd > _maxFd)
                _maxFd = fd;
        }

        //删除文件描述符
        void DeleteFd(int fd)
        {
            FD_CLR(fd,&_readfds);

            //更新最大 文件描述符 数值
            for(int i = _maxFd; i >= 0; i--)
                if(FD_ISSET(i,&_readfds) == 1)//找第一个存在的文件描述符
                {
                    _maxFd = i;
                    break;
                }
        }

        bool SelectWait(vector<Tcpsvr>& vec)
        {
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 3000;//设置超时时间

            fd_set tmp = _readfds;
            int ret = select(_maxFd + 1,&tmp,NULL,NULL,&tv);
            if(ret < 0)
            {
                perror("select");
                return false;
            }
            else if(ret == 0)
            {
                //cout<<"select timeout"<<endl;
                return false;
            }

            //程序正常的流程
            for(int i = 0; i <=  _maxFd; i++)
                if(FD_ISSET(i,&tmp))
                {
                    //返回就绪的 文件描述符i 的类对象
                    Tcpsvr ts;
                    ts.SetFd(i);
                    vec.push_back(ts);
                }

            return true;
        }

    private:
        int _maxFd;
        fd_set _readfds;
};


