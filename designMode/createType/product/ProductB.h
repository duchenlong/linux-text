///////////////////////////////////////////////////////////
//  ProductB.h
//  Implementation of the Class ProductB
//  Created on:      28-12ÔÂ-2020 20:52:14
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_610CB0A8_3841_4c94_938F_191549BD89BA__INCLUDED_)
#define EA_610CB0A8_3841_4c94_938F_191549BD89BA__INCLUDED_

#include "Product.h"

class ProductB : public Product
{

public:
	ProductB();
	virtual ~ProductB();

	virtual void Operation();

};

ProductB::ProductB(){

}

ProductB::~ProductB(){

}


void ProductB::Operation(){
    cout << " ProductB Operation" << endl;
}
#endif // !defined(EA_610CB0A8_3841_4c94_938F_191549BD89BA__INCLUDED_)
