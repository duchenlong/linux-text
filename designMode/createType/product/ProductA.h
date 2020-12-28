///////////////////////////////////////////////////////////
//  ProductA.h
//  Implementation of the Class ProductA
//  Created on:      28-12ÔÂ-2020 20:52:10
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_4894AC25_8E34_4654_A27A_71AF89944F8C__INCLUDED_)
#define EA_4894AC25_8E34_4654_A27A_71AF89944F8C__INCLUDED_

#include "Product.h"

class ProductA : public Product
{

public:
	ProductA();
	virtual ~ProductA();

	virtual void Operation();

};

ProductA::ProductA(){

}



ProductA::~ProductA(){

}

void ProductA::Operation(){
    cout << " productA Operation " << endl;
}
#endif // !defined(EA_4894AC25_8E34_4654_A27A_71AF89944F8C__INCLUDED_)
