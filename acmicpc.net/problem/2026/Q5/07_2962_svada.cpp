/***
https://www.acmicpc.net/problem/2962
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
struct monkey
{
    long long a, b;
};
pair<long long, long long> countCoconut(vector<monkey> &m, long long time)
{
    long long mi = 0, ma = 0;
    bool valid = false;
    for (int i = 0; i < m.size(); ++i)
    {
        if (time >= m[i].a)
        {
            if(time==m[i].a){
                mi+=1;
                ma+=1;
                valid = true;
                continue;
            }
            if ((time - m[i].a) % m[i].b == 0 && !valid)
            {
                valid = true;
                mi+= (time - m[i].a) / m[i].b + 1;
            }else if((time - m[i].a) % m[i].b == 0){
                mi+= (time - m[i].a) / m[i].b;
            }else{
                mi+= (time - m[i].a) / m[i].b+1;
            }
            // mi+= (time - m[i].a) / m[i].b;
            ma += (time - m[i].a) / m[i].b + 1;
        }else{
            return make_pair(-1LL, -1LL);
        }
    }
    return (valid ? make_pair(mi, ma) : make_pair(-1LL, -1LL));
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
    long long T, N, M;
    cin >> T;
    cin >> N;
    vector<monkey> m1(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> m1[i].a >> m1[i].b;
    }
    cin >> M;
    vector<monkey> m2(M);
    for (int i = 0; i < M; ++i)
    {
        cin >> m2[i].a >> m2[i].b;
    }
    long long l = 0, r = T;
    long long aCount = 0, bCount = 0;
    long long res = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        long long sum1 = 0, sum2 = 0;
        auto aCount = countCoconut(m1, mid);
        auto bCount = countCoconut(m2, T - mid);
        // cout<<mid<<" |"<<aCount.first<<" "<<aCount.second<<" "<<bCount.first<<" "<<bCount.second<<"\n";
        if (aCount.first == -1)
        {
            l = mid + 1;
            continue;
        }
        if (bCount.first == -1)
        {
            r = mid - 1;
            continue;
        }
        if (aCount.second < bCount.first)
        {
            l = mid + 1;
        }
        else if(aCount.first > bCount.second)
        {
            r = mid - 1;
        }
        else
        {
            res = mid;
            l = mid + 1;
            break;
        }
    }
    cout << res;
    return 0;
}
