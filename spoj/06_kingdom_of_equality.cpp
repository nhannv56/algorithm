#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * algo: binary lifting
 * algo: graph theory
 * ============================================================================
 * PACKAGE: Binary Lifting (Reusable for Tree Problems)
 * ============================================================================
 * Features:
 * - LCA (Lowest Common Ancestor) in O(log N)
 * - Distance between 2 nodes in O(log N)
 * - K-th Ancestor in O(log N)
 * - Get node on path (u -> v) at distance k in O(log N)
 * ============================================================================
 */
class BinaryLifting {
public:
    int n, logn;
    vector<vector<int>> up;
    vector<int> depth;

    BinaryLifting() : n(0), logn(0) {}
    BinaryLifting(int _n) : n(_n) {
        logn = 0;
        while ((1 << logn) <= n) logn++;
        up.assign(n + 1, vector<int>(logn, -1));
        depth.assign(n + 1, 0);
    }
    // Xây dựng bảng up và depth cho cây có gốc tại node 1
    void build(int u, int p, int d, const vector<int> adj[], bool visited[]) {
        visited[u] = true;
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < logn; i++) {
            if (up[u][i - 1] != -1)
                up[u][i] = up[up[u][i - 1]][i - 1];
            else
                up[u][i] = -1;
        }
        for (int v : adj[u]) {
            if (v != p) build(v, u, d + 1, adj, visited);
        }
    }
    // Trả về LCA của 2 node u và v
    int get_lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = logn - 1; i >= 0; i--) {
            if (up[u][i] != -1 && depth[up[u][i]] >= depth[v])
                u = up[u][i];
        }
        if (u == v) return u;
        for (int i = logn - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
    // Trả về khoảng cách giữa 2 node u và v
    int get_dist(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }
    // Trả về k-th ancestor của node u, nếu tồn tại, ngược lại trả về -1
    int get_kth_ancestor(int u, int k) const {
        if (k < 0) return -1;
        for (int i = 0; i < logn; i++) {
            if ((k >> i) & 1) {
                if (u == -1) break;
                u = up[u][i];
            }
        }
        return u;
    }

    // Trả về node trên đường đi từ u đến v tại khoảng cách k từ u
    int get_node_on_path(int u, int v, int k) const {
        int l = get_lca(u, v);
        int d_u_l = depth[u] - depth[l];
        if (k <= d_u_l) return get_kth_ancestor(u, k);
        int d_v_l = depth[v] - depth[l];
        int total_dist = d_u_l + d_v_l;
        if (k <= total_dist) return get_kth_ancestor(v, total_dist - k);
        return -1;
    }
};

const int MAXN = 200005;
vector<int> full_adj[MAXN]; 
vector<int> k1_adj[MAXN];   
int sz_k1[MAXN];            
int cityLabel[MAXN];        
int compSize[MAXN];         
bool visited_full[MAXN], visited_k1[MAXN];
BinaryLifting bl;
int N, Q;

void dfs_k1(int u, int p, int label, vector<int>& nodes) {
    visited_k1[u] = true;
    cityLabel[u] = label;
    compSize[label]++;
    nodes.push_back(u);
    for (int v : k1_adj[u]) {
        if (v != p) dfs_k1(v, u, label, nodes);
    }
}

