///////////////////////////////////////////////////////////
//  subject.h
//  Implementation of the Interface ChainOfResponsibility
//  Created on:      29-12ÔÂ-2020 18:21:47
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_92D83DAD_ED47_4999_8117_1BBFC0053F84__INCLUDED_)
#define EA_92D83DAD_ED47_4999_8117_1BBFC0053F84__INCLUDED_

#include <iostream>

using namespace std;

class ChainOfResponsibility
{

public:
	ChainOfResponsibility(ChainOfResponsibility* ch) {
        _successor = ch;
	}

	virtual ~ChainOfResponsibility() {
        delete _successor;
        _successor = nullptr;
	}
	virtual void Handle(int i) =0;

protected:
	void Next(int i);
private:
	ChainOfResponsibility* _successor;

};

void ChainOfResponsibility::Next(int i) {
    if(_successor)
        _successor->Handle(i);
}
#endif // !defined(EA_92D83DAD_ED47_4999_8117_1BBFC0053F84__INCLUDED_)
