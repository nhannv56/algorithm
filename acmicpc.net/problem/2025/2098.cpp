/******************************************************************************

https://www.acmicpc.net/problem/2098
bitmask dp traveling salemans

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int N=-1;
int maxlen= 17*1000000;

vector<vector<int>> dp = vector<vector<int>>(1<<16, vector<int>(16, -1));
int resolve(int mask, int u, const vector<vector<int>> & cost) {    
    //cout<<"mask:"<<std::bitset<8>(mask)<<" u:"<<u<<endl;
    if(dp[mask][u] != -1){
        return dp[mask][u];
    }
    if(mask == 1){
        if(cost[0][u] > 0){
            return cost[0][u];
        }else{
            return maxlen;
        }
    }
    int result  = maxlen;
    //mask &= ~(1<<u);
    for(int v = 1; v < N; ++v){
        if((mask & (1<<v)) != 0 && cost[v][u] > 0){// in list and have way revert trace
            int nMask = (mask & ~(1<<v));
            // nMask &= ~(1<<u);
            result = min(result, resolve(nMask, v, cost) + cost[v][u]);
            //cout<<u<<" "<<v<<" mask:"<<std::bitset<8>(nMask)<<" cost:"<<result<<endl;
        }
    }
    //cout<<"u:"<<u<<" "<<result<<endl;
    dp[mask][u]=result;
    return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>N;
    vector<vector<int>> arr(N, vector<int>(N,-1));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N;++j){
            cin>>arr[i][j];
        }
    }
    dp[1][0]=0;
	int result = INT_MAX;
	
	int m = 1<<N;
	
	//cout<<"m:"<<std::bitset<8>(m)<<endl;
	for(int v = 1; v < N; v ++){
	    if(arr[v][0] > 0){
	       // cout<<"last: "<<std::bitset<8>(m-1)<<" "<<v<<" " <<dp[m][v]<<endl;
	        result = min(result, resolve((m-1)&~(1<<v), v, arr)+arr[v][0]);
	    }
	}
	cout<<result<<'\n';
	return 0;
}