/******************************************************************************
https://www.acmicpc.net/problem/25845
algo: dp xuôi(xây từ gốc 0 0 0)
algo: string
Build string từ 3 string đã cho, đếm số cách để build được string message

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int res = 0;
vector<vector<vector<int>>> dp(101,vector<vector<int>>(101,vector<int>(101,0)));
//wi words[wi]
//ci character words[wi][ci]

int solve(string words[], string & message){
    dp[0][0][0] = 1;
    for(int i = 0; i <= words[0].length(); ++i){
        for(int j = 0; j <= words[1].length() ;++j){
            for(int k = 0; k <= words[2].length();++k){
                // cout<<"i: "<<i<<" j: "<<j<<" k: "<<k<<" t: "<<t<<" message[t]: "<<message[t]<<endl;
                int t= i + j + k;
                if(t >= message.length()) continue;
                //tại dp[i][j][k] đã có số cách để build được string message[0..t-1], giờ cần xét message[t]
                if(i < words[0].length() && words[0][i] == message[t] ){
                    dp[i+1][j][k] += dp[i][j][k];
                    dp[i+1][j][k] %= 1000000007;
                    // cout<<"dp["<<i+1<<"]["<<j<<"]["<<k<<"]: "<<dp[i+1][j][k]<<endl;
                }
                if(j < words[1].length() && words[1][j] == message[t] ){
                    dp[i][j+1][k] += dp[i][j][k];
                    dp[i][j+1][k] %= 1000000007;
                    // cout<<"dp["<<i<<"]["<<j+1<<"]["<<k<<"]: "<<dp[i][j+1][k]<<endl;
                }
                if(k < words[2].length() && words[2][k] == message[t] ){
                    dp[i][j][k+1] += dp[i][j][k];
                    dp[i][j][k+1] %= 1000000007;
                    // cout<<"dp["<<i<<"]["<<j<<"]["<<k+1<<"]: "<<dp[i][j][k+1]<<endl;
                }
            }
        }
    }
    int i = words[0].length();
    int j = words[1].length();
    int k = words[2].length();
    // dp[i][j][k] = dp[i-1][j][k] + dp[i][j-1][k] + dp[i][j][k-1];
    return dp[i][j][k];
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
    string words[3];
    string message;
    for(int i = 0; i < 3;++i){
        cin>>words[i];
    }
    cin>>message;
    cout<<solve(words, message);
	return 0;
}
