#include <vector>
#include <algorithm>
using namespace std;

class SSFT {
    public:
        SSFT(vector<int>& vec,int start) {
           _pos = start;
            _vec = vec;
            _vis = vector<bool> (_vec.size(),false);
        }

        int slove() {
            int p = -1;
            int span = 0x3f3f3f3f;
            int n =  _vec.size();

            for(int i = 0; i < n; i++) {
                if(_vis[i]) continue;

                int t = abs(_vec[i] - _pos);
                if(t < span) {
                    p = i;
                    span = t;
                }
            }

            _vis[p] = true;
            int ret = span;
            _pos = _vec[p];
            return ret;
        }
    private:
        vector<int> _vec;
        vector<bool> _vis;
        int         _pos;
};
