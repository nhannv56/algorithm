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
vector<vector<int>> dpuvu; //min u->v ... ->v -> u
vector<bool>visited;
pair<int, bool> cal(int u,int vi){
   int v= adj[u][vi];
   // cout<<"from "  << u<< " to "<<v<<endl;
   if(dpuvu[u][vi] != -1){
      // cout<<u<<" to "<<adj[u][vi]<<" dis:"<<dpuvu[u][vi]<<endl;
      return {dpuvu[u][vi],dpuvu[u][vi]>0};
   }
   int res = 2;
   visited[u]= true;
   visited[v]= true;
   auto it = find(phoRes.begin(), phoRes.end(),v);
   bool phoFromV = (it != phoRes.end());
   int i = 0;
   for(auto vv : adj[v]){
      // cout<<"next:"<<vv<<" visit:"<<visited[vv]<<endl;
      if(!visited[vv]){
         auto [dis,havePho] = cal(v, i);
         if(havePho){
            phoFromV = true;
            dpuvu[v][i] = dis;
         }
         res+=dpuvu[v][i];
      }
      ++i;
   }
   if(phoFromV){
      dpuvu[u][vi] = res;
   }else{
      dpuvu[u][vi] = 0;
   }
   // cout<<u<<" to "<<adj[u][vi]<<" dis:"<<dpuvu[u][vi]<<endl;
   return {dpuvu[u][vi], phoFromV};
}
int solve(){
   int res = INT_MAX;
   //tính min đi từ u ->v ... ->v ->u qua tất cả các điểm yêu cầu
   visited.resize(N, false);
   for(int i = 0; i < M; ++i){
      cout<<"cal "<<phoRes[i]<<endl;
      fill(visited.begin(),visited.end(),false);
      for(int j = 0; j < adj[phoRes[i]].size();++j){
         cal(phoRes[i],j);
      }
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
   adj.resize(N );
   dpuvu.resize(N );

   for (int i = 0; i < M; ++i)
   {
      cin>>phoRes[i];
   }
   sort(phoRes.begin(), phoRes.end());
   for (int i = 0; i < N-1 ; ++i)
   {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
   for(int i = 0; i < N; ++i){
      sort(adj[i].begin(), adj[i].end());
      dpuvu[i].resize(adj[i].size(), -1);
   }
   cout<<solve();
   return 0;
}
