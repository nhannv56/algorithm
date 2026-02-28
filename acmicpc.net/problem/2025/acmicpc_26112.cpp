#/******************************************************************************

algo: dp
algo: lcs 
algo: Dynamic Programming
algo: Longest Common Subsequence
*******************************************************************************/
#include <iostream>
#include<string.h>
#include<vector>
using namespace std;
vector<string> x;
vector<string> p1;
vector<string> p2;

int res = 0;
int main()
{
    int N, P1Len, P2Len;
    cin>>N>>P1Len>>P2Len;
    string tmp;
    for(int i = 0; i < N;++i){
        cin>>tmp;
        x.push_back(tmp);
    }
    for(int i = 0; i < P1Len; ++i){
        cin>>tmp;
        p1.push_back(tmp);
    }
    for(int i = 0; i < P2Len; ++i){
        cin>>tmp;
        p2.push_back(tmp);
    }
    int dp[N+1][P1Len+1][P2Len+1] = {0};
    dp[0][0][0] = 0;
    memset(dp, 0, (N+1)*(P1Len+1)*(P2Len+1)*sizeof(int));
    for(int i = 1; i <= N ; ++i){
        for(int j = 0; j <= P1Len; ++j){
            for(int k = 0; k <= P2Len; ++k){
                if(j > 0 || k > 0){
                    //chuỗi dài i = max chuỗi dài i-1, và hiện tại
                    dp[i][j][k] = max(dp[i-1][j][k],dp[i][j][k]);
                    if(j > 0){
                        //chuỗi dài i max chuội j-1,k
                        dp[i][j][k] = max(dp[i][j-1][k],dp[i][j][k]);
                        if(p1[j-1] == x[i-1]){// chuỗi tạo được bằng chuỗi target
                            dp[i][j][k] = max(dp[i-1][j-1][k]+1,dp[i][j][k]);
                        }
                    }
                    if(k > 0){
                        dp[i][j][k] = max(dp[i][j][k-1],dp[i][j][k]);
                        if(p2[k-1] == x[i-1]){
                            dp[i][j][k] = max(dp[i-1][j][k-1]+1,dp[i][j][k]);
                        }
                    }
                    //cout<<"dp["<<i<<"]:"<<dp[i][j][k]<<endl;
                }
                
            }
        }
    }
    cout<<dp[N][P1Len][P2Len]<<endl;
    return 0;
}
