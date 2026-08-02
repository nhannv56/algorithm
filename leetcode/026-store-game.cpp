//https://leetcode.com/problems/stone-game/description/?envType=daily-question&envId=2026-08-02
// alice & bob chose left and right for max score
// algo: game theory
// algo: dp 2 player
class Solution {
public:
    vector<vector<pair<int,bool>>> dp = vector<vector<pair<int,bool>>>(500, vector<pair<int,bool>>(500, {-1, false}));
    pair<int,bool> maxScore(vector<int>& piles, int i, int j) {
        if (i > j) {
            return {0,false};
        }
        if (i == j) {
            return {piles[i],false};
        }
        
        if (dp[i][j].first == -1) {
            int l = piles[i];
            auto [other,leftSelect] = maxScore(piles, i + 1, j);
            if (leftSelect) {
                l += maxScore(piles, i + 2, j).first;
            } else {
                l += maxScore(piles, i + 1, j - 1).first;
            }
            int r = piles[j];
            auto [rother,rselect] = maxScore(piles, i, j - 1);
            if (rselect) {
                r += maxScore(piles, i + 1, j - 1).first;
            } else {
                r += maxScore(piles, i, j - 2).first;
            }

            bool left = (l >= r);
            dp[i][j] = {max(l, r),left};
            
        }
        return dp[i][j];
    }
    bool stoneGame(vector<int>& piles) {
        int total = 0;
        for(auto p : piles){
            total+=p;
        }
        auto [alice,left] = maxScore(piles, 0, piles.size()-1);
        return (alice*2 >= total);
    }
};
