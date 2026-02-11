/******************************************************************************

https://www.acmicpc.net/problem/26183
algo:sort
algo:segment tree build from l (0->N)
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>

using namespace std;
int N;
vector<long long > res;
vector<long long> r_coords;

struct line{
    long s, e, i;
};
bool compare(line a, line b){
    if(a.s != b.s){
        return a.s < b.s;
    }else{
        return a.e > b.e;
    }
}

class SegmentTree {
private:
    int n;
    vector<int> tree;

public:
    SegmentTree(int n) : n(n) {
        tree.assign(4 * n + 1, -1);
    }

    // Cập nhật giá trị tại vị trí idx lên giá trị val (Point Update)
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = max(tree[node], val);
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    // Truy vấn giá trị lớn nhất trong đoạn [L, R] (Range Query)
    int query(int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return -1;
        }
        if (L <= start && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return max(query(2 * node, start, mid, L, R),
                   query(2 * node + 1, mid + 1, end, L, R));
    }
};


void solve(vector<line> & lines){
    sort(lines.begin(), lines.end(), compare);
    
    auto get_compressed_r = [&](long long r) {
        return lower_bound(r_coords.begin(), r_coords.end(), r) - r_coords.begin() + 1;
    };
    
    // for(auto it : lines){
    //     cout<<it.s<<' '<<it.e<<' '<<it.i<<endl;
    // }
    int m = r_coords.size();
    //khởi tạo segment tree = -1 để đảm bảo chỉ duyệt theo left và chỉ cập nhật theo right -> keep 
    //st update chỉ những max range
    SegmentTree st(m);
    for(int i = 0; i < lines.size(); ++i){
        //chỉ số right -> end m
        int comp_r = get_compressed_r(lines[i].e);
        //query từ comp_r -> m đảm bảo tại i thì ri luôn <= comp_r -> m(max)
        //và đoạn này đã được update max của tất car lj<= li
       
        // các item từ comp_r -> đã đảm bào là lj <= li vì đã sắp xếp
        int max_con = st.query(1,1,m,comp_r,m);
        // cập nhật giá trị max của i vào st đảm bảo duy trì query lần tiếp theo
        int cur_c = (max_con == -1) ? 0: max_con+1;
        res[lines[i].i] = cur_c;
        st.update(1,1, m, comp_r,cur_c);
    }
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>N;
    int len = 0;
    long long s,  t;
    vector<line> lines(N);
    res = vector<long long>(N, 0);
    for(int i = 0; i < N;i++){
        cin>>lines[i].s>>lines[i].e;
        lines[i].e+=lines[i].s;
        lines[i].i = i;
        r_coords.push_back(lines[i].e);
    }
    sort(r_coords.begin(), r_coords.end());
    r_coords.erase(unique(r_coords.begin(), r_coords.end()), r_coords.end());
    int m = r_coords.size();
    
    solve(lines);
   
    for(int i = 0; i < res.size(); ++i){
        cout<<res[i]<<' ';
    }
	return 0;
}