#include <list>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

class MyOpt{
    private:
        vector<int> _vec;
        list<int>   _list;
        int         _capacity;
        unordered_map<int,list<int>::iterator> _hash;
    public:
        MyOpt(vector<int>& vec,int num) {
            _vec = vec;
            _capacity = num;
        }
        bool get(int value);
        void put(int value,int pos);
        void show();
        int find(int value,int pos);
};

int MyOpt::find(int value,int pos) {
    int n = _vec.size();
    for(int i = pos; i < n; i++) {
        if(_vec[i] == value) 
            return i;
    }
    return -1;
}

bool MyOpt::get(int value) {
    if(_hash.count(value) == 0) 
        return false;
    return true;
}

void MyOpt::put(int value,int pos) {
    if(get(value))
        return ;
    
    if((int)_hash.size() == _capacity) {
        // 删除
        auto it = _list.begin();
        auto del = it;
        auto span = _vec.begin() + pos;
        for(; it != _list.end(); it++) {
            auto it_e = std::find(_vec.begin() + pos,_vec.end(),*it);
            if(it_e == _vec.end()) {
                del = it;
                break;
            } else if(it_e > span){
                span = it_e;
                del = it;
            }
        }
        
        _hash.erase(*del);
        _list.erase(del);
    }

    _list.push_back(value);
    _hash[value] = _list.end()--;
}

void MyOpt::show() {
    for(auto& e : _list)
        cout << e << " ";
    cout << endl;
}
