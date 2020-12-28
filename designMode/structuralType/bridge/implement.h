///////////////////////////////////////////////////////////
//  implement.h
//  Implementation of the Interface implement
//  Created on:      16-12ÔÂ-2020 18:40:07
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_E034BBAE_C514_4558_BFA8_939A09F9C836__INCLUDED_)
#define EA_E034BBAE_C514_4558_BFA8_939A09F9C836__INCLUDED_

#include <iostream>

using namespace std;

class implement
{

public:
	implement() {

	}

	virtual ~implement() {

	}

	virtual void operation() =0;

};

class implementA : public implement
{

public:
	implementA() = default;
	virtual ~implementA() = default;

    virtual void operation() {
        cout << "\tcall operation A" << endl;
    }

};


class implementB : public implement
{

public:
	implementB() = default;
	virtual ~implementB() = default;

    virtual void operation() {
        cout << "\tcall operation B" << endl;
    }

};
#endif // !defined(EA_E034BBAE_C514_4558_BFA8_939A09F9C836__INCLUDED_)
