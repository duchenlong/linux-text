///////////////////////////////////////////////////////////
//  Decorator.h
//  Implementation of the Class Decorator
//  Created on:      29-12��-2020 16:30:25
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_9050909E_09A4_4586_B0B2_E6CBFFAFB3FF__INCLUDED_)
#define EA_9050909E_09A4_4586_B0B2_E6CBFFAFB3FF__INCLUDED_

#include "Component.h"

class Decorator : public Component
{

public:
	Decorator();
	virtual ~Decorator();
	Component *m_Component;

	Decorator(Component* c);
	virtual void Operation();
};


Decorator::Decorator(){

}

Decorator::~Decorator(){
    delete m_Component;
    m_Component = nullptr;
}

Decorator::Decorator(Component* c){
	m_Component = c;
}

void Decorator::Operation(){
    m_Component->Operation();
}
#endif // !defined(EA_9050909E_09A4_4586_B0B2_E6CBFFAFB3FF__INCLUDED_)
