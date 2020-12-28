///////////////////////////////////////////////////////////
//  abstration.h
//  Implementation of the Interface abstration
//  Created on:      16-12ÔÂ-2020 18:40:02
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_0583644A_2FDE_41c9_A97A_5BC0F78208CD__INCLUDED_)
#define EA_0583644A_2FDE_41c9_A97A_5BC0F78208CD__INCLUDED_

#include "implement.h"

class abstration
{

public:
	abstration(char ch = '\0') {
        m_implement = nullptr;
	}
	virtual ~abstration() {
	}

	virtual void operation() =0;
protected:
	implement *m_implement;
};

class abstrationA : public abstration
{

public:
    abstrationA(char ch = '\0') {
        if(ch == 'A') {
            m_implement = new implementA();
        } else if(ch == 'B') {
            m_implement = new implementB();
        } 
    }

    virtual ~abstrationA() {
        delete m_implement;
        m_implement = nullptr;
    }

    virtual void operation() {
        m_implement->operation();
    }

};
#endif // !defined(EA_0583644A_2FDE_41c9_A97A_5BC0F78208CD__INCLUDED_)
