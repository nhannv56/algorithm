/******************************************************************************

https://www.acmicpc.net/problem/32322

algo:segment tree sum range
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>

using namespace std;
int N;
vector<long long > res;
vector<long long> r_coords;

class SegmentTree {
    vector<long long> tree, lazy;
    int n;

public:
    // Constructor to initialize segment tree and lazy arrays
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        
         // LLONG_MIN indicates no pending assignment
        lazy.assign(4 * n, LLONG_MIN);
    }

    // Push pending updates to children
    void push(int node, int start, int end) {
        if (lazy[node] != LLONG_MIN) {
         
            // Apply lazy value to current node
            tree[node] = (long long)(end - start + 1) * lazy[node];
          
            // Propagate lazy value to children if not a leaf
            if (start != end) {
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            
             // Clear lazy value
            lazy[node] = LLONG_MIN;
        }
    }

    // Update values in range [l,r] to val
    void updateRange(int node, int start, int end, int l, int r, long long val) {
        push(node, start, end);

        // No overlap
        if (r < start || end < l) return;

        // Total overlap
        if (l <= start && end <= r) {
            lazy[node] = val;
            push(node, start, end);
            return;
        }

        // Partial overlap, recurse on children
        int mid = (start + end) / 2;
        updateRange(node * 2, start, mid, l, r, val);
        updateRange(node * 2 + 1, mid + 1, end, l, r, val);

        // Update current node based on children
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    // Query sum of values in range [l,r]
    long long queryRange(int node, int start, int end, int l, int r) {
        push(node, start, end);

        // No overlap
        if (r < start || end < l) return 0;

        // Total overlap
        if (l <= start && end <= r) return tree[node];

        // Partial overlap, query children
        int mid = (start + end) / 2;
        return queryRange(node * 2, start, mid, l, r) +
               queryRange(node * 2 + 1, mid + 1, end, l, r);
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
    #endif
    int N,T;
    char type;
    int rRoom,sRoom, eRoom;
    cin>>N>>T;
    SegmentTree st(N+1);
    //fill tất cả là 1
    for(int i = 0; i < N;++i){
        st.updateRange(1,1,N,i+1,i+1,1);
    }
    for(int t = 0; t < T;++t){
        cin>>type;
        if(type == 'R'){
            cin>>rRoom;
            st.updateRange(1,1,N,rRoom,rRoom,0);// update 0 cho đã reverse
        }else{
            cin>>sRoom>>eRoom;
            cout<<st.queryRange(1, 1, N, sRoom, eRoom)<<'\n';
        }
    }
	return 0;
}