///////////////////////////////////////////////////////////
//  Component.h
//  Implementation of the Interface Component
//  Created on:      29-12ÔÂ-2020 12:09:03
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_9D29071E_BC2B_4277_8BC3_CEE4AC28E7B1__INCLUDED_)
#define EA_9D29071E_BC2B_4277_8BC3_CEE4AC28E7B1__INCLUDED_
#include <iostream>

using namespace std;

class Component
{

public:
	Component() {

	}

	virtual ~Component() {

	}

	virtual void Operation(int n) =0;
	void indent(int n);
};

void Component::indent(int n){
    while(n --) 
        cout << "  ";
}
#endif // !defined(EA_9D29071E_BC2B_4277_8BC3_CEE4AC28E7B1__INCLUDED_)
