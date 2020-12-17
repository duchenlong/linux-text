#include "head.hpp"

int main() {
    init();
    
    cout << "\n\nLRU算法演示 :  " << endl;
    lru();

    cout << "\n\nFIFO算法演示: " << endl;
    fifo();

    cout << "\n\nOPT算法演示: " << endl;
    opt();
    return 0;
}
