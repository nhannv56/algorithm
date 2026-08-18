
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, M;
long long solve(vector<long long> &b)
{
    long long ans = 0;
    stack<long long> mono;
    for (int i = 0; i < N; ++i)
    {
        auto remain = (N-i);//before
        // ans+=remain;
        // cout<<ans<<" ";
        while(!mono.empty() && b[mono.top()] < b[i])
        {
            mono.pop();
        }
        //i-l số dãy bắt đầu bên trái i bao gồm b[i] là max
        long long  l = mono.empty() ? 0 : mono.top()+1;
        
        ans+=remain*(i-l+1);
        
        // cout<<ans<<" ";
        mono.push(i);
    }
    // ans+=mono.size()-1;
    return ans;
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
        // cout<<items[i];
    }
    auto res = solve(items);
    cout<<res<<"\n";
    return 0;
}
