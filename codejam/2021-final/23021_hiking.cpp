/******************************************************************************

https://codejam.lge.com/problem/23021
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, T;
long long n,m,C,D;
long long MOD = 1e9+7;
long long x = 10;
struct Node{
    long long mask, sum, w, m;// ways, mountain
};
vector<long long> gt(20);
void giaithua(){
    gt[1]=1;
    for(long long g = 2; g < 20;++g){
        gt[g]= (gt[g-1]*g) % MOD;
    }
}

long long get_count(const map<long long, long long>& m, long long val) {
    if (m.empty()) return 0;
    auto it = m.lower_bound(val);
    if (it != m.end() && it->first == val) {
        return it->second;
    }
    if (it == m.begin()) {
        return 0;
    }
    --it;
    return it->second;
}
long long solve(vector<long long> & E, vector<long long> & W){
    long long res = 0;
    int maxE = 1 << n;
    giaithua();
    int maxW = 1 << m;
    vector<vector<long long>> cE(n+1), cW(m+1);

    for(int i = 1; i < maxE;++i){
        auto nbit = __builtin_popcount(i);
        long long sum = 0;
        int can = i;
        int b = 0;
        while(can> 0){
            if(can & 1){
                sum+=E[b];
            }
            can>>=1;
            ++b;
        }
        cE[nbit].push_back(sum);
        if(nbit==1 && C<=sum && sum<=D){
            res = (res + 1) % MOD;
        }
    }
    for(int i = 1; i < maxW;++i){
        auto nbit = __builtin_popcount(i);
        long long sum = 0;
        int can = i;
        int b = 0;
        while(can> 0){
            if(can & 1){
                sum+=W[b];
            }
            can>>=1;
            ++b;
        }
        if(nbit==1 && C<=sum && sum<=D){
            res = (res + 1) % MOD;
        }
        cW[nbit].push_back(sum);
    }
    
    for(int i = 1; i <= m; ++i){
        sort(cW[i].begin(), cW[i].end());
    }

    for(long long i = 1; i <=n;++i){
        for(long long j = i-1; j <=i+1;++j){
            if(j > 0 && j <= m){
                for(long long s1 : cE[i]){
                    auto exS2= C-(s1+(i+j-1)*x);
                    auto exD2= D-(s1+(i+j-1)*x);
                    if(exD2 < 0){
                        continue;
                    }
                    
                    auto it1 = lower_bound(cW[j].begin(), cW[j].end(), exS2);
                    auto it2 = upper_bound(cW[j].begin(), cW[j].end(), exD2);
                    long long w2 = distance(it1, it2);
                    
                    if (w2 > 0) {
                        long long cur = w2 % MOD;
                        cur = (cur * gt[i]) % MOD;
                        cur = (cur * gt[j]) % MOD;
                        if (i == j) cur = (cur * 2) % MOD;
                        res = (res + cur) % MOD;
                    }
                }
            }
        }
    }
    return res;
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
    cin >> T;
    
    while(T > 0){
        cin>>n>>m>>x>>C>>D;
        vector<long long> E(n), W(m);
        for(int i = 0; i < n; ++i){
            cin>>E[i];
        }
        for(int i = 0; i < m; ++i){
            cin>>W[i];
        }
        cout<<solve(E,W)<<endl;
        --T;
    }
    return 0;
}
