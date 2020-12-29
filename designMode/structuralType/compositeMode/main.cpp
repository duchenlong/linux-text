#include "Composite.h"
#include "Leaf.h"

Composite* makeComposite() {
    Composite* c1 = new Composite();
    c1->add(new Leaf());
    c1->add(new Leaf());

    Composite* c2 = new Composite();
    c2->add(new Leaf());
    c2->add(new Leaf());
    c2->add(c1);

    return c2;
}

int main() {
    Component* component = makeComposite();
    component->Operation(0);

    delete component;
    component = nullptr;
    return 0;
}

