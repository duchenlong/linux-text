///////////////////////////////////////////////////////////
//  PrototypeB.h
//  Implementation of the Class PrototypeB
//  Created on:      28-12ÔÂ-2020 19:36:13
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_63B5EB2F_D71C_416e_8B7A_AB7F597A5231__INCLUDED_)
#define EA_63B5EB2F_D71C_416e_8B7A_AB7F597A5231__INCLUDED_

#include "Prototype.h"

class PrototypeB : public Prototype
{

public:
	PrototypeB();
	virtual ~PrototypeB();

	PrototypeB(const PrototypeB& p);
	virtual Prototype* Clone();
	virtual void Operation(const string& str);
	virtual void Operation();

private:
	int _value;

};

PrototypeB::PrototypeB(){
    _value = -1;
}



PrototypeB::~PrototypeB(){

}




// Ô­ÐÍ¿½±´
PrototypeB::PrototypeB(const PrototypeB& p){
    _value = p._value;
}


Prototype* PrototypeB::Clone(){

	return  new PrototypeB(*this);
}


void PrototypeB::Operation(const string& str){
    _value = atoi(str.c_str());
    cout << " update PrototypeB::_value is " << _value << endl;
}


void PrototypeB::Operation(){
    cout << " PrototypeB::_value is " << _value << endl;
}
#endif // !defined(EA_63B5EB2F_D71C_416e_8B7A_AB7F597A5231__INCLUDED_)
