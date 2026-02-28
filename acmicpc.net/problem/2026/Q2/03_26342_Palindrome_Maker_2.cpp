/******************************************************************************
https://www.acmicpc.net/problem/26342
algo:lcs

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

// int dp[10001][10001];
vector<vector<int>> dp (10001, vector<int>(10001,0));
int solve(vector<int>& l1){
    auto l2 = l1;
    // memset(dp,0, (l1.size()+1)*(l1.size()+1)*sizeof(int));
    for(int i = 0; i <= l1.size();++i){
        for(int j = max(1,i-101); j <= min(i+101,(int)l1.size()); ++j){
            dp[i][j]=0;
        }
    }
    reverse(l1.begin(), l1.end());
   
    for(int i = 1; i <= l1.size();++i){
        for(int j = max(1,i-100); j <= min(i+100,(int)l1.size()); ++j){
            if(l1[i-1]==l2[j-1]){
                dp[i][j] = dp[i-1][j-1]+1;
            }else{
                dp[i][j] = max(dp[i-1][j],dp[i][j]);    
                dp[i][j] = max(dp[i][j-1],dp[i][j]);
                
            }
        }
    }
    return l1.size()-dp[l1.size()][l1.size()];
    
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
    cin>>N;
    for(int i = 1; i <= N; ++i){
        cin>>K;
        vector<int> arr(K);
        for(int j =0; j < K;++j){
            cin>>arr[j];
        }
        auto res =solve(arr);
        cout<<"Sequence #"<<i<<": "<<res<<"\n\n";
    }
	return 0;
}