#include "Extend1Chain.h"
#include "Extend2Chain.h"
#include "Extend3Chain.h"

ChainOfResponsibility* Create() {
    return new Extend1Chain(\
            new Extend2Chain(\
                new Extend3Chain(nullptr)));
}

int main() {
    ChainOfResponsibility* ch = Create();
    ch->Handle(2);

    ch->Handle(1);

    ch->Handle(3);
    return 0;
}
