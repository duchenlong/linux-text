///////////////////////////////////////////////////////////
//  Composite.h
//  Implementation of the Class Composite
//  Created on:      29-12ÔÂ-2020 12:09:13
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_976364E7_AC8D_4721_B4A6_3E49B4A8A627__INCLUDED_)
#define EA_976364E7_AC8D_4721_B4A6_3E49B4A8A627__INCLUDED_

#include <list>

#include "Component.h"

class Composite : public Component
{

public:
	Composite();
	virtual ~Composite();

	virtual void Operation(int n);
	void add(Component* c);
private:
	list<Component*> _child;

};


Composite::Composite(){

}

Composite::~Composite(){
    for(auto& e : _child) {
        delete e;
        e = nullptr;
    }
}


void Composite::Operation(int n){
    indent(n);
    cout << "+ Composite" << endl;

    for(auto& e : _child) 
        e->Operation(n + 1);
}


void Composite::add(Component* c){
    _child.push_back(c);
}
#endif // !defined(EA_976364E7_AC8D_4721_B4A6_3E49B4A8A627__INCLUDED_)
