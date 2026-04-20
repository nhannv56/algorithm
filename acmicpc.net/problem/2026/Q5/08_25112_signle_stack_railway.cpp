/***
https://www.acmicpc.net/problem/25112
algo: binary search
algo: segment tree sum
Dùng segment tree để tính sum của đoạn trái sang phải và phải sang trái
dùng binary seach để tìm kiếm điểm tối ưu do tổng không đổi nên l nhỏ -> dịch phải, r nhỏ dịch trái

Case 1
5	4	3	2	1	0
0	1	2	3	4	5
0	20	70	40	80	50
20	70	40	80	50	0
					
					
0	20	90	130	210	260
260	240	170	130	50	0

**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long N, Q;
// Template class for Segment Tree
class SegmentTree
{
    vector<long long> tree;
    int n;

    // Build the tree in O(N) time
    void build(const vector<int> &arr, int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Update value at a specific position in O(log N)
    void update(int node, int start, int end, int idx, int val)
    {
        if (start == end)
        {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Query sum in range [l, r] in O(log N)
    long long query(int node, int start, int end, int l, int r)
    {
        if (r < start || end < l)
            return 0; // No overlap
        if (l <= start && end <= r)
            return tree[node]; // Total overlap
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }

public:
    SegmentTree(const vector<int> &arr)
    {
        n = arr.size();
        tree.assign(4 * n, 0); // 4N space is safe for recursive ST
        build(arr, 1, 0, n - 1);
    }

    void update(int idx, int val) { update(1, 0, n - 1, idx, val); }
    long long query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
long long binarySearch(SegmentTree &segTree1, SegmentTree &segTree2)
{
    long long l = 0, r = N - 1;
    long long ans = segTree1.query(0, N - 1);
    while (l <= r)
    {
        long long m = l + (r - l) / 2;
        if (segTree1.query(0, m) == segTree2.query(0, N - 1 - m))
        {
            return 0;
        }
        auto ansl = segTree1.query(0, m);
        auto ansr = segTree2.query(0, N - 1 - m);
        // cout<<"m:"<<l<<"-"<<r<<":"<<m<<" ansl: "<<ansl<<" ansr: "<<ansr<<'\n';
        if (ansl < ansr)
        {
            l = m + 1;
            ans = min(ans, abs(ansl - ansr));
        }
        else
        {
            r = m - 1;
            ans = min(ans, abs(ansl - ansr));
        }
    }
    return ans;
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
    cin >> N;
    vector<int> a1(N, 0);
    vector<int> a2(N, 0);

    for (long long i = 1; i < N; ++i)
    {
        cin >> a1[i];
        a2[N - i] = a1[i];
    }

    SegmentTree segTree1(a1);
    SegmentTree segTree2(a2);
    cin >> Q;
    cout << binarySearch(segTree1, segTree2) << '\n';
    for (long long i = 0; i < Q; ++i)
    {
        long long x, y;
        cin >> x >> y;
        // --x;
        // cout<<"x: "<<x<<" y: "<<y<<'\n';
        segTree1.update(x, y);
        segTree2.update(N - x, y);
        cout << binarySearch(segTree1, segTree2) << '\n';
    }
    return 0;
}
