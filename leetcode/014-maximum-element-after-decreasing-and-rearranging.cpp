//https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/submissions/2053562891/
//algo:sort

class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int res = 0;
        sort(arr.begin(), arr.end());
        // for(auto num : arr){
        //     cout<<num<<' ';
        // }cout<<endl;
        arr[0]=1;
        for(int i = 1; i < arr.size(); ++i){
            if(abs(arr[i]-arr[i-1]) > 1){//decrease
                arr[i]= arr[i-1]+1;
            }
        }
        return *arr.rbegin();
    }
};
