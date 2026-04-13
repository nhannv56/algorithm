/***

https://www.acmicpc.net/problem/25902
Thủy chiều dâng
algo: bfs
algo: prirority queue
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
struct Node
{
    long long h, t, r, c;
};
struct CompareNode
{
    bool operator()(const Node &x, const Node &y) const
    {
        return x.h < y.h; // max Heap
    }
};
long long R, C;
long long mv[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
string bfs(vector<vector<long long>> &gr)
{
    priority_queue<Node, vector<Node>, CompareNode> pq;
    pq.push({gr[0][0], 0, 0, 0});
    string res = "impossible";
    long long minH = gr[0][0];
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    visited[0][0] = true;
    while (!pq.empty())
    {
        auto [h, t, r, c] = pq.top();
        pq.pop();
        if (r == R - 1 && c == C - 1)
        {
            res = to_string(h);
            break;
        }
        long long nt = t + 1;
        for (long long i = 0; i < 4; ++i)
        {
            long long nc = c + mv[i][0];
            long long nr = r + mv[i][1];
            if (0 <= nr && nr < R && 0 <= nc && nc < C && !visited[nr][nc] && gr[nr][nc] - nt > 0)
            {
                long long nh = gr[nr][nc] - nt;
                visited[nr][nc] = true;                
                pq.push({min(nh,h), nt, nr, nc});
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
    long long T;
    cin >> T;
    while (T > 0)
    {
        cin >> R >> C;
        vector<vector<long long>> gr(R, vector<long long>(C));
        for (long long i = 0; i < R; ++i)
        {
            for (long long j = 0; j < C; ++j)
            {
                cin >> gr[i][j];
            }
        }
        cout << bfs(gr) << '\n';
        --T;
    }
    return 0;
}
