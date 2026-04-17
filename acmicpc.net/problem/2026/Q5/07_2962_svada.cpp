/***
https://www.acmicpc.net/problem/2962
2 lần binary search
lần 1: tìm thời gian cần thiết để có được T quả dừa
lần 2: tìm số dừa của mỗi con khỉ tại thời gian đó
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
struct monkey
{
    long long a, b;
};
long long countCoconut(vector<monkey> &m, long long time)
{
    long long total = 0;
    for (int i = 0; i < m.size(); ++i)
    {
        if (time >= m[i].a)
        {
            total += (time - m[i].a) / m[i].b + 1;
        }
    }
    return total;
}
//tìm thời gian cần thiết để có được coconutCount quả dừa
long long timeNeed(vector<monkey> &m, long long coconutCount)
{
    long long l = 0, r = 1e12;//time
    while (l < r)
    {
        long long mid = (l + r) / 2;
        if (countCoconut(m, mid) >= coconutCount)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
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
    //binary search theo số dừa hái được để tìm thời gian cần thiết để có được T quả dừa
    long long l = 0, r = T*M;
    long long res = 0;
    while (l <= r)
    {
        long long mid = (l + r) / 2;
        long long t1 = timeNeed(m1, mid);
        long long t2 = timeNeed(m2, mid);
        if (t1 + t2 == T)
        {
            res = t1;
            break;
        }
        else if (t1 + t2 < T)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    cout << res;
    return 0;
}
