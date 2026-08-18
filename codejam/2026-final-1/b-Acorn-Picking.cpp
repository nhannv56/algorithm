
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long L,N,K;
long long solve(vector<long long> items){
    long long res = LLONG_MAX;
    sort(items.begin(), items.end());
    int l = 0, r = 0;
    int i =0;
    deque<long long> dq;
    for( i = 0; i < K;++i){
        dq.push_back(items[i]);
    }
    res = dq.back()-dq.front();
    while(i < items.size()){
        dq.pop_front();dq.push_back(items[i]);
        res = min(dq.back()-dq.front(),res);
        ++i;
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
    cin >> L>>N>>K;
    vector<long long> items(N, 0);
    for (int i = 0; i < N; ++i)
    {
        cin>>items[i];
    }
    cout << solve(items);
    return 0;
}
