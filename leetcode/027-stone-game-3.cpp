//https://leetcode.com/problems/stone-game-iii/?envType=daily-question&envId=2026-08-03
// algo: dp
class Solution {
public:
    vector<pair<int, int>> dp =
        vector<pair<int, int>>(5e4, {-1, 0}); // value and selected at round
    pair<int, int> maxScore(vector<int>& sv, int s) {
        if (s >= sv.size()) {
            return {0, 0};
        }
        if (dp[s].first == -1) {
            int v1 = sv[s];
            auto [b1, bc1] = maxScore(sv, s + 1);
            auto [a1, ac1] = maxScore(sv, s + 1 + bc1);
            v1 += a1;

            int v2 = -3000;
            int sz = 1;
            if (s + 1 < sv.size()) {
                v2 = sv[s] + sv[s + 1];
                auto [b2, bc2] = maxScore(sv, s + 2);
                auto [a2, ac2] = maxScore(sv, s + 2 + bc2);
                v2 += a2;
                if (v2 > v1) {
                    sz = 2;
                }
            }
            int v3 = -3000;
            if (s + 2 < sv.size()) {
                v3 = sv[s] + sv[s + 1] + sv[s + 2];
                auto [b3, bc3] = maxScore(sv, s + 3);
                auto [a3, ac3] = maxScore(sv, s + 3 + bc3);
                v3 += a3;
                if (v3 > max(v1, v2)) {
                    sz = 3;
                }
            }
            dp[s] = {max({v1, v2, v3}), sz};
        }
        return dp[s];
    }
    string stoneGameIII(vector<int>& stoneValue) {
        int total = 0;
        for (auto s : stoneValue) {
            total += s;
        }
        //vì đệ quy take time -> đảo ngược cách gọi build từ phải qua trái tránh đệ quy nhiều
        for(int s = stoneValue.size()-3; s >=0;--s){
            maxScore(stoneValue,s);
        }
        //tính kết quả
        auto [alice, c] = maxScore(stoneValue, 0);
        if (alice * 2 == total) {
            return "Tie";
        } else if (alice * 2 > total) {
            return "Alice";
        } else {
            return "Bob";
        }
    }
};
