/**
https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/?envType=daily-question&envId=2026-07-07
You are given an integer n.

Form a new integer x by concatenating all the non-zero digits of n in their original order. If there are no non-zero digits, x = 0.

Let sum be the sum of digits in x.

Return an integer representing the value of x * sum.
Input: n = 10203004

Output: 12340
algo: bit
algo: digit
**/


class Solution {
public:
    long long sumAndMultiply(int n) {
        stack<long long> st;
        long long sum = 0;
        long long digit;
        
        while(n > 0){
            digit = n%10;
            n/=10;
            if(digit!=0){
                st.push(digit);
                // cout<<digit<<endl;
            }
            sum+=digit;
        }
        if(st.size()==0){
            return 0;
        }
        long long res = 0;
        while(!st.empty()){
            res*=10;
            auto cur = st.top(); st.pop();
            res+=cur;
        }
        return res*sum;
    }
};
