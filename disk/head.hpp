#include <cstdio>

#include <iostream>
#include <vector>

#include "FCFS.hpp"
#include "SSFT.hpp"
#include "SCAN.hpp"
using namespace std;

vector<int>  vec;       // 磁道访问请求
int         start;     // 开始位置

void init() {
    vec = {55,58,39,18,90,160,150,38,184};
    start = 100;
}

void check(int sum,int n) {
    printf("\n平均移动距离： [%lf]\n",(double)sum / n);
}

void fcfs() {
    cout << "FCFS 先来先服务算法模拟->\n" << endl;
    FCFS my_fcfs(start,vec);
    int n = vec.size();

    int sum = 0;
    for(int i = 0; i < n; i++) {
        int ret = my_fcfs.slove(i);
        printf("\t第 [%d] 次访问 [%d] 磁盘，磁头移动距离 [%d]\n",i+1,i+1,ret);
        sum += ret;
    }

    check(sum,n);
}
    
void ssft() {
    cout << "SSFT 最短寻道时间优先算法模拟->\n" << endl;

    SSFT my_ssft(vec,start);
    int n = vec.size();
    int sum = 0;

    for(int i = 0; i < n; i ++) {
        int ret = my_ssft.slove();
        sum += ret;
        printf("\t第 [%d] 次访问 [%d] 磁盘，磁头移动距离 [%d]\n",i+1,i+1,ret);
    }

    check(sum,n);
}
void scan(bool flag) {
    SCAN my_scan(start,flag,vec);
    int n = vec.size();
    int sum = 0;

    for(int i = 0; i < n; i ++) {
        int ret = my_scan.slove();
        sum += ret;
        printf("\t第 [%d] 次访问磁盘，磁头移动距离 [%d]\n",i+1,ret);
    }

    check(sum,n);
}
