#include "DecoratorA.h"
#include "DecoratorB.h"
#include "BasicComponent.h"

Component* Create(int f) {
    if(f == 0) {
        return new BasicComponent(); 
    } else if ( f == 1 ) {
        return new DecoratorA(new BasicComponent());
    } else if ( f == 2 ) {
        return new DecoratorB(new BasicComponent());
    }

    return nullptr;
}

int main() {
    Component* c0 = Create(0);
    c0->Operation();
    
    cout << endl;
    Component* c1 = Create(1);
    c1->Operation();

    cout << endl;
    Component* c2 = Create(2);
    c2->Operation();
    
    cout << endl;
    return 0;
}
