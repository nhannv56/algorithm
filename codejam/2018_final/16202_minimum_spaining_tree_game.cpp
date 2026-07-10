/**
algo: mst minimum spanning tree game
algo: priority queue
algo: kruskal ưu tiên cạnh ngắn nhất
dung union find disjoin set để gộp các thành phần
đếm số điểm đã connect
tính chi phí khi join
**/
#include <iostream>
#include <set>
#include <iterator>
#include <bits/stdc++.h>

using namespace std;
int N, M, K;
class UnionFind {
public:
    vector<int> parent;
    vector<int> cnt;
    
public:
    UnionFind(int size) {
      
        parent.resize(size);
        cnt.resize(size);
      
        // Initialize the parent array with each 
        // element as its own representative
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            cnt[i]=1;
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
        parent[i] = find(parent[i]);
        return parent[i];
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
        cnt[jrep]= cnt[irep]+cnt[jrep];// tổng đã kết nối
    }
};
void solve(deque<pair<int, pair<int,int>>> edges){
    vector<int> res(K,0);
    int i = 0;
    for(; i < K;++i){
        int cost = 0;
        UnionFind uf(N);
        int cnt =  0;
        for(auto [d,uv]: edges){
            auto [u, v]= uv;      
            --u;--v;      
            if(uf.find(u) != uf.find(v)){
                uf.unite(u,v);//join group
                cost+=d;//tính chi phí
                // cout<<"cost:"<<cost<<endl;
            }
            // if(!visited[u]){
            //     visited[u] = true;
            // }
            // if(!visited[v]){
            //     visited[v] = true;
            // }
            int pu = uf.find(u);
            // cout<<"cnt:"<<uf.cnt[pu]<<endl;
            if(uf.cnt[pu]== N){
                res[i] = cost;// có kết nối
                break;
            }
        }
        edges.pop_front();//xóa cạnh ngắn nhất
    }
    
    for(int r : res){
        cout<<r<<' ';
    }
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
    std::cin >> N>> M >>K;
    deque<pair<int, pair<int,int>>> edges; // dis, u,v
    int u,v;
    for (int i = 1; i <= M; i++) {
        cin>>u>>v;
        edges.push_back({i,{u,v}});
    }
    solve(edges);
    return 0;
}
