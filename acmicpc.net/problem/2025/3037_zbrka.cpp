/******************************************************************************
https://www.acmicpc.net/problem/3037
algo:dp
algo:prefix sum

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;

long long solve(long long N, long long C){
    long long res = 1;
    vector<vector<long long>> dp(N+1, vector<long long>(C+1,0));
    //dp[n][c] = dp[n-1][i]+dp[n-1][i+1] +... + dp[n-1][c]
    // max c = n*(n-1)/2
    // min c-n+1
    dp[1][0] = 1;
    dp[1][1] = 0;
    if(C== 0){
        return 1;
    }
    if(N==1){
        return dp[N][C];
    }
    //start prefix with n =1 all is 1
    vector<long long> prefix(C+1,1); //store sum dp[n-1][0] to dp[maxC];//start with prefix 1
    for(int n = 2; n <=N; ++n){
        long long maxC= n*(n-1)/2;
        if(n == N && maxC < C){
            return 0;
        }
        vector<long long> prefix_next(C+1,1);
        for(int c = 0; c <= C && c <= maxC; ++c){
            long long minC = c-n+1;
            if(minC >= 1){ //minC >=1 so c always > minC and prefix[c]-prefix[minC-1] is valid
                dp[n][c] = (prefix[c] - prefix[minC-1] + 1000000007) % 1000000007;
            }else{
                dp[n][c] = prefix[c];
            }
            if(c > 0){
                prefix_next[c] = prefix_next[c-1] + dp[n][c];
            }else{
                prefix_next[c] = dp[n][c];
            }
            prefix_next[c] %=1000000007;
            //cout<<"dp["<<n<<"]["<<c<<"]="<<dp[n][c]<<endl;
            if(n== N && c == C){
                return dp[n][c];
            }
        }
        fill(prefix_next.begin()+min(C,maxC), prefix_next.end(), prefix_next[min(C, maxC)]);
        prefix = prefix_next;
    }
    return dp[N][C];
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    long long N, C;
    cin>>N>>C;
    cout<<solve(N,C);
	return 0;
}