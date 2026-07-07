/**
https://leetcode.com/problems/count-subarrays-with-majority-element-ii/editorial/?envType=daily-question&envId=2026-07-06
You are given an integer array nums and an integer target.

Return the number of subarrays of nums in which target is the majority element.

The majority element of a subarray is the element that appears strictly more than half of the times in that subarray.
Input: nums = [1,2,2,3], target = 2

Output: 5
algo: segment tree
algo: prefix sum

Chuyển đổi sang mảng +1, -1
Build prefix sum trên mảng
Tính trên đoạn có bao nhiêu prefix sum > 0 -> thêm vào kết quả
**/

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        // represents the occurrence count of prefix sums -n, -(n-1), ..., 0, 1,
        // ..., n, with index offset by n.
        vector<int> pre(n * 2 + 1, 0);
        pre[n] = 1;
        int cnt = n;
        long long ans = 0, presum = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                presum += pre[cnt];
                ++cnt;
                ++pre[cnt];
            } else {
                --cnt;
                presum -= pre[cnt];
                ++pre[cnt];
            }
            ans += presum;
        }
        return ans;
    }
};
