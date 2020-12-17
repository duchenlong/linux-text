#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

class MyLRU{
    private:
        unordered_map<int,list<int>::iterator> _hash;
        list<int> _list;
        int _capacity;
    public:
        MyLRU(int num){
            _capacity = num;
        }
        bool get(int value);
        void put(int value);
        void show();
};

bool MyLRU::get(int value) {
    if(_hash.count(value) == 0) 
        return false;
    auto node = _hash[value];
    _list.erase(node);

    _list.push_front(value);
    _hash[value] = _list.begin();
    return true;
}

void MyLRU::put(int value) {
    if(get(value)) return ;
    
    if((int)_hash.size() == _capacity) {
        // 尾删
        auto del = _list.back();
        _hash.erase(del);
        _list.pop_back();
    }

    _list.push_front(value);
    _hash[value] = _list.begin();
}

void MyLRU::show() {
    for(auto& e : _list) {
        cout << e << " ";
    }
    cout << endl;
}
