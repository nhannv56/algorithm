/***
algo: uninon-find
algo: graph
  **/
class UnionFind {
    vector<int> parent;
public:
    vector<int> cost;
    UnionFind(int size) {
      
        parent.resize(size);
        cost.resize(size);
      
        // Initialize the parent array with each 
        // element as its own representative
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            cost[i]= INT_MAX;
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
    void unite(int i, int j,int w) {
      
        // Representative of set containing i
        int irep = find(i);
      
        // Representative of set containing j
        int jrep = find(j);
       
        // Make the representative of i's set
        // be the representative of j's set
        parent[irep] = jrep;
        cost[jrep] = cost[irep] & cost[jrep] & w;
        // cost[jrep] = cost[irep];
        // cout<<"cost["<<jrep<<"] "<<cost[jrep]<<endl;
    }
};
class Solution {
public:
    void fullfill(int s, vector<vector<int>> );
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        UnionFind uf(n);
        vector<int>res(query.size());
        for(auto edge : edges){
            uf.unite(edge[0],edge[1], edge[2]);            
        }
        for( int i = 0; i < query.size();++i){
            auto q = query[i];
            if(uf.find(q[0])!=uf.find(q[1])){
                res[i] = -1;
            }else{
                auto p = uf.find(q[0]);
                res[i] = uf.cost[p];
            }
        }
        return res;
    }
};
