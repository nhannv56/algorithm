/******************************************************************************

https://codejam.lge.com/problem/19592
algo: union find disjoin-set djs
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, T;
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
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> T;
    long long N,Seed,A,B;
    while(T > 0){
        cin>>N>>Seed>>A>>B;
        UnionFind uf(N);
        // vector<int> E(N+1,0);
        long long d = 1;
        unordered_set<long long> us;
        long long NN =N*N;
        long long E= Seed%NN;
        long long X = E/N, Y=E%N;
        us.insert(E);
        int groups = N;
        if(X!=Y){
            uf.unite(X,Y);
            // cout<<d<<" desc:"<<X<<" "<<Y<<" gr:"<<groups<<endl;
            groups--;
        }
        while(true){
            ++d;
            E = (E*A+B)%NN;
            // cout<<"d:"<<d<< " E:"<<E<<endl;
            X= E/N;
            Y = E%N;
            if(us.find(E)!=us.end()){
                break;
            }
            us.insert(E);
            if(X!=Y &&uf.find(X)!= uf.find(Y)){
                uf.unite(X,Y);
                groups--;
                // cout<<d<<" desc:"<<X<<" "<<Y<<" gr:"<<groups<<endl;
                if(groups==1){
                    break;
                }
            }
        }
        if(groups==1){
            cout<<d<<endl;
        }else{
            cout<<0<<endl;
        }
        --T;
    }
    return 0;
}
