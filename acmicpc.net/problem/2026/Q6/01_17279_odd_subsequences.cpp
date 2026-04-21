/***
https://www.acmicpc.net/problem/17279
algo: dp
algo: knapsack
algo: sort
xét trên tổng tính số trường hợp sinh ra được tổng thỏa mãn điều kiện
dp knapsack để tính các số có xuất hiện để tính tổng
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long cal(int index, int sum, vector<int> &Arr, vector<int> &counts, vector<vector<long long>> &dp)
{
    if (sum == 0)
    {
        return 1LL;
    }
    if (index == counts.size() || sum < 0)
    {
        return 0LL;
    }

    if (dp[sum][index] == -1)
    {
        dp[sum][index] = 0;
        for (int i = 0; i <= counts[index]; ++i)
        {
            dp[sum][index] += cal(index + 1, sum - i * Arr[index], Arr, counts, dp);
        }
    }
    return dp[sum][index];
}
long long solve(vector<int> &Arr, vector<int> &counts, int sum)
{
    long long res = 0;
    vector<vector<long long>> dp(sum + 1, vector<long long>(Arr.size() + 1, -1));
    for (int t = 1; t <= sum; ++t)
    {
        int tmp = t;
        int digit = 0;
        int numOdd = 0;
        while (tmp > 0)
        {
            digit = tmp % 10;
            if (digit % 2 != 0)
            {
                numOdd++;
            }
            tmp /= 10;
        }
        if (numOdd % 2 != 0)
        {
            res += cal(0, t, Arr, counts, dp);
            // cout<<"solve:"<<t<<" "<<res<<endl;
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
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
#endif
    int T;
    int N;
    cin >> T;
    while (T > 0)
    {
        cin >> N;
        vector<int> A(N);
        int sum = 0;
        for (int i = 0; i < N; ++i)
        {
            cin >> A[i];
            sum += A[i];
        }
        sort(A.begin(), A.end());
        //---------------
        vector<int> Arr;
        vector<int> counts;
        Arr.push_back(A[0]);
        counts.push_back(1);
        for (int i = 1; i < N; ++i)
        {
            if (A[i] != A[i - 1])
            {
                Arr.push_back(A[i]);
                counts.push_back(1);
            }
            else
            {
                counts[counts.size() - 1]++;
            }
        }
        // cout<<"Size:"<<Arr.size()<<" "<<counts.size()<<endl;
        // for(int i = 0; i < Arr.size();++i){
        //     cout<<"C:"<<Arr[i]<<" c:"<<counts[i]<<endl;
        // }
        cout << solve(Arr, counts, sum) << endl;
        --T;
    }
    return 0;
}
