///////////////////////////////////////////////////////////
//  ProductB.h
//  Implementation of the Interface ProductB
//  Created on:      04-12ÔÂ-2020 17:12:33
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_7B96DD47_7EA9_4746_9808_45928C667E11__INCLUDED_)
#define EA_7B96DD47_7EA9_4746_9808_45928C667E11__INCLUDED_

#include <iostream>

using std::cout;
using std::endl;

class ProductB
{

public:
	ProductB() {

	}

	virtual ~ProductB() {

	}

	virtual bool Operation() =0;

};

class ProductB1 : public ProductB
{

public:
	ProductB1()=default;
	virtual ~ProductB1()=default;

    virtual bool Operation() {
        cout << " ProductB1 Operation " << endl;
        return true;
    }

};


class ProductB2 : public ProductB
{

public:
	ProductB2()=default;
	virtual ~ProductB2()=default;

    virtual bool Operation() {
        cout << " ProductB2 Operation " << endl;
        return true;
    }

};
#endif // !defined(EA_7B96DD47_7EA9_4746_9808_45928C667E11__INCLUDED_)
