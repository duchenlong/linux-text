///////////////////////////////////////////////////////////
//  Leaf.h
//  Implementation of the Class Leaf
//  Created on:      29-12ÔÂ-2020 12:09:08
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_121B89EA_7863_40e6_81AB_ACCC7A81A6DC__INCLUDED_)
#define EA_121B89EA_7863_40e6_81AB_ACCC7A81A6DC__INCLUDED_

#include "Component.h"

class Leaf : public Component
{

public:
	Leaf();
	virtual ~Leaf();

	virtual void Operation(int n);
};

Leaf::Leaf(){

}



Leaf::~Leaf(){

}


void Leaf::Operation(int n){
    indent(n);
    cout << "- Leaf" << endl;
}
#endif // !defined(EA_121B89EA_7863_40e6_81AB_ACCC7A81A6DC__INCLUDED_)
