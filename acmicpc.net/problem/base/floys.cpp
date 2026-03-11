#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e15; // Đủ lớn cho hầu hết bài toán

void floydWarshall(int n, vector<vector<long long>>& dist /*, vector<vector<int>>& next_node*/) {
    // // next_node dùng để truy vết đường đi
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         if (i == j) dist[i][j] = 0;
    //         if (dist[i][j] < INF && i != j) next_node[i][j] = j;
    //         else next_node[i][j] = -1;
    //     }
    // }

    // 3 vòng lặp O(V^3) - Lưu ý: k phải là vòng lặp ngoài cùng
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        // next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }
    }
}