int solve() {
    int g;
    if (!(cin >> g)) return 0;
    vector<int> pts(g);
    for (int i = 0; i < g; i++) cin >> pts[i];
    
    // Kiểm tra tính kết nối: tất cả các thành phố trong nhóm phải thuộc cùng một thành phần k=1
    for (int i = 1; i < g; i++)
        if (cityLabel[pts[i]] != cityLabel[pts[0]]) return 0;
    
    // Loại bỏ các thành phố trùng lặp và xử lý trường hợp nhóm chỉ có 1 thành phố
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() == 1) return compSize[cityLabel[pts[0]]];

    // Tìm đường kính (diameter) của nhóm thành phố dựa trên khoảng cách của cây gốc
    int u1 = pts[0], v1 = pts[0], max_d = -1;
    for (int p : pts) {
        int d = bl.get_dist(u1, p);
        if (d > max_d) { max_d = d; v1 = p; }
    }
    u1 = v1; max_d = -1;
    for (int p : pts) {
        int d = bl.get_dist(u1, p);
        if (d > max_d) { max_d = d; v1 = p; }
    }

    // Nếu đường kính là số lẻ (không có điểm chính giữa cách đều các đầu mút), trả về 0
    if (max_d % 2 != 0) return 0;

    // Tìm điểm trung tâm M (trung điểm của đường kính)
    int M = bl.get_node_on_path(u1, v1, max_d / 2);

    // Kiểm tra xem M có cách đều tất cả các thành phố khác trong nhóm không
    for (int p : pts) if (bl.get_dist(M, p) != max_d / 2) return 0;

    // Logic loại trừ: Tính số thành phố trong thành phần liên thông của M, 
    // trừ đi các nhánh hướng tới các thành phố trong nhóm để đảm bảo tính cách đều
    vector<int> bad_neighbors;
    int total = compSize[cityLabel[M]];
    for (int p : pts) {
        int l = bl.get_lca(p, M);
        if (l == M) {
            // Nếu p nằm trong cây con của M (nhìn từ gốc 1), tìm nút con của M nằm trên đường đến p
            bad_neighbors.push_back(bl.get_kth_ancestor(p, bl.depth[p] - bl.depth[M] - 1));
        } else {
            // Nếu p không nằm trong cây con của M, nhánh cha của M sẽ là nhánh bị cấm
            bad_neighbors.push_back(bl.up[M][0]);
        }
    }

    // Lấy các nhánh duy nhất ( unique bad neighbors )
    sort(bad_neighbors.begin(), bad_neighbors.end());
    bad_neighbors.erase(unique(bad_neighbors.begin(), bad_neighbors.end()), bad_neighbors.end());

    long long excluded = 0;
    for (int nb : bad_neighbors) {
        if (nb == -1) continue;
        if (nb == bl.up[M][0]) {
            // Loại bỏ toàn bộ các thành phố phía ngoài cây con của M (nếu nhánh cha bị cấm)
            excluded += (total - sz_k1[M]);
        } else {
            // Loại bỏ cây con tại nhánh con nb
            excluded += sz_k1[nb];
        }
    }

    // Kết quả cuối cùng là tổng số thành phố trong thành phần trừ đi phần bị loại bỏ
    return (int)(total - excluded);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    if (!(cin >> N)) return 0;

    // Đọc danh sách các cạnh
    for (int i = 0; i < N - 1; i++) {
        int u, v, k; cin >> u >> v >> k;
        full_adj[u].push_back(v); 
        full_adj[v].push_back(u);
        if (k == 1) { 
            k1_adj[u].push_back(v); 
            k1_adj[v].push_back(u); 
        }
    }

    // Xây dựng Binary Lifting trên toàn bộ cây gốc
    bl = BinaryLifting(N);
    for (int i = 1; i <= N; i++) {
        if (!visited_full[i]) bl.build(i, -1, 0, full_adj, visited_full);
    }

    // Phân loại các nút vào các thành phần liên thông k=1 và tính sz_k1
    int label_cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited_k1[i]) {
            vector<int> nodes; 
            dfs_k1(i, -1, ++label_cnt, nodes);

            // Tính sz_k1 theo thứ tự từ lá lên đến gốc (Post-order) 
            // sz_k1[u] là số lượng nút trong cùng thành phần liên thông k=1 thuộc cây con của u
            for (int j = (int)nodes.size() - 1; j >= 0; j--) {
                int u = nodes[j]; 
                sz_k1[u] = 1;
                for (int v : full_adj[u]) {
                    // Nếu v là con của u trong cây gốc và v nằm trong cùng thành phần liên thông k=1
                    if (v != bl.up[u][0] && cityLabel[v] == cityLabel[u]) {
                        sz_k1[u] += sz_k1[v];
                    }
                }
            }
        }
    }

    // Xử lý từng truy vấn
    if (cin >> Q) while (Q--) cout << solve() << "\n";
    return 0;
}
