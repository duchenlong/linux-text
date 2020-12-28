///////////////////////////////////////////////////////////
//  PrototypeA.h
//  Implementation of the Class PrototypeA
//  Created on:      28-12月-2020 19:36:10
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_DCA7B391_40CD_4854_AA2F_6547597970DB__INCLUDED_)
#define EA_DCA7B391_40CD_4854_AA2F_6547597970DB__INCLUDED_

#include "Prototype.h"

class PrototypeA : public Prototype
{

public:
	PrototypeA();
	virtual ~PrototypeA();

	PrototypeA(const PrototypeA& p);
	virtual Prototype* Clone();
	virtual void Operation(const string& str);
	virtual void Operation();

private:
	string _value;

};


PrototypeA::PrototypeA(){
    _value = "";
}



PrototypeA::~PrototypeA(){

}

// 原型的拷贝
PrototypeA::PrototypeA(const PrototypeA& p){
    _value = p._value;
}


Prototype* PrototypeA::Clone(){
    
	return  new PrototypeA(*this);
}


void PrototypeA::Operation(const string& str){
    _value = str;
    cout << " update PrototypeA::Value is " <<_value << endl;
}


void PrototypeA::Operation(){
    cout << " PrototypeA::Value is " << _value << endl;
}
#endif // !defined(EA_DCA7B391_40CD_4854_AA2F_6547597970DB__INCLUDED_)
