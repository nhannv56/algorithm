/**
algo: prefix sum
algo: precompute
tính chi phí di  chuyển a->b
tính trước chi phí dùng prefix sum trái qua phải, phải qua trái
min chi phí gần nhau giữa 2 điểm là closet -> max là adj
*/
class Solution {
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
        // for(auto it : indices){
        //     cout<<it<<" ";
        // }cout<<endl;
        vector<int> res,pre1(nums.size(),0),pre2(nums.size(),0);
        for(int i = 1; i < indices.size();++i){
            if(indices[i-1]==i){
                 pre1[i]=pre1[i-1]+1;
            }else{
                 pre1[i]=pre1[i-1]+abs(nums[i-1]-nums[i]);
            }
            //cout<<pre1[i]<<" ";
        }//cout<<endl;
        for(int i = indices.size()-2; i >= 0; --i){
            if(indices[i+1]==i){
                pre2[i] = pre2[i+1]+1;
            }else{
                pre2[i]=pre2[i+1]+abs(nums[i+1]-nums[i]);
            }
        }
        for(auto q : queries){
            auto l=q[0], r=q[1];
            int qres = 0;
            if(l == r){
                res.push_back(0);
            }else if (l < r){
                res.push_back(pre1[r]-pre1[l]);
            }else{
                res.push_back(pre2[r]-pre2[l]);
            }
        }
        return res;
    }
};
