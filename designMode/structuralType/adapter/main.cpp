#include <string>

#include "Adapter.h"

using namespace std;

Target* Create(const string& s) {
    if(s == "Target") {
        return new Target();
    }
    else if(s == "Adapter") {
        return new Adapter();
    }

    return nullptr;
}

int main() {
    Target* t1 = Create("Target");
    Target* t2 = Create("Adapter");

    t1->Operation();

    t2->Operation();
    return 0;
}
