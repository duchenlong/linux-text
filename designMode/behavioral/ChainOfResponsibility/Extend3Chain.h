///////////////////////////////////////////////////////////
//  Extend3Chain.h
//  Implementation of the Class Extend3Chain
//  Created on:      29-12ÔÂ-2020 18:22:03
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_C40FAF44_5CF7_41e9_A8FB_D77A63D2B40C__INCLUDED_)
#define EA_C40FAF44_5CF7_41e9_A8FB_D77A63D2B40C__INCLUDED_

#include "subject.h"

class Extend3Chain : public ChainOfResponsibility
{

public:
	Extend3Chain(ChainOfResponsibility* ch);
	virtual void Handle(int i);
};

Extend3Chain::Extend3Chain(ChainOfResponsibility* ch)
    :ChainOfResponsibility(ch)
{}

void Extend3Chain::Handle(int i){
    if(i == 3) {
        cout << "extend 3 Message" << endl;
    } else {
        Next(i);
    }
}
#endif // !defined(EA_C40FAF44_5CF7_41e9_A8FB_D77A63D2B40C__INCLUDED_)
