///////////////////////////////////////////////////////////
//  Prototype.h
//  Implementation of the Interface Prototype
//  Created on:      28-12ÔÂ-2020 19:36:06
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_76F9F098_6880_48fd_9A17_AA9DED71C51B__INCLUDED_)
#define EA_76F9F098_6880_48fd_9A17_AA9DED71C51B__INCLUDED_

#include <iostream>
#include <string>

using namespace std;


class Prototype
{

public:
	Prototype() {

	}

	virtual ~Prototype() {

	}

	virtual Prototype* Clone() =0;
	virtual void Operation(const string& str) =0;
	virtual void Operation() =0;

};
#endif // !defined(EA_76F9F098_6880_48fd_9A17_AA9DED71C51B__INCLUDED_)
