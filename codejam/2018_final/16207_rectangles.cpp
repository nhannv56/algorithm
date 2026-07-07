/******************************************************************************

https://codejam.lge.com/contest/problem/16207
algo: greedy
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, M;

long long solve(vector<long long> &a)
{
    long long res = 0;
    sort(a.begin(), a.end(), greater<long long>());
    // for(auto i : a){
    //     cout<<i<<' ';
    // }cout<<endl;
    long long l=-1,r=-1;
    for(int i =0; i < a.size()-1;i+=1){
        if(abs(a[i]-a[i+1]) <=1){
            if(l==-1){
                l = min(a[i],a[i+1]);
            }else{
                r = min(a[i],a[i+1]);
            }
            ++i;
        }
        if(l!=-1 && r !=-1){
            res+=l*r;
            l=-1;
            r=-1;
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
    cin >> N;
    vector<long long> items(N, 0);
    for (int i = 0; i < N; ++i)
    {
        cin>>items[i];
    }
    cout << solve(items);
    return 0;
}
