/******************************************************************************

https://www.acmicpc.net/problem/17270
algo:dijkstra

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
long long N,M;

struct Node{
    int u, w;//len, parent, cur
};

// vector<int> visited(101,-1);


struct CompareNode {
    bool operator()(const Node& x, const Node& y) const {
        return x.w > y.w; // min-heap theo len
    }
};
static void dijkstra(int s, const vector<vector<pair<int,int>>>& al, vector<int>& dist) {
    dist.assign(dist.size(), INT_MAX);
    priority_queue<Node, vector<Node>, CompareNode> pq;

    dist[s] = 0;
    pq.push({s, 0});

    while (!pq.empty()) {
        auto [u,d] = pq.top(); pq.pop();

        // stale entry
        if (d != dist[u]) continue;

        for (auto [v, w] : al[u]) {
            int nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({v, nd});
            }
        }
    }
}

long long solve(int j, int s, vector<vector<pair<int,int>>>& al){
    vector<int> jvisited(N+1, INT_MAX);
    vector<int> svisited(N+1, INT_MAX);
    dijkstra(j, al, jvisited);
    dijkstra(s, al, svisited);
    // for(int i = 0; i < N+1; i++){
    //     cout<<"from "<<j<< " to "<< i<< "="<<jvisited[i]<<endl;
    //     //cout<<"from "<<s<< " to "<< i<< "="<<svisited[i]<<endl;
    // }
    int res = -1;
    int jdisMin = INT_MAX;
    int minHaveMid = INT_MAX;
    for(int i = 1; i < jvisited.size();++i){
        if(i != j && i != s && jvisited[i] != INT_MAX && svisited[i]!= INT_MAX)
            minHaveMid = min(minHaveMid,jvisited[i]+svisited[i]);
    }
    for(int i = 1; i < jvisited.size(); i++){ //condition 4.2
        int total = jvisited[i] + svisited[i];
        if(i != j && i != s && jvisited[i] != INT_MAX && svisited[i]!= INT_MAX && total == minHaveMid){//1 & 2
            if(jvisited[i] <= svisited[i]){
                if(jdisMin > jvisited[i]){
                    jdisMin = jvisited[i];
                    res = i;
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
    cin>>N>>M;
    int p1, p2, w;
    //cout<<"N,M:"<<N<<","<<M<<endl;
    int j,s;
    vector<vector<pair<int,int>>> al(N+1);
    for(int i = 0; i < M;++i){
        cin>>p1>>p2>>w;
        al[p1].push_back({p2,w});
        al[p2].push_back({p1,w});
    }
    cin>>j>>s;
    //cout<<"JS:"<<j<<" "<<s<<endl;
    cout<<solve(j, s, al);
	return 0;
}