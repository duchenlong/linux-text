///////////////////////////////////////////////////////////
//  Extend1Chain.h
//  Implementation of the Class Extend1Chain
//  Created on:      29-12ÔÂ-2020 18:21:52
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_9AD94152_EE8C_4dc4_A549_D01FAA926921__INCLUDED_)
#define EA_9AD94152_EE8C_4dc4_A549_D01FAA926921__INCLUDED_

#include "subject.h"

class Extend1Chain : public ChainOfResponsibility
{

public:
	Extend1Chain(ChainOfResponsibility* ch);

	virtual void Handle(int i);
};

Extend1Chain::Extend1Chain(ChainOfResponsibility* ch)
   :ChainOfResponsibility(ch)
{}

void Extend1Chain::Handle(int i){
    if(i == 1) {
        cout << "extend 1 Message" << endl;
    } else{
        Next(i);
    }
}
#endif // !defined(EA_9AD94152_EE8C_4dc4_A549_D01FAA926921__INCLUDED_)
