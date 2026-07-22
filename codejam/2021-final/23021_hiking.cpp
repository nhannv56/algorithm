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
        gt[g]= gt[g-1]*g;
    }
}
long long solve(vector<long long> & E, vector<long long> & W){
    long long res = 0;
    int maxE = pow(2,n);
    giaithua();
    int maxW = pow(2,m);
    vector<map<long long, long long>> cE(n+1), cW(m+1);

    for(int i = 1; i < maxE;++i){
        auto nbit = __builtin_popcount(i);
        long long sum = 0;
        int can = i;
        int b = 0;
        while(can> 0){
            if(can & 1 ==1){
                sum+=E[b];
            }
            can>>=1;
            ++b;
        }
        cE[nbit][sum]++;
        if(nbit==1 &&C<=sum && sum<=D){
            ++res;
        }
    }
    for(int i = 1; i < maxW;++i){
        auto nbit = __builtin_popcount(i);
        long long sum = 0;
        int can = i;
        int b = 0;
        while(can> 0){
            if(can & 1 ==1){
                sum+=W[b];
            }
            can>>=1;
            ++b;
        }
        if(nbit==1 &&C<=sum && sum<=D){
            ++res;
        }
        cW[nbit][sum]++;
    }
    // for(auto & vt : cE){
    //     // sort(vt.begin(), vt.end());
    //     // for(auto s : vt){
    //     //     cout<<s<<" ";
    //     // }cout<<endl;
    //     auto pre = vt.begin();
    //     for(auto it = vt.begin(); it != vt.end();++it){
    //         if(it != vt.begin()){
    //             it->second += pre->second;
    //         }
    //         pre = it;
    //     }
    // }
    for(auto & vt : cW){
        // sort(vt.begin(), vt.end());
        auto pre = vt.begin();
        for(auto it = vt.begin(); it != vt.end();++it){
            if(it != vt.begin()){
                it->second += pre->second;
            }
            pre = it;
        }
    }
    for(long long i = 1; i <=n;++i){
        for(long long j = i-1; j <=i+1;++j){
            // cout<<"ij:"<<i<<" "<<j<<endl;
            if(j > 0 && j <= m){
                for(auto [s1,c1] : cE[i]){
                    auto exS2= C-(s1+(i+j-1)*x);
                    auto exD2= D-(s1+(i+j-1)*x);
                    if(exS2 <=0 &&exD2 <=0){
                        continue;
                    }
                    auto it1 = cW[j].lower_bound(exS2);
                    auto it2 = cW[j].lower_bound(exD2);
                    
                    if(it1 != cW[j].end()){
                        auto w1 = 0;
                        if(it1 != cW[j].begin()){
                            it1--;
                            w1 = it1->second;
                        }
                        auto w2 = 0;

                        if(it2!= cW[j].end()){
                            if(it2->first > exD2){
                                --it2;
                            }
                            w2 = it2->second-w1;
                        }else{
                            w2 = cW[j].rbegin()->second - w1;
                        }
                        auto cur=gt[i]*gt[j]*(i==j?2:1)*c1*w2;//todo
                        res+=cur;
                        // cout<<"i:"<<i<<" "<<j<<" "<<c1<<" "<<w2<<" "<<cur<<endl;
                        res%=MOD;
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
