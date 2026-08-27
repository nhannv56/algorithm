/**
https://leetcode.com/problems/stone-game-v
algo: dp
algo: game theory
**/
class Solution {
public:
    vector<int> pre = vector<int>(501,0);
    vector<vector<int>> dp = vector<vector<int>>(500, vector<int>(500, -1));
    int round(int s, int e, vector<int>& stone) {
        if(e==s){
            return 0;
        }
        if (e - s == 1) {
            return min(stone[e], stone[s]);
        }
        if (dp[s][e] == -1) {
            // dp[s][e] = 0;
            for (int i = s; i < e; ++i) {
                int s1 = s, e1 = i;
                int s2 = i + 1, e2 = e;
                int sum1 = pre[e1 + 1] - pre[s1];
                int sum2 = pre[e2 + 1] - pre[s2];
                int tres = min(sum1, sum2);
                if (sum1 > sum2) {
                    tres += round(s2, e2, stone);
                } else if (sum1 < sum2) {
                    tres += round(s1, e1, stone);
                } else {
                    auto r1 = round(s1, e1, stone);
                    auto r2 = round(s2, e2, stone);
                    tres += max(r1, r2);
                }

                dp[s][e] = max(dp[s][e], tres);
            }
        }
        return dp[s][e];
    }
    int stoneGameV(vector<int>& stoneValue) {
        // pre.resize(stoneValue.size() + 1, 0);
        for (int i = 0; i < stoneValue.size(); ++i) {
            pre[i + 1] = pre[i] + stoneValue[i];
            // cout<<pre[i+1]<<endl;
        }
        // for (int i = 1; i < stoneValue.size() - 1; ++i) {
        //     round(0, i, stoneValue);
        // }
        return round(0, stoneValue.size() - 1, stoneValue);
    }
};
