#include "head.hpp"

int main() {
    system("clear");
    init();
    if(!banker()) return 0;
    
    display();  // 显示当前资源
    while (isExit() == false) {
        bool ret = input();    // 输入
        
        if(ret)
            banker();   // 执行银行家算法

        display();  // 显示当前资源
        cout << "按任意键继续 ~~~~~~~~~~~" << endl;
        fflush(stdout);
        getchar();
    }

    return 0;
}
