
#ifndef __HEAD_HPP__
#define __HEAD_HPP__ 

#include "abstration.h"
#include <iostream>

using namespace std;

void slove(char ch) {
    cout << "operation " << ch << " ing....." << endl;
    abstration* abstrat = new abstrationA(ch);
    abstrat->operation();
}


#endif
