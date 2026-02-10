/******************************************************************************

https://www.acmicpc.net/problem/25806
dynamic programing bài toàn rơi trứng

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

vector<vector<long long>>dp;
long long cal(int w, int k){
    int res = -1;
    //$f(w, k) = f(w-1, k-1) + f(w-1, k)$
    // cần w tuần với k lần thử để thử tất cả các nhà hàng
    if(dp[w][k]!=-1){
        return dp[w][k];
    }else{
        dp[w][k] = cal(w-1,k-1) + cal(w-1,k)+1;
    }
    if(dp[w][k]> dp.size()){
        dp[w][k] = dp.size();
    }
    return dp[w][k];
}
int solve(long long N, long long K)
{
    if (K == 1)
    {
        return N - 1;
    }
    if(K >= ceil(log2(N))){
        return ceil(log2(N));
    } 
    // sử dụng duyệt tránh tràn số
    int w=0;
    for(w = 1; w < N; ++w){
        auto res = cal(w, K);
        // cout<<"res:"<<w<<" "<<res<<endl;
        if(res >= N-1){
            break;
        }
    }
    return w;
    //sử dụng binary search
    // int l=1, r= N-1;

    // int w=1;
    // while(l <= r){
    //     int mid = (l+r)/2;
    //     if(cal(mid,K) >= N-1){
    //         w=mid;
    //         r=mid-1;
    //     }else{
    //         l=mid+1;
    //     }
    // }
    // return w;
        
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
    long long N, K;
    cin >> N >> K;
    dp = vector<vector<long long>>(N, vector<long long>(17,-1));//nxk
    vector<long long> init = vector<long long>(17, 0);
    for(int i = 0; i < N; i++){
        dp[i][0]=0;
    }
    dp[0] = init;
    cout << solve(N, K);
    return 0;
}
