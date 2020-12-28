
#include "PrototypeA.h"
#include "PrototypeB.h"

Prototype* Create(char flag) {
    if(flag == 'A') {
        return new PrototypeA();
    } else if(flag == 'B') {
        return new PrototypeB();
    }
    return nullptr;
}

int main() {
    // 创建A的原型
    Prototype* pa = Create('A');
    pa->Operation(" Hello ");
    cout << "clone A" << endl;

    // A 对象原型拷贝，并执行拷贝后的对象
    Prototype* pa1 = pa->Clone();
    pa1->Operation();

    // 创建B的原型
    Prototype* pb = Create('B');
    pb->Operation("1314");
    cout << "clone B" << endl;
    
    // B  对象原型拷贝，并执行拷贝后的对象
    Prototype* pb1 = pb->Clone();
    pb1->Operation();
    return 0;
}
