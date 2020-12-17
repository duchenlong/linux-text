#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class MyFifo{
    private:
        unordered_map<int,list<int>::iterator> _hash;
        list<int>   _list;
        int         _capacity;
    public:
        MyFifo(int num){
            _capacity = num;
        }
        
        bool get(int value);
        void put(int value);
        void show();
};

bool MyFifo::get(int value){
    if(_hash.count(value) == 0) 
        return false;
    return true;
}

void MyFifo::put(int value) {
    if(get(value) == true) 
        return ;

    if((int)_hash.size() == _capacity) {
        // 头删
        auto f = _list.front();
        _hash.erase(f);
        _list.pop_front();
    }

    _list.push_back(value);
    _hash[value] = _list.end()--;
}

void MyFifo::show() {
    for(auto& e : _list) {
        cout << e << " ";
    }
    cout << endl;
}
