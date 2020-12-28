///////////////////////////////////////////////////////////
//  Singleton.h
//  Implementation of the Class Singleton
//  Created on:      28-12月-2020 0:06:22
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_7F08158A_D6C4_420a_9235_240C0277BA3F__INCLUDED_)
#define EA_7F08158A_D6C4_420a_9235_240C0277BA3F__INCLUDED_

#include <iostream>

using namespace std;

class Singleton
{

public:
	static Singleton* Create();
	static void Destory();
	void Printf();
	void next();

private:
	static Singleton* _instance;
	int _value;

	Singleton();
	~Singleton();

};

Singleton* Singleton::_instance = nullptr;

// 构造函数
Singleton::Singleton(){
    _value = 1;
}


Singleton::~Singleton(){
    _value = -1;
}


Singleton* Singleton::Create(){
    if(Singleton::_instance == nullptr) {
        _instance = new Singleton();
    }
	return  _instance;
}


void Singleton::Destory(){
    delete _instance;
    _instance = nullptr;
}


void Singleton::Printf(){
    cout << _value << endl;
}


void Singleton::next(){
    _value ++;
}
#endif // !defined(EA_7F08158A_D6C4_420a_9235_240C0277BA3F__INCLUDED_)
