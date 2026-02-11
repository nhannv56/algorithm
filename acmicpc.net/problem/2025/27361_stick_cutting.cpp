/******************************************************************************

https://www.acmicpc.net/problem/27361
Dynamic Programming
Knapsack

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
long long T,N,K, a, b;

long long maxP = 1e18;
long long solve(int pos, long long k,const long long arr[]){
    long long result = 0;
    int len1 = 0;
    for(int i = 0; i < N; ++i){
        if(arr[i] == 1){
            len1++;
        }
    }
    if(len1 >= k){
        return 0;
    }
    k-= len1;
    const long long INF = 1e18;
    vector<long long> dp(k + 1, INF);
    dp[0] = 0;
    for(int i = 0; i < N; i++){
        if(arr[i] != 1){
            long long cost = a*(arr[i]-1)*(arr[i]-1) +b;
            for(int j = k; j >=1; --j){
                int prev = max(j-arr[i], 0ll);
                dp[j] = min(dp[j], dp[prev]+cost);
            }
        }
    }
    return dp[k];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>T;
    
    for(int t = 0; t < T; t++){
        //cout<<"TC:"<<t<<endl;
        cin>>N>>K>>a>>b;
        //cout<<N<<" "<<K<<" "<<a<<" "<<b<<endl;
        long long arr[N];
        long long dp[K+1];
        //memset(dp, maxP, sizeof(long long)*(K+1));
        dp[0] = 0;
        for(int i = 0; i < N;++i){
            cin>>arr[i];
        }
        cout<<solve(0, K, arr)<<'\n'   ;
    }
	return 0;
}