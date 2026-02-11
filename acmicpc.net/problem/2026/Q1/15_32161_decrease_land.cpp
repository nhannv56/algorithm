/******************************************************************************

https://www.acmicpc.net/problem/32161

algo:bfs
algo:Disjoint Set Uinon

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
int N,M,Q;

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
vector<vector<int>> dj;
int Group ;
int solve(vector<vector<int>>& adj, vector<int>& b, int s, int e){
    
    if(dj[s][e]==1){
        return 1;
        
    }
    // nếu có thể jump magic max = 2
    if(Group >= 2){
        return 2;
    }else{
        return dj[s][e];
    }
}
// Sửa lại hàm djiktra
vector<vector<int>> djiktra(vector<vector<int>>& adj){
    // Khởi tạo res toàn bộ là vô cực (hoặc 1 giá trị lớn > N)
    // Lưu ý: V_size là số đỉnh thực tế (b.size()), dùng adj.size() hơi thừa nếu adj to hơn b
    vector<vector<int>> res(adj.size(), vector<int>(adj.size(), 1e9)); 

    deque<pair<int,int>> dq;
    for(int startNode = 0; startNode < adj.size(); ++startNode){
        vector<int> dis(adj.size(),1e9);
        dq.push_back({startNode, 0});
        dis[startNode] = 0; // Khoảng cách tới chính nó là 0

        while(!dq.empty()){
            auto [u, d] = dq.front(); 
            dq.pop_front();

            // Optimization: Nếu tìm thấy đường đi ngắn hơn đã có -> bỏ qua (cho Dijkstra, BFS thì ít gặp)
            if (d > res[startNode][u]) continue;

            for(int v : adj[u]){
                if(dis[v] > d + 1){ // Chỉ đi vào nếu tìm thấy đường ngắn hơn
                    dis[v] = d + 1;
                    //res[v][startNode] = d + 1; // Có thể bỏ dòng này nếu chỉ BFS 1 chiều, nhưng giữ cũng được cho đồ thị vô hướng
                    dq.push_back({v, d + 1});
                }
            }
        }
        res[startNode] = dis;
    }
    return res;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>N>>M>>Q;
    vector<int> vetexs;
    vector<int> b;//compress to value
    vector<vector<int>> edges(M,vector<int>(2));
    for(int i = 0; i < M;++i){
        cin>>edges[i][0]>>edges[i][1];
        vetexs.push_back(edges[i][0]);
        vetexs.push_back(edges[i][1]);
    }
    b = vetexs;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    Group = N;
    unordered_map<int,int> compress;
    for(int i = 0; i < b.size(); ++i){
        compress[b[i]] = i;
    }
    vector<vector<int>> adj(b.size());
    UnionFind uf(adj.size()+1);
    
    for(int i = 0; i < M; ++i){
        int u = lower_bound(b.begin(), b.end(), edges[i][0]) - b.begin();
        int v = lower_bound(b.begin(), b.end(), edges[i][1]) - b.begin();
        adj[u].push_back(v);
        adj[v].push_back(u);
        if(uf.find(u) != uf.find(v)){// chỉ gộp khi khác cha trường hợp có vòng a-b-c-d and d->a
            uf.unite(u,v);
            Group--;
        }
    }
    dj = djiktra(adj);
    int s,e;
    for(int i = 0; i < Q; ++i){
        cin>>s>>e;
        if(s==e){
            cout<<"0\n";
        }else{
            auto compress_s = compress.find(s);
            auto compress_e = compress.find(e);
            //nằm ở 2 đồ thị khác nhau
            if(compress_e == compress.end() || compress_s == compress.end() ||
               uf.find(compress_e->second) != uf.find(compress_s->second) ){
                cout<<"1\n";
            }else{
                //nằm chung 1 đồ thị
                cout<<solve(adj, b,compress_s->second, compress_e->second)<<'\n';
            }
        }
    }
	return 0;
}