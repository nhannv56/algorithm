/******************************************************************************

https://www.acmicpc.net/problem/12013
algo:dp

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;

int N;
int result = 0;
vector<vector<int>> dp;
/** Quy hoạch động trên đoạn i-j số lớn nhất sinh ra được từ i -> j
 * dp[i][j] = max{ dp[i][k]+1 nếu dp[i][k] == dp[k+1][j]
 *            { dp[i][j]
 * i <= k <j
 * dp[i][i] = a[i]
 * **/
void init(vector<int>& a){
    dp = vector<vector<int>>(N, vector<int>(N, -1));
    
    for(int i = 0; i < N; ++i){
        dp[i][i] = a[i];
        result = max(result,a[i]);
    }
}
int solve(vector<int>& a, int i, int j){ // base and count
    int res = 0;
    //initialize
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    for(int k = i; k < j;++k){
        int left = solve(a, i, k);
        int right = solve(a, k+1, j);
        if(left != 0 && right !=0 && left == right){
            dp[i][j] = max(left+1, dp[i][j]);
        }
    }
    if(dp[i][j] == -1){
        dp[i][j] = 0;
    }
    result = max(dp[i][j], result);
    // cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
    return dp[i][j];
    
}
int main(){
    
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>N;
	vector<int> A(N);
	for(int i =0; i < N; i++){
	    cin>>A[i];
	}
	init(A);
	solve(A, 0 , N-1);
	cout<<result;
	return 0;
}