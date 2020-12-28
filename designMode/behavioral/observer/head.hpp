#ifndef  __HEAD_HPP__
#define __HEAD_HPP__ 

#include "Iobserve.h"

#include <iostream>

using namespace std;

void slove() {
    Isubject* subj = new subject();

    // 设置两个对象
    Iobserve* objA = new BinaryObserve(subj);
    Iobserve* objB = new HexaObserve(subj);
   
    cout << "subject modification 10 ->" << endl;
    subj->setState(10);

    cout << "objA  modification 155 ->" << endl;
    objA->write(155);
    
    cout << "objB  modification 65535 ->" << endl;
    objB->write(65535);
}

#endif 
