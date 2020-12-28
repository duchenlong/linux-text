
#include "Creator.h"

int main() {
    Creator* factor = new Creator();

    cout << "创建A产品 " << endl;
    Product* pa = factor->FactoryMethod("A");
    pa->Operation();

    cout << "创建B产品" << endl;
    Product* pb = factor->FactoryMethod("B");
    pb->Operation();
    return 0;
}
