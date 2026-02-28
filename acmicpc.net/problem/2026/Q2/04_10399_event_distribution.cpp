/******************************************************************************
https://www.acmicpc.net/problem/10399
algo:bfs
algo:gcd
Duyệt từ tất cả các điểm
tại mỗi điểm khi ghé thăm mà có 1 gcd mới sẽ có 1 bộ có thể xem
xét -> đẩy vào queue
=> đảm bảo tất cả các cặp được xem xét
bắt đầu từ a, b, c enque
a-> b tại b ta có a, gcd(a,b)
b->c tại c ta có kế hợp ac, c gcd(a,b)->xét tại b sẽ có 
abc hoặc b->c
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int I, S;
std::unordered_set<int> res;
void bfs(vector<int> &C,vector<vector<int>>& adj){
    deque<pair<int,int>> dq;
    vector<unordered_set<int>>visited(I+1);
    for(int i = 1; i <=I;++i){
        dq.push_back({i,C[i]});
        res.insert(C[i]);
        visited[i].insert({C[i]});
    }
    while(!dq.empty()){
        auto [u,cgcd] = dq.front(); dq.pop_front();
        for(auto v : adj[u]){
            int next_gcd = gcd(cgcd, C[v]);
            if(visited[v].find(next_gcd)== visited[v].end()){
                dq.push_back({v,next_gcd});
                visited[v].insert(next_gcd);
                res.insert(next_gcd);
            }
        }
    }   
}
int solve(vector<int> &C, vector<vector<int>>& adj){
   bfs(C,adj);
    return res.size();
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
    cin>>I>>S;
    vector<int> C(I+1);
    vector<vector<int>> adj(I+1);
    for(int i = 1; i <= I; ++i){
        cin>>C[i];
    }
    int u,v;
    for(int i = 0; i < S;++i){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout<<solve(C, adj);
	return 0;
}