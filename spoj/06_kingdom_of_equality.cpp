#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * Bai toan: Kingdom of Equality (KEQUALITY) - SPOJ
 * Tim so luong thanh pho X cach deu mot nhom thanh pho cho truoc.
 * Dieu kien:
 * 1. X phai co the den duoc tu moi thanh pho trong nhom chi bang cac duong co san (k=1).
 * 2. Khoang cach tu moi thanh pho den X phai bang nhau (khoang cach tinh tren cay goc, k=0 hoac k=1).
 * 
 * Thuat toan:
 * - Su dung tat ca canh de xay dung cay goc (Full Tree) de tinh khoang cach va LCA.
 * - Su dung canh k=1 de tim cac thanh phan lien thong va tinh kich thuoc cay con kha dung (sz_k1).
 * - Voi moi query:
 *   1. Kiem tra xem tat ca moi nguoi co nam trong cung mot thanh phan lien thong k=1 khong.
 *   2. Tim duong kinh D cua nhom thanh pho tren Full Tree.
 *   3. Neu D le, khong co trung diem -> ket qua = 0.
 *   4. Neu D chan, tim trung diem M cua duong kinh.
 *   5. M phai cach deu tat ca thanh pho trong nhom (khoang cach = D/2).
 *   6. Count X: Lay tong so nut trong thanh phan lien thong cua M - (tong sz_k1 cua cac nhanh chua it nhat 1 thanh pho trong nhom).
 */

const int MAXN = 200005;
const int LOGN = 20;

int N, Q;
vector<int> full_adj[MAXN]; // Tat ca canh (du k=0 hay k=1)
vector<int> k1_adj[MAXN];   // Chi canh co san (k=1)
int up[MAXN][LOGN];         // Binary Lifting table
int level_full[MAXN];       // Do khau tren cay goc
int sz_k1[MAXN];            // Kich thuoc cay con tinh trong pham vi k=1
int cityLabel[MAXN];        // Nhan thanh phan lien thong (k=1)
int compSize[MAXN];         // So luong nut trong moi thanh phan lien thong (k=1)
bool visited_full[MAXN], visited_k1[MAXN];

// Duyet tren toan bo canh de xay dung cay goc va Binary Lifting
void dfs_full(int u, int p, int d) {
    visited_full[u] = true;
    level_full[u] = d;
    up[u][0] = p;
    for (int i = 1; i < LOGN; i++) {
        if (up[u][i - 1] != -1)
            up[u][i] = up[up[u][i - 1]][i - 1];
        else
            up[u][i] = -1;
    }
    for (int v : full_adj[u]) {
        if (v != p) dfs_full(v, u, d + 1);
    }
}

// Duyet de phan loai cac thanh phan lien thong dua tren canh k=1
void dfs_k1(int u, int p, int label, vector<int>& nodes) {
    visited_k1[u] = true;
    cityLabel[u] = label;
    compSize[label]++;
    nodes.push_back(u); // Luu lai danh sach cac nut de tinh sz_k1 sau
    for (int v : k1_adj[u]) {
        if (v != p) dfs_k1(v, u, label, nodes);
    }
}

