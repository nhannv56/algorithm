/******************************************************************************

https://www.spoj.com/problems/ADATRIP/
algo: dijktra
desc: Đếm số đường đi ngắn nhất từ u đến v, 
nếu có nhiều đường đi ngắn nhất thì đếm tất cả các đường đi đó. 
Đường đi ngắn nhất là đường đi có tổng trọng số nhỏ nhất. 
Nếu không có đường đi nào từ u đến v thì in ra -1 0.

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
int N, M, Q;
struct Node
{
    long long p, d; // distance, cost, position
};

struct CompareNode
{
    bool operator()(const Node &a, const Node &b)
    {
        return a.d > b.d;
    }
};
std::pair<long long, long long> dijkstra(long long &_u, vector<vector<pair<long long, long long>>> &adj)
{

    priority_queue<Node, vector<Node>, CompareNode> pq; // min heap
    long long res = LLONG_MAX;
    // distance to v min
    vector<long long> dist(N + 1, LLONG_MAX);// distance to v min
    vector<bool> visited(N + 1, false);// check if visited
    vector<bool> counted(N + 1, false);// check if counted in result
    pq.push({_u, 0});
    dist[_u] = 0;
    visited[_u] = true;
    long long dis = 0;
    long long counts = 0;

    while (!pq.empty())
    {
        auto [p, d] = pq.top();
        pq.pop();
        // cout<<pos<<" "<<len<<" "<<cost<<endl;
        if(counted[p]) continue;// nếu đã đếm rồi thì bỏ qua việc đếm lại con đường dài hơn là sai
        if (d > dis)
        {
            counts = 1;
            dis = d;
            counted[p] = true;
        }
        else if (d == dis && !counted[p])
        {
            counted[p] = true;
            counts++;
        }

        for (auto [v, weight] : adj[p])
        {
            auto nd = d + weight;
            if (nd < dist[v])
            {
                dist[v] = nd;
                pq.push({v, nd});
                visited[v] = true;
            }else if (nd == dist[v] && !visited[v])
            {
                pq.push({v, nd});
                visited[v] = true;
            }
        }
    }
    return {counts, dis};
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

    cin >> N >> M >> Q;
    long long u, v, d;
    vector<vector<pair<long long, long long>>> adj(N + 1);
    for (int i = 0; i < N; ++i)
    {
        adj[i].push_back({i, 0});
    }
    for (int i = 1; i <= M; ++i)
    {
        cin >> u >> v >> d;
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }

    for (int i = 0; i < Q; ++i)
    {
        cin >> u;
        auto [num, dis] = dijkstra(u, adj);
        cout << dis << " " << num << endl;
    }
    return 0;
}