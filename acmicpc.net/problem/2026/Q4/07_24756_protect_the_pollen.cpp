/***
 * https://www.acmicpc.net/problem/24756
 * TÓM TẮT ĐỀ BÀI VÀ PHƯƠNG PHÁP GIẢI: FLARIANA FLOWERS
algo: dp on tree
algo: knapsack
---
1. Tóm tắt đề bài
- Cấu trúc: N bông hoa (N <= 300) nối thành một Cây (Tree).
- Dữ liệu mỗi hoa k: s_k (số lượng ong), p_k (sức mạnh).
- Giới hạn: Tổng số ong chọn đi <= S (S <= 300).
- Điều kiện: Với mỗi cạnh (u, v), không được chọn cả hai gia đình u và v cùng đi.
- Mục tiêu: Tìm tổng sức mạnh p_k lớn nhất.

---
2. Phương pháp giải: Tree DP + Knapsack
Đây là bài toán tìm Tập độc lập có trọng số (Independent Set) trên cây kết hợp giới hạn cái túi (Knapsack).

Trạng thái DP:
dp[u][j][state]: Sức mạnh lớn nhất ở cây con gốc u, dùng j con ong.
- state = 0: Không chọn u.
- state = 1: Có chọn u.

Công thức truy hồi (Khi gộp con v vào cha u):
1. Nếu không chọn u (state=0):
   dp[u][j+k][0] = max(dp[u][j][0] + max(dp[v][k][0], dp[v][k][1]))
2. Nếu có chọn u (state=1):
   dp[u][j+k][1] = max(dp[u][j][1] + dp[v][k][0])

Khởi tạo:
- dp[u][0][0] = 0
- Nếu s_u <= S: dp[u][s_u][1] = p_u
- Các giá trị khác = -vô cùng.

---
3. Độ phức tạp
- Thời gian: O(N * S^2) ~ 300^3 = 27,000,000 (Pass tốt trong 1-2s).
- Không gian: O(N * S).
 */

#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

int N, S;
const int INF = -1e9;

vector<pair<int, int>> bees(301); // bee farmily with number of bee and pollination power
vector<vector<int>> adj(300 + 1);
vector<bool> visited(300 + 1, false);
vector<vector<vector<int>>> dp(301, vector<vector<int>>(301, vector<int>(2, INF)));
void dfs(int u)
{
   //no back to root
   visited[u] = true;
   
   //init
   dp[u][0][0]=0;
   
   if(bees[u].first <= S){
      dp[u][bees[u].first][1] = bees[u].second;
   }
   for(auto v : adj[u]){
      if(visited[v]){
         continue;
      }
      //xây từ dưới lên
      dfs(v);
      vector<vector<int>> curDP = vector<vector<int>>(S+1,vector<int>(2,INF));

      for(int w1 = 0; w1 <=S; ++w1){
         for(int w2= 0; w2 <= S-w1; ++w2){
            //không chọn u
            //dp[u][w1][0] tối ưu ko chọn u và w1 con ong tại nhánh con chưa bao gồm v
            if(dp[u][w1][0] > INF){
               int best = max(dp[v][w2][0], dp[v][w2][1]);
               if(best > INF){
                  curDP[w1+w2][0] = max(curDP[w1+w2][0], dp[u][w1][0]+ best);
               }
            }
            //chọn u tối ưu bằng max tại đã chọn w1 tại u vs các nhánh trước đó
            //dp[u][w1][1] tối ưu chưa có v với w1 con ong
            if(dp[u][w1][1] > INF && dp[v][w2][0] > INF){
               curDP[w1+w2][1] = max(curDP[w1+w2][1], dp[u][w1][1]+ dp[v][w2][0]);
            }
         }
      }
      //chọn
      dp[u] = curDP;
   }
}
int solve()
{
   int res = 0;
   //init
   dp[1][0][0] = 0;
   dp[1][bees[1].first][1]= bees[1].second;
   
   dfs(1);
   
   //result
   for (int i = 0; i <= S; ++i)
   {
      res = max({res, dp[1][i][0], dp[1][i][1]});
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
   cin >> N >> S;

   for (int i = 1; i <= N; ++i)
   {
      int x, y;
      cin >> x >> y;
      bees[i] = {x, y};
   }

   for (int i = 0; i < N - 1; ++i)
   {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
   cout << solve();
   return 0;
}
