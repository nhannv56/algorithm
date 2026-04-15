/***
https://www.acmicpc.net/problem/1016
algo: math
algo: sieve of eratosthenes sàng

tìm các số không phải dạng a*a*b và >=min & <=mã
dùng sàng a*a 1e6
chạy b theo biên
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
#endif
    long long mi, ma;
    cin >> mi >> ma;
    long long maxNum = sqrt(ma);
    long long sNum = 0;
    long long count = 0;
    vector<bool> visited(ma - mi + 2, false);
    for (long long c = 2; c <= maxNum; ++c)// range bình phương
    {
        long long cc = c * c;//tính bình phương
        long long i = mi / cc;
        for (; i * cc <= ma; ++i)//dùng sàng tính c*c*i
        {
            // cout<<"at:"<<i * cc<<" "<<i * cc -mi<<endl;
            if (i * cc >= mi && !visited[i * cc - mi])
            {
                ++count;
                visited[i * cc - mi] = true;
            }
        }
    }

    cout << ma - mi + 1 - count;
    return 0;
}
