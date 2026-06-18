/***
  https://leetcode.com/problems/maximum-subarray/description/
  algo: kandanes's algorithm
  algo: dp (minVal is dp at[i-1] max sub array ket thuc taij i-1
  **/
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        
        int minVal = 0,  maxVal = 0;
        int res = 0;
        for(auto val: nums){
            minVal = min({minVal+val,val});
            maxVal = max({maxVal+val,val});
            // cout<<minVal<<" "<<maxVal<<endl;
            res = max({res, abs(minVal), abs(maxVal)});
        }
        return res;
    }
};
