/******************************************************************************
https://www.acmicpc.net/problem/1167
algo:bfs 2 lần
Tìm path dài nhất trong cây
từ 1 điềm bfs dài nhất -> điểm đó sẽ là 1 trong 2 điểm nằm trên cạnh dài nhất
bfs lần 2
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

pair<int,int> bfs(int s, vector<vector<pair<int,int>>>& adj){
    priority_queue<pair<int,int>> pq;
    pq.push({0,s});
    vector<bool> visited(adj.size()+1, false);
    visited[s] = true;
    int tv=1, tw=0;
    while(!pq.empty()){
        auto [w,u] = pq.top(); pq.pop();
        if(w > tw){
            tv = u;
            tw = w;
        }
        for(auto [v,nw]: adj[u]){
            if(!visited[v]){
                visited[v]=true;
                pq.push({nw+w,v});
            }
        }
    }
    return {tv, tw};
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
    int N;
    cin>>N;
    vector<vector<pair<int,int>>> adj(N+1);
    for(int i = 1; i <= N; ++i){
        int u, v, w;
        cin>>u;
        while(true){
            cin>>v;
            if(v == -1){
                break;
            }else{
                cin>>w;
                adj[u].push_back({v,w});
                adj[v].push_back({u,w});
            }
        }
    }
    auto [tv, w1] = bfs(1,adj);
    auto [tu, w2] = bfs(tv, adj);
    cout<<w2;
	return 0;
}
