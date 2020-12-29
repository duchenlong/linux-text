///////////////////////////////////////////////////////////
//  Extend2Chain.h
//  Implementation of the Class Extend2Chain
//  Created on:      29-12ÔÂ-2020 18:21:57
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_1926CCD5_8855_45b6_B089_BAD71937A425__INCLUDED_)
#define EA_1926CCD5_8855_45b6_B089_BAD71937A425__INCLUDED_

#include "subject.h"

class Extend2Chain : public ChainOfResponsibility
{

public:
	Extend2Chain(ChainOfResponsibility* ch);

	virtual void Handle(int i);
};

Extend2Chain::Extend2Chain(ChainOfResponsibility* ch)
    :ChainOfResponsibility(ch)
{}

void Extend2Chain::Handle(int i){
    if(i == 2) {
        cout << "extend 2 Message" << endl;
    } else {
        Next(i);
    }
}
#endif // !defined(EA_1926CCD5_8855_45b6_B089_BAD71937A425__INCLUDED_)
