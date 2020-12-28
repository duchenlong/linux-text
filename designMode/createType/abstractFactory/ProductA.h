///////////////////////////////////////////////////////////
//  ProductA.h
//  Implementation of the Interface ProductA
//  Created on:      04-12ÔÂ-2020 17:12:32
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_AA61F0A6_359F_4e45_809A_362A62F9DAAE__INCLUDED_)
#define EA_AA61F0A6_359F_4e45_809A_362A62F9DAAE__INCLUDED_

#include <iostream>

using std::endl;
using std::cout;

class ProductA
{

public:
	ProductA() {

	}

	virtual ~ProductA() {

	}

	virtual bool Operation() =0;

};

class ProductA1 : public ProductA
{

public:
	ProductA1()=default;
	virtual ~ProductA1()=default;

    virtual bool Operation() {
        cout << " ProductA1 Operation " << endl;
        return true;
    }

};


class ProductA2 : public ProductA
{

public:
	ProductA2()=default;
	virtual ~ProductA2()=default;

    virtual bool Operation() {
        cout << " ProductA2 Operation " << endl;
        return true;
    }

};
#endif // !defined(EA_AA61F0A6_359F_4e45_809A_362A62F9DAAE__INCLUDED_)
