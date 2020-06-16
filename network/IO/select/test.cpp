#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
    fd_set read_fds;
    
    timeval time;

    while(1)
    {
        //清除 fd_set 的所有位
        FD_ZERO(&read_fds);
        // 设置 0 标准输入 文件描述符
        FD_SET(0,&read_fds);
        
        printf("> ");
        fflush(stdout);
        
        //没有超时时间
        //int ret = select(1,&read_fds,NULL,NULL,NULL);
        
        time.tv_sec = 3;
        time.tv_usec = 0;
        //设置超时时间
        printf("time = %d\n",time.tv_sec);
        int ret = select(0 + 1,&read_fds,NULL,NULL,&time);
        if(ret < 0)
        {
            perror("select");
            continue;
        }
        else if(ret == 0)
        {
            printf("timeout time : %d\n",time.tv_sec);
            sleep(1);
            continue;
        }

        //判断 0 标准输入文件描述符是否为真
        if(FD_ISSET(0,&read_fds))
        {
            //就绪
            char buf[1024] = {'\0'};
            read(0,buf,sizeof(buf)-1);
            printf("输入 ： %s\n",buf);
        }
        else 
        {
            printf("无效的文件描述符 \n");
            continue;
        }

    }

    return 0;
}
