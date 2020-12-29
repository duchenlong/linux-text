///////////////////////////////////////////////////////////
//  Adapter.h
//  Implementation of the Class Adapter
//  Created on:      29-12ÔÂ-2020 10:33:18
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_F6F691D8_0C70_4d34_ABF3_F099E726452C__INCLUDED_)
#define EA_F6F691D8_0C70_4d34_ABF3_F099E726452C__INCLUDED_

#include "Target.h"

class Adapter : public Target
{

public:
	Adapter();
	virtual ~Adapter();

	virtual void Operation() const;

};

Adapter::Adapter(){

}



Adapter::~Adapter(){

}


void Adapter::Operation() const {
    cout << "i am new Adapter" << endl;
}

#endif // !defined(EA_F6F691D8_0C70_4d34_ABF3_F099E726452C__INCLUDED_)
