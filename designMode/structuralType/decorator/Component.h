///////////////////////////////////////////////////////////
//  Component.h
//  Implementation of the Interface Component
//  Created on:      29-12ÔÂ-2020 16:30:18
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_8788204A_9D6B_41cd_9415_CFDEAD09C396__INCLUDED_)
#define EA_8788204A_9D6B_41cd_9415_CFDEAD09C396__INCLUDED_

#include <iostream>

using namespace std;

class Component
{

public:
	Component() {

	}

	virtual ~Component() {

	}

	virtual void Operation() =0;

};


#endif // !defined(EA_8788204A_9D6B_41cd_9415_CFDEAD09C396__INCLUDED_)
