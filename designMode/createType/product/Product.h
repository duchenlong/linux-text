///////////////////////////////////////////////////////////
//  Product.h
//  Implementation of the Interface Product
//  Created on:      28-12ÔÂ-2020 20:52:03
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_13A54FF8_B55E_420a_8A6E_0010772716B8__INCLUDED_)
#define EA_13A54FF8_B55E_420a_8A6E_0010772716B8__INCLUDED_

#include <iostream>

using namespace std;

class Product
{

public:
	Product() {

	}

	virtual ~Product() {

	}

	virtual void Operation() =0;

};
#endif // !defined(EA_13A54FF8_B55E_420a_8A6E_0010772716B8__INCLUDED_)
