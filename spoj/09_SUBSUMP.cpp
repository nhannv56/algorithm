/******************************************************************************

https://spoj.com/problems/SUBSUMP/

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <cctype>
using namespace std;
int T, N, V, FreeSize;
vector<bool>visited(12, false);
vector<vector<int>> combine;
vector<pair<int, int>> pos;
int res = 0;
void genCombine(const int& sum, int minVal, const int &n, vector<int>& cur)
{
    if (sum < 0 || cur.size() > FreeSize)
    {
        return;
    }
    if (cur.size() == FreeSize)
    {
        if (sum == 0)
        {
            combine.push_back(cur);
        }
        return;
    }

    for (int i = minVal; i <= n; ++i)
    {
        cur.push_back(i);
        genCombine(sum - i, i, n, cur);
        cur.pop_back();
    }
}
bool canPush(int & val, int pI, vector<vector<int>>& used){
    
    auto [x,y] = pos[pI];
    if((used[0][x] & (1<<val)) || (used[1][y] & (1<<val))){
        return false;
    }
    return true;
}
void backtrack(const int idx, vector<int>& cand, int pI,  vector<vector<int>>& gr, int cnt, vector<vector<int>>& used){ //numI in combine
    
    if(canPush(cand[idx], pI, used)){                
        ++cnt;
        auto [x,y] = pos[pI];
        // gr[x][y] = cand[idx];
        used[0][x] |= (1<<cand[idx]);
        used[1][y] |= (1<<cand[idx]);
        visited[idx]=true;
        pI++;
        if(cnt==pos.size()){
            ++res;
        }else{
            int pre = -1;
            vector<bool> selected(13,false);
            for(int i = 0; i < cand.size();++i){
                if(!visited[i]){
                    if(!selected[cand[i]] && pI < pos.size()){
                        selected[cand[i]] = true;
                        backtrack(i,cand,pI,gr, cnt, used);
                    }
                }
            }
        }
        visited[idx]= false;
        // gr[x][y] = 0;
        used[0][x] &= ~(1<<cand[idx]);
        used[1][y] &= ~(1<<cand[idx]);
    }
}
int solve(vector<string> grid)
{
    combine.clear();
    vector<int> initV;
    genCombine(V, 1, N, initV);
    int pi = -1, pj = -1;
    vector<vector<int>> gr(N, vector<int>(N, 0));
    map<long long, int> counting;
    for(auto c : combine){
        vector<long long> countSame(13,0);
        int pre = c[0];
        int sameNumCount = 0;
  
        for(int num: c){
            if(pre==num){
                sameNumCount++;
            }else{
                ++countSame[sameNumCount];
                sameNumCount=1;
            }
            pre=num;
        }
        countSame[sameNumCount]++;
        long long num = 0;     
        for(int i = 1; i < countSame.size();++i){
            if(countSame[i]!=0){
                num |= countSame[i]<<((i-1)*4);
            } 
        }
        if(counting.find(num) == counting.end()){
            counting[num] = 1;
        } else {
            ++counting[num];
        }
    }

    int total = 0;
    for(auto [p, c] : counting){
        vector<int> cand;
        int label = 1;
        auto pp = p;
        int bit = 1;
        while(pp > 0){
            long long tmp = pp&0b1111;
            for(long long i = 1; i <= tmp; ++i){
                for(long long j = 0; j < bit; ++j){
                    cand.push_back(label);
                }
                ++label;
            }
            ++bit;
            pp >>= 4;
        }

        for(int j = 0; j < cand.size();++j){
            if(j==0 || cand[j]!= cand[j-1]){
                int fillCount = 0;
                res=0;
                vector<vector<int>> used(2, vector<int>(13,0));//row is 0 cols is 1
                backtrack(j, cand, 0, gr,fillCount, used);

                total +=res*c;
            }
        }
    }
    return total;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
#endif
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        cin >> N >> V;
        vector<string> grid(N);
        FreeSize = 0;
        pos.clear();
        for (int i = 0; i < N; ++i)
        {
            cin >> grid[i];
            for (int j = 0; j < grid[i].length(); ++j)
            {
                if (grid[i][j] == '.')
                {
                    pos.push_back({i, j});
                    FreeSize++;
                }
            }
        }
  
        auto f = solve(grid);
        cout << "Case " << t << ": " << f << '\n';
    }
    return 0;
}
