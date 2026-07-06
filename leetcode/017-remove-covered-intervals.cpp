/**
algo: sorting
https://leetcode.com/problems/remove-covered-intervals/?envType=daily-question&envId=2026-07-06
tìm xem có bao nhiêu đoạn nằm trong các đoạn khác
trả về số đoạn không nằm hoàn toàn trong đoạn khác
**/
class Solution {
    class Node{
        public:
        int l, r;
        bool operator < (Node & b)const{
            if(l != b.l){
                return l < b.l;
            }else{
                return r > b.r;
            }
        };
    };
    
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        vector<Node> sortInterval;
        for (auto iv : intervals) {
            sortInterval.push_back({iv[0],iv[1]});
        }
        sort(sortInterval.begin(), sortInterval.end());
        // for(auto [l,r]: sortInterval){
        //     cout<<l <<" "<<r<<endl;
        // }
        auto [fl, fr] = sortInterval[0];
        int maxLen = fr-fl+1;
        int res = intervals.size();
        for(int i = 1; i < sortInterval.size();++i){
            auto [l, r] = sortInterval[i];
            int curLen = r-l+1;
            maxLen = maxLen - (l - sortInterval[i-1].l);
            if(maxLen >=curLen){
                res--;
            }
            maxLen =max(maxLen, curLen);
        }
        return res;
    }
};
