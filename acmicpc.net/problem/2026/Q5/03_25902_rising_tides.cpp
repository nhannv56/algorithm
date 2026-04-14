/***

https://www.acmicpc.net/problem/25902
Thủy chiều dâng
algo: bfs
algo: priority queue
giải thích thuật toán:
- Sử dụng BFS với priority queue để tìm đường đi từ (0, 0) đến (R-1, C-1) sao cho độ cao tối thiểu trên đường đi là lớn nhất.
- Mỗi node trong priority queue sẽ chứa thông tin về độ cao hiện tại, thời gian đã trôi qua, và vị trí (r, c).
- Khi mở một node, nếu đã đến đích (R-1, C-1), cập nhật kết quả với độ cao tối thiểu trên đường đi.
- Với mỗi node, duyệt qua 4 hướng di chuyển (lên, xuống, trái, phải). Nếu vị trí mới hợp lệ và nước chưa ngập, tính độ cao mới sau khi trôi qua thời gian và đẩy node mới vào priority queue.
- Sử dụng một cấu trúc dữ liệu visited để lưu trữ các trạng thái đã thăm, 
tránh việc thăm lại những trạng thái không tối ưu 
(nếu đã có một trạng thái với độ cao cao hơn và thời gian ít hơn, thì bỏ qua trạng thái mới).

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
    // visited[r][c] = vector of pairs (h, t) where h is the height and t is the time
    vector<vector<vector<pair<int, int>>>> visited(500, vector<vector<pair<int, int>>>(500));
    visited[0][0].push_back({gr[0][0], 0});
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
            if (0 <= nr && nr < R && 0 <= nc && nc < C && nt < R * C && gr[nr][nc] - nt > 0)
            {
                long long nh = gr[nr][nc] - nt;
                bool ignore = false;
                for (auto &v : visited[nr][nc])
                {
                    //kiểm tra điều kiện nếu time lớn hơn và high nhỏ hơn thì bỏ qua -> không tối ưu
                    if (v.first >= nh && v.second <= nt) 
                    {
                        ignore = true;
                        break;
                    }
                }
                if (!ignore)
                {
                    visited[nr][nc].push_back({nh, nt});
                    pq.push({min(nh, h), nt, nr, nc});
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
