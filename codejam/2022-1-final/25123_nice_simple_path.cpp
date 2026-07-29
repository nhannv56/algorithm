/**
 * algo: dp on tree
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n;
string label;
vector<vector<int>> adj;

int max_len;
long long max_ways;

// Hàm cập nhật kỷ lục độ dài và số đường đi
void update(int len, long long ways) {
    if (ways <= 0) return;
    if (len > max_len) {
        max_len = len;
        max_ways = ways;
    } else if (len == max_len) {
        max_ways += ways;
    }
}

// Trả về {độ dài đi xuống dài nhất từ u, số lượng đường đi đạt độ dài đó}
pair<int, long long> dfs(int u) {
    vector<pair<int, long long>> valid;

    for (int v : adj[u]) {
        auto res = dfs(v);
        // Chỉ kéo dài đường đi nếu nhãn khác nhau
        if (label[v] != label[u]) {
            valid.push_back(res);
        }
    }

    // Đỉnh u đứng một mình tạo thành đường đi độ dài 1
    update(1, 1);

    if (valid.empty()) {
        return {1, 1};
    }

    // Sắp xếp các nhánh con giảm dần theo độ dài
    sort(valid.begin(), valid.end(), [](const pair<int, long long>& a, const pair<int, long long>& b) {
        return a.first > b.first;
    });

    // 1. Tính đường đi đi từ u xuống các nhánh con
    int L1 = valid[0].first;
    long long sum_c1 = 0;
    int count1 = 0;

    for (auto& p : valid) {
        if (p.first == L1) {
            sum_c1 += p.second;
            count1++;
        } else {
            break;
        }
    }

    // Đường đi xuất phát từ u đi xuống 1 nhánh con
    update(L1 + 1, sum_c1);

    // 2. Xét đường đi đi qua u kết nối 2 nhánh con khác nhau
    if (valid.size() >= 2) {
        if (count1 >= 2) {
            // Có từ 2 nhánh trở lên cùng đạt độ dài lớn nhất L1
            // Số cặp = ( (Σ c_i)^2 - Σ (c_i^2) ) / 2
            long long sum_sq = 0;
            for (int i = 0; i < count1; ++i) {
                sum_sq += valid[i].second * valid[i].second;
            }
            long long ways = (sum_c1 * sum_c1 - sum_sq) / 2;
            update(2 * L1 + 1, ways);
        } else {
            // Chỉ có 1 nhánh đạt L1, ghép với các nhánh đạt L2 (độ dài lớn thứ 2)
            int L2 = valid[1].first;
            long long sum_c2 = 0;
            for (size_t i = 1; i < valid.size(); ++i) {
                if (valid[i].first == L2) {
                    sum_c2 += valid[i].second;
                } else {
                    break;
                }
            }
            long long ways = valid[0].second * sum_c2;
            update(L1 + L2 + 1, ways);
        }
    }

    return {L1 + 1, sum_c1};
}

void solve() {
    max_len = 0;
    max_ways = 0;

    // Chạy DFS từ đỉnh gốc (ở đây là các đỉnh trong adj[0])
    for (int root : adj[0]) {
        dfs(root);
    }

    cout << max_len << " " << max_ways << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            cin >> n >> label;
            label = " " + label; // 1-indexed

            adj.assign(n + 1, vector<int>());
            for (int i = 1; i <= n; ++i) {
                int p;
                cin >> p;
                adj[p].push_back(i);
            }

            solve();
        }
    }
    return 0;
}