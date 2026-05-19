/******************************************************************************

https://spoj.com/problems/KEQUALITY/
algo: bfs
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
long long N, Q;
vector<map<int,int>> dp(1e5);
int cal(int u, int v, vector<vector<int>> &adj){
    if(adj[v].size() == 1){
        // cout<<"cal u:"<<u<<" v:"<<v<<" leaf"<<endl;
        return 1;
    }
    int cnt = 0;
    // cout<<"cal u:"<<u<<" v:---------"<<v<<endl;
    if(dp[u].find(v) == dp[u].end()){
        for( int nv : adj[v]){
            if(nv != u){
                cnt+=cal(v,nv, adj);
                // cout<<"cal u:"<<u<<" v:"<<v<<" nv:"<<nv<<" cnt:"<<cnt<<endl;
            }
        }
        dp[u][v] = cnt+1;
    }
    // cout<<"final u:"<<u<<" v:"<<v<<" cnt:"<<dp[u][v]<<endl;
    return dp[u][v];
}
int solve(vector<vector<int>> &adj, vector<int> &startPoints)
{
    int res = 0;
    // visited[0] number of visiter
    // visited[1] distance
    vector<vector<int>> visited(2, vector<int>(N + 1, 0));
    deque<pair<int, int>> q; // distance and node
    sort(startPoints.begin(), startPoints.end());
    int prev = -1;
    for (int sp : startPoints)
    {
        if (prev == -1 || sp != prev)
        {
            prev = sp;
            visited[0][sp]++;
            q.push_back({0, sp});
        }
        else
        {
            visited[0][sp]++;
        }
    }
    while (!q.empty())
    {
        auto [dist, node] = q.front();
        q.pop_front();
        // visited[1][node] = dist;
        // cout<<"node:"<<node<<" dist:"<<dist<<" visited:"<<visited[0][node]<<endl;
        if (visited[0][node] >= startPoints.size())
        {
            for(int v : adj[node]){
                // cout<<"node:"<<node<<" v:"<<v<<" visited:"<<visited[0][v]<<" dp:"<<dp[node][v]<<endl;
                if(visited[0][v] == 0){
                    res+=dp[node][v];
                }
            }
            ++res;
            return res;
        }
        for (int neighbor : adj[node])
        {
            if (visited[0][neighbor] == 0)
            {
                visited[0][neighbor] = visited[0][node];
                visited[1][neighbor] = dist + 1;
                q.push_back({dist + 1, neighbor});
            }
            else
            {
                if (visited[1][neighbor] == dist + 1)
                {
                    visited[0][neighbor] += visited[0][node];
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

    cin >> N;
    vector<vector<int>> adj(N + 1);
    int u, v, k;
    for (long long i = 0; i < N - 1; ++i)
    {
        cin >> u >> v >> k;
        if (k == 1)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    for(int u =1; u<=N; ++u){
        for(int v: adj[u]){
            cal(u,v, adj);
        }
    }
    cin >> Q;
    for (int i = 0; i < Q; ++i)
    {
        int qi;
        vector<int> startPoints;
        cin >> qi;
        for (int j = 0; j < qi; ++j)
        {
            int sp;
            cin >> sp;
            startPoints.push_back(sp);
        }
        cout << solve(adj, startPoints) << endl;
    }
    return 0;
}
