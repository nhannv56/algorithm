/******************************************************************************

https://www.acmicpc.net/problem/24470
algo:dp 2 trọng số cho diktra 
algo:dijkstra
algo:shortest path
Đồ thị có hướng
Dùng dijktra có trọng số k để duyệt khi K > 0 còn đẩy vào queue
dist khai báo đủ cho N và K
dùng matrix lưu thay vì cạnh kề vì số cạnh quá lớn và số đỉnh thì nhỏ

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
int N,M;
struct Node{
    long long p, d, k;//distance, cost, position
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.d > b.d;
    }
};
long long dijkstra(long long& _u, long long& _v, long long& _k, vector<vector<long long>>& matrix){
    
    priority_queue<Node,vector<Node>,CompareNode> pq;//min heap
    long long res = LLONG_MAX;
    //lưu lại khoảng cách nhỏ nhất với k tương ứng
    vector<vector<long long>> dist(N+1, vector<long long>(141, LLONG_MAX));

    pq.push({_u,0,_k});
    dist[_u][_u]=0;
    
    while(!pq.empty()){
        auto [p,d,k] = pq.top(); pq.pop();
        // cout<<pos<<" "<<len<<" "<<cost<<endl;
        if(p == _v){
            return d;
        }
        
        if(k==0 || d > dist[p][k] ) continue;
        for( int v = 1; v <= N; ++v ){
            if(matrix[p][v] != LLONG_MAX){
                auto nd = d + matrix[p][v];
                auto nk = k-1;
                if(nd < dist[v][nk]){
                    dist[v][nk] = nd;
                    pq.push({v, nd, nk});
                }        
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
    
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
    #endif
    
    cin>>N>>M;
    long long u,v,d;
    vector<vector<long long>> matrix(N+1, vector<long long>(N+1, LLONG_MAX));
    for(int i = 1; i <= M;++i){
        cin>>u>>v>>d;
        matrix[u][v]= min(matrix[u][v],d);
    }
    long long k,q;
    cin>>k>>q;
    // đồ thị có hướng nên k có thể tối đa là 2*N-1
    if(k > 140){ //reduce k
        k = 140;
    }
    for(int i = 0; i < q;++i){
        cin>>u>>v;
        auto res = dijkstra(u,v,k, matrix);
        if(res == LLONG_MAX){// trường hợp ko có đường đi phù hợp -1
            cout<<-1<<'\n';
        }else{
            cout<<res<<'\n';
        }
    }
	return 0;
}