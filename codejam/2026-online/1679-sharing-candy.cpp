/******************************************************************************

https://codejam.lge.com/contest/problem/1677/2
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N;


void solve(vector<long long> &a)
{
    long  long res = 0;
    long long l = 0, r = 0;
    long long sum = 0;
    std::map<long long, long long, std::greater<long long>> maxInLR;
    while(r < N){
        
        sum += a[r];
        if(maxInLR.find(a[r]) == maxInLR.end()){
            maxInLR[a[r]] = 1;
        }else{
            maxInLR[a[r]]++;
        }
        while(!maxInLR.empty() && sum < 0){
            sum -= a[l];
            maxInLR[a[l]]--;
            if(maxInLR[a[l]] == 0){
                maxInLR.erase(a[l]);
            }
            // cout<<"erase: "<<l<<" sum: "<<sum<<endl;
            l++;
        }
        if(!maxInLR.empty()){
            res = max(res, sum - maxInLR.begin()->first);
            // cout<<"sum: "<<sum<<" res: "<<res<<endl;
        }
        // cout<<"l: "<<l<<" r: "<<r<<endl;        
        r++;
    }
    while(l < r){
        sum -= a[l];
        maxInLR[a[l]]--;
        if(maxInLR[a[l]] == 0){
            maxInLR.erase(a[l]);
        }
        l++;
        if(!maxInLR.empty()){
            res = max(res, sum - maxInLR.begin()->first);
            // cout<<"sum: "<<sum<<" res: "<<res<<endl;
        }
    }
    cout<<res;
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

    cin >> N ;
    vector<long long> a(N);
    for (long long i = 0; i < N; ++i)
    {
        cin >> a[i];
    }
    solve(a);
    return 0;
}
