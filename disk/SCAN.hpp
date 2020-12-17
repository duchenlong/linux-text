#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class SCAN{
    public:
        SCAN(int start,bool flag,vector<int>& vec) {
            _pos = start;
            _flag = flag;
            _add = 1;
            _min = *min_element(vec.begin(),vec.end());
            _max = *max_element(vec.begin(),vec.end());
            for(auto& e : vec) {
                _hash.insert(e);
            }
        }

        int slove() {
            int ret = 0;
            while(!_hash.empty()) {
                if(_pos > _max) {
                    if(_flag) {
                        ret += _max - _min - 1;
                        _pos = _min;
                    }
                    else {
                       _add = -1;
                       _pos = _max - 1;
                    }   
                }

                if(_hash.count(_pos) == 0) {
                    _pos+=_add;
                    ret++;
                    continue;
                }
                _hash.erase(_pos);
                break;
            }
            return ret;
        }
    private:
        bool _flag;
        unordered_set<int> _hash;
        int         _pos;
        int         _add;
        int         _min;
        int         _max;
};
