///////////////////////////////////////////////////////////
//  Target.h
//  Implementation of the Class Target
//  Created on:      29-12ÔÂ-2020 10:33:14
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_B2463A47_CC4A_4e94_8914_365E0B1FBFAC__INCLUDED_)
#define EA_B2463A47_CC4A_4e94_8914_365E0B1FBFAC__INCLUDED_

#include <iostream>

using namespace std;

class Target
{

public:
	Target();

	virtual ~Target();
	virtual void Operation() const;

};

Target::Target(){

}


Target::~Target(){

}

void Target::Operation() const{
    cout << " hello design pattern , i am Target" << endl;
}
#endif // !defined(EA_B2463A47_CC4A_4e94_8914_365E0B1FBFAC__INCLUDED_)
