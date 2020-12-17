#include <iostream>
#include <algorithm>
#include <vector>

#include "LRU.hpp"
#include "FIFO.hpp"
#include "OPT.hpp"

using namespace std;

static int blockNum = 0;    // 物理块数
static int pageNum  = 0;    // 页面个数
static int num = 0;         // 允许的页数
static vector<int> orderPage;      // 页面序列


void init() {
    blockNum = 20;
    pageNum = 7;
    num = 3;
    //orderPage.reserve(blockNum);
    orderPage = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
} 

void lru() {
    MyLRU myLru(num);
    for(auto& e : orderPage) {
        if(myLru.get(e) == false) {
            cout << "发生缺页 ";
            myLru.put(e);
        }
        myLru.show();
    }
}

void fifo() {
    MyFifo myFifo(num);
    for(auto& e : orderPage) {
        if(myFifo.get(e) == false) {
            cout << "发生缺页 ";
            myFifo.put(e);
        }
        myFifo.show();
    }
}

void opt() {
    MyOpt myOpt(orderPage,num);
    int n = orderPage.size();
    for(int i = 0; i < n; i++) {
        if(myOpt.get(orderPage[i]) == false) {
            cout << "发生缺页: ";
            myOpt.put(orderPage[i],i+1);
        } 
        myOpt.show();
    }
}


 
