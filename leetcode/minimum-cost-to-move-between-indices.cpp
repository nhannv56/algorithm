
class Solution {
//https://leetcode.com/problems/minimum-cost-to-move-between-indices/
public:
    vector<int> minCost(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> indices(nums.size(), 0);
        int closestI = 0;
        for(int i = 0; i < nums.size();++i){            
            if(i == 0){
                closestI= i+1;
            }
            if(i == nums.size()-1){
                closestI = nums.size()-2;
            }
            if(i > 0 && i < nums.size()-1){
                if(abs(nums[i-1] -nums[i])== abs(nums[i]-nums[i+1])){
                    closestI = i-1;
                }else{
                    closestI = abs(nums[i-1] -nums[i]) < abs(nums[i]-nums[i+1])? i-1:i+1;
                }
            }
            indices[i]= closestI;
        }
        for(auto it : indices){
            cout<<it<<" ";
        }
        vector<int> res;
        for(auto [l,r]: queries){
            bool visits[nums.size()]={false,};
            deque<pair<int,int> dq;
            dq.push_back({l,0});
            res.push_back(abs(nums[l]-nums[r]));
            while(!dq.empty()){
                auto [i,dis] = dq.front(); dq.pop_front();
                if(!visits[i]){
                    visits[i] = true;

                }
            }
        }
        return res;
    }
};
