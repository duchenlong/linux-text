
#ifndef __HEAD_HPP__
#define __HEAD_HPP__

#include <iostream>

#include "Creator.h"

using namespace std;

void sloveA() {
    cout << "\n工厂A 操作 生产A1，B1产品-->" << endl;
    // 创建一个 生产A1,B1产品的工厂A
    Creator* factorAB1 = new CreatorA();
    ProductA* pA1 = factorAB1->CreateProductA();    // A1产品的生产方法
    ProductB* pB1 = factorAB1->CreateProductB();    // B1产品的生产方法

    bool ret = pA1->Operation();

    if(ret == false) {
        cout << "PA1 false" << endl;
        return ;
    }
    ret = pB1->Operation();
    if(ret == false) {
        cout << "PB1 false" << endl;
        return ;
    }
}

void sloveB() {
    cout << "\n工厂B 操作 生产A2，B2产品-->" << endl;
    // 创建一个 生产A2,B2产品的工厂B
    Creator* factorAB2 = new CreatorB();
    ProductA* pA2 = factorAB2->CreateProductA();    // A1产品的生产方法
    ProductB* pB2 = factorAB2->CreateProductB();    // B1产品的生产方法

    bool ret = pA2->Operation();
    if(ret == false) {
        cout << "PA2 false" << endl;
        return ;
    }
    ret = pB2->Operation();

    if(ret == false) {
        cout << "PB2 false" << endl;
        return ;
    }
}

#endif
