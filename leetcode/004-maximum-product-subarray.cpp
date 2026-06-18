/***
https://leetcode.com/problems/maximum-product-subarray/
algo: kandanes' algo
algo: dp multipe lưu lại max dương và min âm
  **/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int mV=1,pV =1;
        int res = nums[0];
        for(int i = 0; i < nums.size();++i){
            if(nums[i]==0){
                mV=1;
                pV=1;
                res = max(res, 0);
            }else{
                auto tMV = mV, tPV = pV;
                mV = min({tPV*nums[i],tMV*nums[i],nums[i]});
                pV = max({tPV*nums[i],tMV*nums[i],nums[i]});
                res = max({mV,pV,res});
            }
        }
        return res;
    }
};
