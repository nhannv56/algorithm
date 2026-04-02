/***
 * https://www.acmicpc.net/problem/14044
 * PHONOMENAL REVIEWS
 * algo: dp on tree
 */

#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

int N, M;
const int INF = -1e9;
vector<int> phoRes;
vector<vector<int>> adj;
vector<vector<int>> dp;
int cal(int u){
   int res = INT_MAX;
   for(auto v : adj[u]){
      if(dp[u][v] > INF){
         res+= dp[u][v];
      }
      //xây từ dưới lên
      int best = cal(v);
      if(best > INF){
         dp[u][v] = best + 1;
      }
   }
}
int solve(){
   int res = INT_MAX;
   for(int i = 0; i < M; ++i){
      res = min(res, cal(phoRes[i]));
   }
   return res;
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
   cin >> N >> M;
   phoRes.resize(M);
   adj.resize(N + 1);
   dp.resize(N + 1);

   for (int i = 0; i < M; ++i)
   {
      cin>>phoRes[i];
   }

   for (int i = 0; i < N ; ++i)
   {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
   for(int i = 1; i <= N; ++i){
      sort(adj[i].begin(), adj[i].end());
      dp[i].resize(adj[i].size(), INF);
   }
   cout<<solve();
   return 0;
}
