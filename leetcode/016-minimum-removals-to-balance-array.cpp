/**
https://leetcode.com/problems/minimum-removals-to-balance-array/?envType=daily-question&envId=2026-07-04
algo: sliding window
**/

class Solution {
public:
    int minRemoval(vector<int>& nums, long long k) {
        map<long long, int> m;
        for (int n : nums) {
            if (m.find(n) == m.end()) {
                m[n] = 1;
            } else {
                m[n]++;
            }
        }
        int res = nums.size();
        auto l = m.begin(), r = m.begin();
        int count = 0;
        while (r != m.end()) {
            // cout<<"loop"<<endl;
            
            while (l->first * k < r->first) {
                count -= l->second;
                // cout<<l->first<<" "<<r->first<<endl<< " count:"<<count<<endl;
                res = min(res, (int)nums.size() - count);
                ++l;
            }        
            while (r != m.end() && r->first <= l->first * k) {
                count += r->second;
                // cout<<l->first<<" "<<r->first<<endl<< " count:"<<count<<endl;
                res = min(res, (int)nums.size() - count);
                ++r;
            }    
        }
        return res;
    }
};
