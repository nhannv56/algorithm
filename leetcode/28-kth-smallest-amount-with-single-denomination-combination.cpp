//https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/?envType=daily-question&envId=2026-08-21
/** algo: Nguyên lý Bao hàm - Loại trừ (Inclusion-Exclusion Principle - PIE) kết hợp với Bitmask.
    algo: binary search
    bội chung nhỏ nhất khi kết hợp các số lẻ thì tăng, chẵn thì giảm
**/
class Solution {
public:
    bool valid(long long N, vector<int>& coins, long long& k) {
        int S = coins.size();
        long long res = 0;
        for(int i = 1; i < (1<<S); ++i){
            long long lcm = 1;
            int bits = 0;
            bool overflow = false;
            for(int j = 0; j < S; ++j){
                if((i>>j)&1){
                    bits++;
                    // //kiểm tra nếu tràn
                    // if(N / coins[j] < lcm){
                    //     overflow = true;
                    //     break;
                    // }
                    lcm = (coins[j]*lcm)/gcd(coins[j],lcm);
                }
            }
            // if(!overflow){
                if(bits%2 == 1){
                    res+=N/lcm;
                }else{
                    res-=N/lcm;
                }
            // }
        }
        return res >=k;
    }
    long long findKthSmallest(vector<int>& coins, long long k) {
        long long l = 1, r = 25 * k;
        long long res = r;
        while (l <= r) {
            auto mid = (l + r) / 2;
            if (valid(mid, coins, k)) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return res;
    }
};
