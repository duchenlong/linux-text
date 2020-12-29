///////////////////////////////////////////////////////////
//  BasicComponent.h
//  Implementation of the Class BasicComponent
//  Created on:      29-12ÔÂ-2020 16:30:22
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_FA82CC30_1110_4a20_A431_2B426F9A93C6__INCLUDED_)
#define EA_FA82CC30_1110_4a20_A431_2B426F9A93C6__INCLUDED_

#include "Component.h"

class BasicComponent : public Component
{

public:
	BasicComponent();
	virtual ~BasicComponent();

	virtual void Operation();

};

BasicComponent::BasicComponent(){

}



BasicComponent::~BasicComponent(){

}

void BasicComponent::Operation(){
    cout << " Basic ";
}
#endif // !defined(EA_FA82CC30_1110_4a20_A431_2B426F9A93C6__INCLUDED_)
