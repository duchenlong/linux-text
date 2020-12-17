#include "head.hpp"

int main() {
    init();

    fcfs();

    ssft();
    cout << "SCAN 电梯算法算法模拟->\n" << endl;
    scan(false);

    cout << "CSCAN 电梯算法单向模拟->\n" << endl;
    scan(true);
    return 0;
}
