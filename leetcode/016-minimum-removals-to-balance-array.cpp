/**
algo: sliding window
https://leetcode.com/problems/minimum-removals-to-balance-array/?envType=daily-question&envId=2026-07-04
**/

class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int res = nums.size();
        auto l = 0, r = 0;
        while (r < nums.size()) {
            while ((long long)((long long)nums[l] * (long long)k) < (long long)nums[r]) {
                // res = min(res, (int)nums.size() - (r - l + 1));
                // cout<<l<<" "<<r<<" "<<res<<endl;
                ++l;
            }
            while (r < nums.size() && (long long)((long long)nums[l] * (long long)k) >= (long long)nums[r]) {
                res = min(res, (int)nums.size() - (r - l + 1));
                // cout<<l<<" "<<r<<" "<<res<<endl;
                ++r;
            }
            
        }
        return res;
    }
};
