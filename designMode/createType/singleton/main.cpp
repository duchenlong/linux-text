#include "Singleton.h"

int main() {
    Singleton* one = Singleton::Create();   // 创建第一个对象实例
    Singleton* two = Singleton::Create();   // 第二个对象实例

    cout << "one 对象 value -> " << endl;
    one->Printf();

    cout << "two 对象 value -> " << endl;
    two->Printf();
    
    one->next();
    two->next();
    cout << "one 和 two 修改后 value 的结果 -> " << endl;

    cout << "one 对象 value -> " << endl;
    one->Printf();

    cout << "two 对象 value -> " << endl;
    two->Printf();
    return 0;
}