// Tim to tien chung gan nhat
int get_lca(int u, int v) {
    if (level_full[u] < level_full[v]) swap(u, v);
    for (int i = LOGN - 1; i >= 0; i--) {
        if (up[u][i] != -1 && level_full[up[u][i]] >= level_full[v])
            u = up[u][i];
    }
    if (u == v) return u;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

// Khoang cach tren cay goc
int get_dist(int u, int v) {
    return level_full[u] + level_full[v] - 2 * level_full[get_lca(u, v)];
}

// Nhay len to tien thu k
int get_kth_ancestor(int u, int k) {
    for (int i = 0; i < LOGN; i++)
        if ((k >> i) & 1) u = up[u][i];
    return u;
}

// Tim nut nam tren duong di tu u den v tai mot khoang cach k tinh tu u
int get_node_on_path(int u, int v, int k) {
    int l = get_lca(u, v);
    int dist_u_l = level_full[u] - level_full[l];
    if (k <= dist_u_l) return get_kth_ancestor(u, k);
    int dist_v_l = level_full[v] - level_full[l];
    return get_kth_ancestor(v, dist_v_l - (k - dist_u_l));
}

int solve() {
    int g;
    if (!(cin >> g)) return 0;
    vector<int> pts(g);
    for (int i = 0; i < g; i++) cin >> pts[i];
    
    // Kiem tra reachability: tat ca phai o cung mot thanh phan lien thong k=1
    for (int i = 1; i < g; i++)
        if (cityLabel[pts[i]] != cityLabel[pts[0]]) return 0;
    
    // Loai bo cac nut trung va xu ly truong hop chi co 1 nut
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() == 1) return compSize[cityLabel[pts[0]]];

    // Tim duong kinh (diameter) cua tap hop nuts pts
    int u1 = pts[0], v1 = pts[0], max_d = -1;
    for (int p : pts) {
        int d = get_dist(u1, p);
        if (d > max_d) { max_d = d; v1 = p; }
    }
    u1 = v1; max_d = -1;
    for (int p : pts) {
        int d = get_dist(u1, p);
        if (d > max_d) { max_d = d; v1 = p; }
    }

    // Neu duong kinh le, khong co diem o giua cach deu tat ca
    if (max_d % 2 != 0) return 0;
    int M = get_node_on_path(u1, v1, max_d / 2); // Ung cu vien duy nhat cho vi tri trung tam
    
    // Kiem tra xem tat ca moi nguoi co cach deu M mot khoang max_d/2 khong
    for (int p : pts) if (get_dist(M, p) != max_d / 2) return 0;

    // Tim cac nhanh (con truc tiep hoac cha) cua M ma khong duoc phep chon X o do
    vector<int> bad_neighbors;
    int total = compSize[cityLabel[M]];
    for (int p : pts) {
        int l = get_lca(p, M);
        if (l == M) {
            // p nam trong cay con (Full Tree) cua M -> nhanh cam la con cua M tren duong toi p
            bad_neighbors.push_back(get_kth_ancestor(p, level_full[p] - level_full[M] - 1));
        } else {
            // p khong nam trong cay con cua M -> nhanh cam la cha cua M
            bad_neighbors.push_back(up[M][0]);
        }
    }
    // Loai bo nhung nhanh trung lap
    sort(bad_neighbors.begin(), bad_neighbors.end());
    bad_neighbors.erase(unique(bad_neighbors.begin(), bad_neighbors.end()), bad_neighbors.end());

    long long excluded = 0;
    for (int nb : bad_neighbors) {
        if (nb == -1) continue;
        if (nb == up[M][0]) {
            // Neu nhanh cam la cha, tat ca nhung nut ben ngoai sz_k1[M] se khong hop le
            excluded += (total - sz_k1[M]);
        } else {
            // Neu nhanh cam la nut con, tru di sz_k1 cua nut do
            excluded += sz_k1[nb];
        }
    }
    return (int)(total - excluded);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    if (!(cin >> N)) return 0;
    for (int i = 0; i < N - 1; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        full_adj[u].push_back(v);
        full_adj[v].push_back(u);
        if (k == 1) {
            k1_adj[u].push_back(v);
            k1_adj[v].push_back(u);
        }
    }

    // Buoc 1: Xay dung cau truc cay goc va Binary Lifting
    for (int i = 1; i <= N; i++) {
        if (!visited_full[i]) dfs_full(i, -1, 0);
    }

    // Buoc 2: Phan loai cac nut vao cac thanh phan lien thong va tinh sz_k1 (kich thuoc nhanh cay con co san)
    int label_cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited_k1[i]) {
            vector<int> nodes;
            dfs_k1(i, -1, ++label_cnt, nodes);
            // Tinh sz_k1 tu duoi len (Post-order) dua tren cau truc Full Tree
            for (int j = (int)nodes.size() - 1; j >= 0; j--) {
                int u = nodes[j];
                sz_k1[u] = 1;
                for (int v : full_adj[u]) {
                    // v la con cua u trong Full Tree va v thuoc cung thanh phan lien thong voi u
                    if (v != up[u][0] && cityLabel[v] == cityLabel[u]) {
                        sz_k1[u] += sz_k1[v];
                    }
                }
            }
        }
    }

    // Buoc 3: Xu ly truy van
    if (cin >> Q) while (Q--) cout << solve() << "\n";
    return 0;
}
