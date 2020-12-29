///////////////////////////////////////////////////////////
//  DecoratorA.h
//  Implementation of the Class DecoratorA
//  Created on:      29-12ÔÂ-2020 16:30:28
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_8730FA20_8484_4672_A3B9_2770E80545F8__INCLUDED_)
#define EA_8730FA20_8484_4672_A3B9_2770E80545F8__INCLUDED_

#include "Decorator.h"

class DecoratorA : public Decorator
{

public:
	DecoratorA(Component* c);

	virtual void Operation();

};

DecoratorA::DecoratorA(Component* c)
    :Decorator(c)
{}

void DecoratorA::Operation(){
    cout << " <A> ";
    Decorator::Operation();
    cout << " </A> ";
}
#endif // !defined(EA_8730FA20_8484_4672_A3B9_2770E80545F8__INCLUDED_)
