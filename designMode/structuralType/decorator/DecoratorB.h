///////////////////////////////////////////////////////////
//  DecoratorB.h
//  Implementation of the Class DecoratorB
//  Created on:      29-12ÔÂ-2020 16:30:31
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_C16CF926_DBCF_450e_BF7C_68640FDBE4E3__INCLUDED_)
#define EA_C16CF926_DBCF_450e_BF7C_68640FDBE4E3__INCLUDED_

#include "Decorator.h"

class DecoratorB : public Decorator
{

public:
	DecoratorB(Component* c);

	virtual void Operation();

};

DecoratorB::DecoratorB(Component* c)
    :Decorator(c)
{}

void DecoratorB::Operation(){
    cout << " <B> ";
    Decorator::Operation();
    cout << " </B> ";
}
#endif // !defined(EA_C16CF926_DBCF_450e_BF7C_68640FDBE4E3__INCLUDED_)
