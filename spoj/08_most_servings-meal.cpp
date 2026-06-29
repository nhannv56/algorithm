/******************************************************************************

https://spoj.com/problems/MKUHAR/
algo: binary_search binary seach paramatric search
search trên target
search trên đường thẳng tìm điểm thỏa mãn
2 lần binary search
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <cctype>
using namespace std;
int N, M;
vector<int> X(100), Y(100),SM(100),PM(100),SV(100), PV(100);
bool validate(int target){
    int money = M;
    //a*sm/pm+b*sv/pv +y >=target*x
    //a*sm/pm+b*sv/pv +y >=target*x
    for(int i = 0; i < N;++i){
        int maxA = (target*X[i]-Y[i])/SM[i]+1;
        int maxB = (target*X[i]-Y[i])/SV[i]+1;
        int tCost = INT_MAX;
        for(int a = 0; a <= maxA; ++a){
            int l = 0, r = maxB;
            int b=0;
            while(l <= r){
                b =(l+r)/2;
                if(a*SM[i]+b*SV[i]+Y[i] >= target*X[i]){
                    tCost= min(tCost,a*PM[i]+b*PV[i]);
                    r=b-1;
                }else{
                    l=b+1;
                }
            }
        }
        money-=tCost;
        if(money < 0){
            break;
        }
    }
    // cout<<"target:"<<target<<" res:"<<money<<endl;
    return money >= 0;
}
int solve()
{
    int l = 0, r = 1000100;
    
    int mid = (l+r)/2;
    int res = 0;
    while(l <= r){
        // cout<<"check:"<<l<<" "<<r<<endl;
        mid = (l+r)/2;
        if(validate(mid)){
            res = mid;
            l = mid+1;
        }else{
            r = mid-1;
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
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
#endif
    cin>>N>>M;
    for(int i = 0; i < N;++i){
        cin>>X[i]>>Y[i]>>SM[i]>>PM[i]>>SV[i]>>PV[i];
    }
    cout<<solve();
    return 0;
}
