///////////////////////////////////////////////////////////
//  Iobserve.h
//  Implementation of the Interface Iobserve
//  Created on:      11-12月-2020 17:28:04
//  Original author: DELL
///////////////////////////////////////////////////////////

#if !defined(EA_9B2E9142_633A_4555_9128_1FA796FC2627__INCLUDED_)
#define EA_9B2E9142_633A_4555_9128_1FA796FC2627__INCLUDED_

#include <cstdio>

#include <list>
#include <algorithm>
#include <iostream>
#include <string>

using namespace  std;

string Itoa(int Num,int R)
{
	string remain="";
	int temp;
	do {
		temp = Num%R;//取余
		Num /= R;
		if (temp >= 10)
			remain += temp - 10 + 'A';//任意进制为大于基数大于10的进制 例如，十六进制
		else remain += temp + '0';
	} while (Num);
	reverse(remain.begin(),remain.end());//逆序
	return remain;
}

class Isubject;
class Iobserve;

class Iobserve
{
public:
	Iobserve(Isubject* sub = nullptr) {
        m_Isubject = nullptr;
	}

	virtual ~Iobserve() {
	}

	virtual void update(int num) =0;
    
    virtual void write(int num) = 0;
protected:
	Isubject *m_Isubject;

};

class Isubject
{
public:
	Isubject() 
        :_state(0)
    {}

	virtual ~Isubject() {

	}
    
    virtual void setState(int state) = 0; 
    
    void notifyAllObservers() {
        for(auto& e : _vec) {
            e->update(_state);
        }
    }

    void addObserve(Iobserve* observe) {
        _vec.push_back(observe);
    }
    void erase(Iobserve* obe) {
        _vec.erase(find(_vec.begin(),_vec.end(),obe));
    }

protected:
    list<Iobserve*> _vec;
	int _state;
};

class subject : public Isubject
{
    public:
        subject() = default;
        virtual ~subject() {
            for(auto& e : _vec) {
                delete e;
                e = nullptr;
            }
        }
        virtual void setState(int state) {
            _state = state;
            this->notifyAllObservers();
        }
};



class BinaryObserve : public Iobserve
{

public:
    BinaryObserve(Isubject* sub = nullptr) {
        this->m_Isubject = sub;
        this->m_Isubject->addObserve(this);
    }
    virtual ~BinaryObserve() {
        this->m_Isubject->erase(this);
        this->m_Isubject = nullptr;
    }

    virtual void update(int num) {
        string str = Itoa(num,2);
        printf("\tstate is BinaryObserve [%s]\n",str.c_str());
    }
    
    void write(int num) {
        this->m_Isubject->setState(num);
    }
};


class HexaObserve : public Iobserve
{

public:
    HexaObserve(Isubject* sub = nullptr) {
        this->m_Isubject = sub; 
        this->m_Isubject->addObserve(this);
    }
    virtual ~HexaObserve() {
        this->m_Isubject->erase(this);
        this->m_Isubject = nullptr;
    }

    virtual void update(int num) {
        string str = Itoa(num,16);
        printf("\tstate is Hexadecimal [%s]\n",str.c_str());
    }

    void write(int num) {
        this->m_Isubject->setState(num);
    }
};
#endif // !defined(EA_9B2E9142_633A_4555_9128_1FA796FC2627__INCLUDED_)
