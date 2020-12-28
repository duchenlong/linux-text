///////////////////////////////////////////////////////////
//  Creator.h
//  Implementation of the Interface Creator
//  Created on:      04-12ÔÂ-2020 17:12:32
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_35F8958D_37F5_403b_B696_83004115975F__INCLUDED_)
#define EA_35F8958D_37F5_403b_B696_83004115975F__INCLUDED_

#include "ProductA.h"
#include "ProductB.h"

class Creator
{

public:
	Creator() {

	}

	virtual ~Creator() {

	}

	virtual ProductA* CreateProductA() =0;
	virtual ProductB* CreateProductB() =0;
};


class CreatorA : public Creator
{

public:
	CreatorA()=default;
	virtual ~CreatorA()=default;

    virtual ProductA* CreateProductA() {
        return new ProductA1();
    }
    virtual ProductB* CreateProductB() {
        return new ProductB1();
    }

};

class CreatorB : public Creator
{

public:
	CreatorB()=default;
	virtual ~CreatorB()=default;

    virtual ProductA* CreateProductA() {
        return new ProductA2();
    }
    virtual ProductB* CreateProductB() {
        return new ProductB2();
    }

};
#endif // !defined(EA_35F8958D_37F5_403b_B696_83004115975F__INCLUDED_)
