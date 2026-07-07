/******************************************************************************

https://codejam.lge.com/contest/problem/1677/1

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, K;

// Template class for Segment Tree
template <typename T>
class SegmentTree
{
private:
    // Segment tree to store the maximums
    vector<T> tree;
    // Input array
    vector<T> arr;
    // Size of the input array
    long long n;

    // Helper function to get the left child of a node
    long long left(long long node) { return 2 * node + 1; }

    // Helper function to get the right child of a node
    long long right(long long node) { return 2 * node + 2; }

    // Helper function to calculate the middle index
    long long mid(long long l, long long r) { return l + (r - l) / 2; }

    // Function to build the segment tree
    void build(long long node, long long start, long long end)
    {
        // If the current node represents a single element,
        // store it in the tree
        if (start == end)
        {
            tree[node] = arr[start];
            return;
        }
        // Calculate the middle index
        long long m = mid(start, end);
        // Recursively build the left and right children
        build(left(node), start, m);
        build(right(node), m + 1, end);
        // long longernal node will store the maximum of the two
        // children
        tree[node] = max(tree[left(node)], tree[right(node)]);
    }

    // Function to update the value at a specific index in
    // the segment tree
    void update(long long node, long long start, long long end, long long idx,
                T val)
    {
        // If the current node represents a single element,
        // update it
        if (start == end)
        {
            arr[idx] = val;
            tree[node] = val;
            return;
        }
        // Calculate the middle index
        long long m = mid(start, end);
        // Recursively update the left or right child
        if (idx <= m)
            update(left(node), start, m, idx, val);
        else
            update(right(node), m + 1, end, idx, val);
        // long longernal node will store the maximum of the two
        // children
        tree[node] = max(tree[left(node)], tree[right(node)]);
    }

    // Function to query the maximum value in a given range
    T query(long long node, long long start, long long end, long long l, long long r)
    {
        // If the current node's range is completely outside
        // the query range
        if (r < start || end < l)
            return 0;
        // If the current node's range is completely inside
        // the query range
        if (l <= start && end <= r)
            return tree[node];
        // Calculate the middle index
        long long m = mid(start, end);
        // Recursively query the left and right children and
        // combine the results
        T left_max = query(left(node), start, m, l, r);
        T right_max = query(right(node), m + 1, end, l, r);
        return max(left_max, right_max);
    }

public:
    // Constructor to initialize the segment tree with the
    // input array
    SegmentTree(const vector<T> &a)
        : arr(a), n(a.size())
    {
        // Resize the tree to accommodate the segment tree
        // nodes
        tree.resize(4 * n);
        // Build the segment tree
        build(0, 0, n - 1);
    }

    // Public function to update the value at a specific
    // index
    void update(long long idx, T val)
    {
        update(0, 0, n - 1, idx, val);
    }

    // Public function to query the maximum value in a given
    // range
    T query(long long l, long long r)
    {
        return query(0, 0, n - 1, l, r);
    }
};

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int size) {
      
        parent.resize(size);
      
        // Initialize the parent array with each 
        // element as its own representative
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    // Find the representative (root) of the
    // set that includes element i
    int find(int i) {
      
        // If i itself is root or representative
        if (parent[i] == i) {
            return i;
        }
      
        // Else recursively find the representative 
        // of the parent
        return parent[i] = find(parent[i]);
    }

    // Unite (merge) the set that includes element 
    // i and the set that includes element j
    void unite(int i, int j) {
      
        // Representative of set containing i
        int irep = find(i);
      
        // Representative of set containing j
        int jrep = find(j);
       
        // Make the representative of i's set
        // be the representative of j's set
        parent[irep] = jrep;
    }
};
void solve(vector<long long> &a, long long K)
{
    long long res = 0;

    long long n = a.size();
    SegmentTree<long long> st(a);
    vector<pair<long long,pair<long long,long long>>> edges;
    for (long long i = 0; i < n; ++i)
    {
        long long r = i + K;
        long long l = i - K;
        if (r < n)
        {
            long long max_r = st.query(i, r);
            edges.push_back({max_r, {i, r}});
            for (long long j = r+1; j < min(r + K, n); ++j)
            {
                max_r = max(max_r, a[j]);
                edges.push_back({max_r, {i, j}});
                if(a[j] > a[i]){
                    break;
                }
            }
        }
        if (l >= 0)
        {
            long long max_l = st.query(l, i);
            edges.push_back({max_l, {l, i}});
            for (long long j = l-1; j >= max(0LL, l - K); --j)
            {
                max_l = max(max_l, a[j]);
                edges.push_back({max_l, {l, j}});
                if(a[j] > a[i]){
                    break;
                }
            }
        }
    }
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    vector<bool> visited(n, false);
    for(auto &[val, edge]: edges){
        auto [u, v] = edge;
        if(uf.find(u) != uf.find(v)){
            uf.unite(u, v);
            res += val;
        }
    }
    for(long long i = 0; i < n; ++i){
        if(uf.find(i) != uf.find(0)){
            cout<<-1<<endl;
            return;
        }
    }
    cout << res << endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
#endif

    cin >> N >> K;
    vector<long long> a(N);
    for (long long i = 0; i < N; ++i)
    {
        cin >> a[i];
    }
    solve(a, K);
    return 0;
}
