/***

https://www.acmicpc.net/problem/25900
divide


**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long solve(vector<long long> &arr)
{
    long long count = 0;
    vector<long long> countArr(1e7 + 1, 0);
    vector<long long> uniqueArr;
    for (int i = 0; i < arr.size(); ++i)
    {
        ++countArr[arr[i]];
        if (countArr[arr[i]] == 1)
        {
            uniqueArr.push_back(arr[i]);
        }
    }
    sort(uniqueArr.begin(), uniqueArr.end());
    int i = 0;
    if (countArr[0] != 0)
    {
        count += (arr.size() - countArr[0]) * countArr[0];
        ++i;
    }
    for (auto d : uniqueArr)
    {
        if(d == 0) continue;
        for (int n = d * 2; n <= uniqueArr.back(); n += d)
        {
            // auto find = lower_bound(uniqueArr.begin(), uniqueArr.end(), n);
            if (countArr[n] > 0)
            {
                count += countArr[d] * countArr[n];
                // cout << "d: " << d << " q: " << q << " n: " << n << " count: " << count << "\n";
            }
        }
    }
    return count;
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
    long long T;
    cin >> T;
    int N;
    for (int t = 1; t <= T; ++t)
    {
        cin >> N;
        vector<long long> arr(N);
        for (long long i = 0; i < N; ++i)
        {
            cin >> arr[i];
        }
        cout << "Test case #" << t << ": " << solve(arr) << "\n\n";
    }
    return 0;
}
