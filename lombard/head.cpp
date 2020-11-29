#include "head.hpp"

vector<bool> ProVis;                //  当前进程是否已经完全分配
vector<string> ID;                  //  每个进程的名称
vector<vector<int> > Max;           //  每个进程对每种资源的需求
vector<vector<int> > Allocation;    //  每个进程已经分配的每种资源
vector<vector<int> > Need;          //  进程还需要资源
vector<int> Request;                //  进程请求资源量
vector<int> SafeOrder;              //  安全执行的顺序
vector<int> Available;              //  系统可分配资源
int idx;                            //  请求的进程编号
int NoAllocCnt;                     //  当前没有分配完全的进程数

// 初始化
void init() {
    ID          = {"P0","P1","P2","P3","P4"};
    Available   = {3,3,2};
    Max         = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    Allocation  = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    Need        = {{7,4,3},{1,2,2},{6,0,0},{0,1,1},{4,3,1}};

    idx = -1;
    NoAllocCnt = PROCESSCNT;
    ProVis.resize(PROCESSCNT,false);
    Request.reserve(RESOURCECNT);
    //SafeOrder.resize(PROCESSCNT,-1);
    for(int i = 0; i < PROCESSCNT; i++) SafeOrder.push_back(i);
}


// 显示系统资源，未结束的进程占用资源情况                            
void display() {
    printf("\n\n\n-----------------------------------------\n");
    printf("当前系统可用资源: \n");
    for(int i = 0; i < RESOURCECNT; i++) printf("\t%c",'A' + i);
    printf("\n");
    for(int i = 0; i < RESOURCECNT; i++) printf("\t%d",Available[i]);
    printf("\n\n");

    printf("正在执行进程的资源分配情况： \n");
    printf("ID \tMAX \t Allocation \t Need \n");
    for(int i = 0; i < NoAllocCnt; i++) {
        int p = SafeOrder[i];
        cout << ID[p] << "\t";
        for(int j = 0; j < RESOURCECNT; j++) cout << Max[p][j] << " ";
        cout << " \t    ";

        for(int j = 0; j < RESOURCECNT; j++) cout << Allocation[p][j] << " ";
        cout << " \t";

        for(int j = 0; j < RESOURCECNT; j++) cout << Need[p][j] << " ";
        cout << "\n";
    }
    
    cout << "\n 安全分配的序列： ";
    for(int i = 0; i < NoAllocCnt; i++){
        cout << SafeOrder[i];
        if(i != NoAllocCnt - 1) cout << " -> ";
    }
    cout << "\n\n";
}

// 得到第一个可以释放的进程号，没有返回-1
int GetFirst(vector<int>& t, vector<bool>& vis) {
    
    for(int i = 0; i < PROCESSCNT; i++) {
        if(vis[i]) continue;
        int j = 0;
        for(; j < RESOURCECNT; j++) {
            if(Need[i][j] > t[j]) break;
        }
        if(j == RESOURCECNT) return i;
    }

    return -1;
}

void check() {
    if(idx == -1) return ; 
    bool flag = true;
    for(int i = 0; i < RESOURCECNT; i++) {
        Allocation[idx][i] += Request[i];
        Need[idx][i] -= Request[i];
        Available[i] -= Request[i];
        if(Need[idx][i] != 0) flag = false;
    }
    
    // 可以释放
    if(flag) {
        ProVis[idx] = true;
        for(int i = 0; i < NoAllocCnt; i++)
            if(SafeOrder[i] == idx){
                NoAllocCnt --;
                SafeOrder.erase(SafeOrder.begin() + i);
                ProVis[idx] = true;
                for(int j = 0; j < RESOURCECNT; j++)
                    Available[j] += Max[idx][j];
                break;
            }

    }
}

// 执行银行家算法            
bool banker() {
    vector<int> t = Available;          // 当前系统资源的副本
    vector<bool> vis = ProVis;          // 当前可分配资源的副本
    vector<int> newOrder = SafeOrder;   // 安全序列的副本
    vector<int> tIdx;                   // 请求分配进程的Need的副本

    if(idx != -1) {
        tIdx = Need[idx];
        // 减去请求分配的资源
        for(int i = 0; i < RESOURCECNT; i++) {
            t[i] -= Request[i];
            Need[idx][i] -= Request[i];
        }
    }

    for(int i = 0; i < NoAllocCnt; i++) {
        int index = GetFirst(t,vis);
        // cout << index << " ";
        if(index == -1) {
            if(idx != -1) Need[idx] = tIdx;
            cout << "\n 当前资源无法分配 ~~~~~~~~~ " << endl;
            return false; // 存在无法分配资源的进程
        }
        
        for(int j = 0; j < RESOURCECNT; j++) {
            t[j] += Allocation[index][j];           // 当前进程结束后，可以还给操作系统的资源数
            if(index == idx) t[j] += Request[j];    // 是请求分配的资源
        }
        newOrder[i] = index;
        vis[index] = true;
    }
    
    SafeOrder = newOrder;
    if(idx != -1) Need[idx] = tIdx;
    // 可以成功分配，检查idx是否可以释放
    check();
    
    idx = -1;
    return true;
}

// 输入分配资源
bool input() {
    printf("\n\n=========================================\n\n");
    printf("请输入需要分配资源的进程号，例如 P0 : 0  -> ");
    fflush(stdout);
    cin >> idx;
    // cout <<" ------" <<  idx << endl;
    if(idx < 0 || idx >= PROCESSCNT || ProVis[idx]) {
        cout << " 输入进程号不合法 ~~~~~~" << endl;
        return false;
    }
    
    bool flag = true;
    for(int i = 0; i < RESOURCECNT; i++) {
        printf(" 分配给 [%d] 号进程 [%c] 资源的数量为 -> ",idx,(char)('A' + i));
        cin >> Request[i];
        if(Request[i] > Need[idx][i] || Available[i] < Request[i]) flag = false;
        cout << endl;
    }
    if(!flag) cout << " 当前资源分配不合理(和需求不相符，或者超过最大资源)，不能分配 ~~~~~~~~" << endl;
    return flag;
}

// 所有进程是否都得到了资源                    
bool isExit() {
    return NoAllocCnt == 0;
}                            
