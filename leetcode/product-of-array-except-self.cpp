/**
https://leetcode.com/problems/product-of-array-except-self/
algo: kandanes' algo
algo: precom
algo: dp
**/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> lr(nums.size(),1), rl(nums.size(), 1);
        lr[0] = nums[0];
        for(int i = 1; i < nums.size(); ++i){
            lr[i]=lr[i-1]*nums[i];
            // cout<<i<<" "<<lr[i]<<endl;
        }
        rl[nums.size()-1] = nums[nums.size()-1];
        for(int j = nums.size()-2; j >=0; --j){
            rl[j] = rl[j+1]*nums[j];
            // cout<<j<<" "<<rl[j]<<endl;
        }
        vector<int> res(nums.size(),0);
        res[0]=rl[1];
        res[nums.size()-1]=lr[nums.size()-2];
        for(int i = 1; i < nums.size()-1;++i){
            res[i] = lr[i-1]*rl[i+1];
        }
        return res;
    }
};
