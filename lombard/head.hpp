
#ifndef __HEAD_HPP__
#define __HEAD_HPP__ 

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define MAXNUM      20      // 最大行号
#define RESOURCECNT 3       // 系统资源数
#define PROCESSCNT  5       // 系统进程数

extern vector<vector<int> >     Max;           //  每个进程对每种资源的需求
extern vector<vector<int> >     Allocation;    //  每个进程已经分配的每种资源
extern vector<vector<int> >     Need;          //  进程还需要资源
extern vector<int>              Available;     //  系统可分配资源
extern vector<int>              SafeOrder;     //  安全执行的顺序
extern vector<int>              Request;       //  进程请求资源量
extern vector<string>           ID;            //  每个进程的名称
extern vector<bool>             ProVis;        //  当前进程是否已经完全分配
extern int                      idx;           //  请求的进程编号
extern int                      NoAllocCnt;    //  当前没有分配完全的进程数


void init();                                // 初始化
void display();                             // 显示系统资源，未结束的进程占用资源情况
bool banker();                              // 执行银行家算法
bool input();                               // 输入分配指定进程的资源
bool isExit();                              // 所有进程是否都得到了资源
#endif 
