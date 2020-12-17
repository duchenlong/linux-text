#include <vector>
#include <algorithm>

using namespace std;

class FCFS{
    public:
        FCFS(int start,vector<int> vec) 
            :_vec(vec)
        {
            _start = start;
        }

        int slove(int pos) {
            int ret = abs(_vec[pos] - _start);
            _start = _vec[pos];
            return ret;
        }
    private:
        vector<int>     _vec;
        int             _start;
};
