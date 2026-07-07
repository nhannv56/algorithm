/******************************************************************************

https://codejam.lge.com/contest/problem/1677/2
algo: greedy
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, M;

long long solve(vector<long long> &a)
{
    long long res = 0;
    sort(a.begin(), a.end());
    // for(auto i : a){
    //     cout<<i<<' ';
    // }cout<<endl;
    int idx = 0;
    while(idx < a.size()){
        int maxSize = a[idx];
        idx+=a[idx];
        ++res;
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
