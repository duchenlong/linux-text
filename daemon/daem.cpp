#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>


// 确保守护进程唯一

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// 给一个文件加写锁
int lockfile(int fd) {
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;

    return fcntl(fd, F_SETLK, &fl);
}

int already_running() {
    int fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
    if(fd < 0) {
        perror("open");
        exit(-1);
    }

    if(lockfile(fd) < 0) {
        if(errno == EACCES | errno == EAGAIN) {
            close(fd);
            return 1;
        }
        perror("fcntl");
        exit(1);
    }

    // 写入当前守护进程 pid
    ftruncate(fd,0);
    char buf[16] = {'\0'};
    sprintf(buf,"%ld",(long)getpid());
    write(fd,buf,strlen(buf) + 1);
    return 0;
}

// 启动守护进程
void daemonize() {
    umask(0);   // 修改文件模式创建屏蔽字

    // fork
    pid_t fd = fork();
    if(fd < 0) {
        perror("fork");
        exit(0);
    } else if(fd != 0) {
        // 父进程，退出
        exit(0);
    }

    // 子进程
    // 创建一个新的会话
    setsid();

    // 二次调用 fork ，脱离会话的组长
    fd = fork();
    if(fd < 0) {
        perror("fork 2");
        exit(0);
    } else if(fd != 0) {
        // 父进程
        exit(0);
    }

    // 子进程
    // 更改工作目录
    if(chdir("/") < 0) {
        perror("chdir");
        exit(0);
    }

    // 关闭所有文件描述符
    struct rlimit rl;
    getrlimit(RLIMIT_NOFILE,&rl);
    for(rlim_t i = 0; i < rl.rlim_max; i ++) {
        close(i);
    }

    // 附加文件描述符
    int fd0 = open("/dev/null",O_RDWR);
    int fd1 = dup(0);
    int fd2 = dup(0);

    // 判断是否重定向成功
    if(fd0 != 0 || fd1 != 1 || fd2 != 2) {
        printf("dup error\n");
        exit(0);
    }

    // 守护进程创建成功
}

int main() {
    printf("%d\n",getpgrp());
    int fd = fork();
    if(fd < 0) {
        perror("fork");
        return 0;
    } else if(fd == 0) {
        printf("child [%d],pid = [%d]\n",getpgrp(),getpid());
        return 0;
    } else {
        sleep(1);
        printf("father [%d],pid = [%d]\n",getpgrp(),getpid());
    }

    return 0;

    daemonize();
    
    int ret = already_running();
    if(ret == 1) {
        printf("lock file error\n");
        return 0;
    }

    while(1) {
        sleep(1);
    }
    return 0;
}

/*
void test_rlimit() {
    struct rlimit rl;
    getrlimit(RLIMIT_NOFILE,&rl);

    printf("rlim_cur = [%ld] rlim_max = [%ld] \n",rl.rlim_cur,rl.rlim_max);

    if(rl.rlim_max == RLIM_INFINITY) {
        printf("1\n");
    }
}
*/
