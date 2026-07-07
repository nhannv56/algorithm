/******************************************************************************

https://codejam.lge.com/contest/problem/1677/2
algo: greedy
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, M;

int solve(vector<int> &a)
{
    int res = a[10];

    //%10 = 0
    for (int i = 20; i <= 1000 && M > 0; i += 10)
    {
        int needCut = i / 10 - 1;
        while (a[i] > 0 && M > 0)
        {
            if (M >= needCut)
            {
                M -= needCut;
                res += i / 10;
            }else{
                res+=M;
                M = 0;
            }
            a[i]--;
        }
    }
    for (int i = 11; i <= 1000 && M > 0; i++){
        int needCut = i / 10;
        while (a[i] > 0 && M > 0)
        {
            if (M >= needCut)
            {
                M -= needCut;
                res += needCut;
            }else{
                res+=M;
                M = 0;
            }
            a[i]--;
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
    cin >> N >> M;
    vector<int> items(1001, 0);
    int val;
    for (int i = 0; i < N; ++i)
    {
        cin >> val;
        ++items[val];
    }
    cout << solve(items);
    return 0;
}
