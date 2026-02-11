/******************************************************************************

https://www.acmicpc.net/problem/23019
algo:dp
algo:dijkstra
algo:shortest path

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
int N,M;
struct Node{
    long long d=LLONG_MAX ,c=2500,p;//distance, cost, position
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        if(a.d != b.d){
            return a.d > b.d;
        }else{
            return a.c > b.c;
        }
    }
};
long long bfs(vector<long long>& C,vector<vector<pair<long long,long long>>> adj){
    priority_queue<Node,vector<Node>,CompareNode> pq;
    long long res = 0;
    //store at dist[i][j] = k
    //i is city
    //j is fuel cost
    // k is distance min
    vector<vector<long long>> dist(2501, vector<long long>(2501, LLONG_MAX));
    pq.push({0,C[1],1});
    dist[1][C[1]]=0;
    while(!pq.empty()){
        auto [d,c,p] = pq.top(); pq.pop();
        // cout<<pos<<" "<<len<<" "<<cost<<endl;
        if(p == N){
            return d;
        }
        
        if(d > dist[p][c] ) continue;
        for(auto [np, s] : adj[p]){
            auto nd = d + s*c;
            auto nc = min(c, C[np]);
            if(nd < dist[np][nc]){
                dist[np][nc] = nd;
                pq.push({nd, nc, np});
            }
        
        }
    }
    return res;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    
    cin>>N>>M;
    vector<long long> C(N+1);
    long long u,v,d;
    vector<vector<pair<long long,long long>>> adj(N+1);
    for(int i = 1; i <= N;++i){
        cin>>C[i];
    }
    for(int i = 0; i < M; ++i){
        cin>>u>>v>>d;
        adj[u].push_back({v,d});
        adj[v].push_back({u,d});
    }
    auto res = bfs(C,adj);
    cout<<res<<'\n';
	return 0;
}