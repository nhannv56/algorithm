/******************************************************************************

https://www.acmicpc.net/problem/11062 game
algo:game
algo:dp

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int T,N;

int maxScore(int i, int j,const vector<int>& cards,vector<vector<int>>& dp){
    int res = 0,l1,l2,r1,r2;
    
    if(i > j || i >= cards.size()||j < 0){
        return 0;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    if(i==j){
        return cards[i];
    }else{
        //select cards[i]
        l1 = maxScore(i+2, j, cards, dp);//other take front
        l2 = maxScore(i+1, j-1, cards, dp);//other take rear
        //select cards[j]
        r1 = maxScore(i+1,j-1, cards, dp);//other take front
        r2 = maxScore(i,j-2, cards, dp);//other take rear
    }
    
    res = max(cards[i]+min(l1,l2), cards[j]+min(r1,r2));
    
    dp[i][j] = res;
    return res;
}
int solve(vector<int> cards){
    int aliceScore = 0;
    vector<vector<int>> dp = vector<vector<int>>(N, vector<int>(N,-1));
    
    aliceScore = maxScore(0, N-1, cards, dp);
    
    return aliceScore;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>T;
    while(T > 0){
        cin>>N;
        vector<int> cards(N);
        for(int i=0; i < N; i++){
            cin>>cards[i];
        }
        cout<<solve(cards)<<'\n';
        --T;
    }
	return 0;
}