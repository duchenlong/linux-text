///////////////////////////////////////////////////////////
//  Creator.h
//  Implementation of the Class Creator
//  Created on:      28-12ÔÂ-2020 20:52:07
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_A041B680_9CE6_4bbc_9698_EF88F155CAB2__INCLUDED_)
#define EA_A041B680_9CE6_4bbc_9698_EF88F155CAB2__INCLUDED_

#include <string>

#include "ProductA.h"
#include "ProductB.h"

using std::string;

class Creator
{

public:
	Creator();
	~Creator();

	Product* FactoryMethod(const string& flag);

};

Creator::Creator(){

}

Creator::~Creator(){

}

Product* Creator::FactoryMethod(const string& flag){
    if(flag == "A") {
        return new ProductA();
    } 
    else if(flag == "B") {
        return new ProductB();
    }

	return  nullptr;
}
#endif // !defined(EA_A041B680_9CE6_4bbc_9698_EF88F155CAB2__INCLUDED_)
