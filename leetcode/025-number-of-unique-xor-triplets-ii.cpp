/**
You are given an integer array nums.

A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.

Return the number of unique XOR triplet values from all possible triplets (i, j, k).
1 <= nums.length <= 1500
1 <= nums[i] <= 1500
aglo: bit
  */
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        vector<bool> visited(15001, false), result(15001, false);
        // for(auto num: nums){
        //     visited[num]=true;
        // }
        int xorV = 0;
        int res = 0;
        vector<pair<int,int>> cand;
        for(int i = 0; i < nums.size(); ++i){
            for(int j = i; j < nums.size();++j){
                xorV = nums[i]^ nums[j];
                if(!visited[xorV]){
                    cand.push_back({xorV,i*nums.size()+j});
                    visited[xorV]=true;
                }
            }
        }
        // for(int it : cand){
        //     cout<<it<<" ";
        // }cout<<endl;
        for(int i = 0; i < cand.size();++i){
            for(int j = cand[i].second % nums.size(); j < nums.size(); ++j){
                xorV = cand[i].first ^nums[j];
                if(!result[xorV]){
                    // cout<<xorV<<' ';
                    result[xorV]=true;
                    ++res;
                }
            }
        }
        return res;
    }
};
