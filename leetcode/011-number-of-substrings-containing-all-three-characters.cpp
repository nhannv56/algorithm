/**
https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/?envType=daily-question&envId=2026-06-30
algo: string
algo: counting
**/

class Solution {
public:
    int numberOfSubstrings(string s) {
        int res = 0;
        vector<queue<int>> counting(3);
        for(int i = 0; i < s.length(); ++i){
            counting[s[i]-'a'].push(i);
        }
        while(!counting[0].empty() && !counting[1].empty()&& !counting[2].empty()){
            int maxI = max({counting[0].front(), counting[1].front(), counting[2].front()});
            res+=s.length()-maxI;
            int minI = min({counting[0].front(), counting[1].front(), counting[2].front()});
            if(minI== counting[0].front()){
                counting[0].pop();
            }else if(minI== counting[1].front()){
                counting[1].pop();
            }else{
                counting[2].pop();
            }
        }
        return res;
    }
};
