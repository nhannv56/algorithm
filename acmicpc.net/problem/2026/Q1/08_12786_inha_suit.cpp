/******************************************************************************

https://www.acmicpc.net/problem/27361
algo:dp

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int N,T;
vector<vector<int>> dp;//col, high, pos

int cal(vector<vector<bool>>& cols, int pos, int i){
    if(i >= N){
        return 0;
    }
    if(dp[i][pos]!= -1){
        return dp[i][pos];
    }
    int o=100,a=100,b =100,c=100,t=100;
    // cout<<"col:"<<i<<" : "<<pos<<" :";
    // for(int m = 1; m <=20;m++){
    //     cout<<cols[i][m]<<" ";
    // }
    // cout<<endl;
    if(cols[i][pos]){
        // cout<<"o:"<<i<<" pos:"<<pos<<endl;
        o = cal(cols, pos, i+1);
    }
    if(pos+1<=20 && cols[i][pos+1]){
        // cout<<"a:"<<i<<" pos:"<<pos<<endl;
        a = cal(cols,pos+1,i+1);
    }
    if(pos-1 > 0 && cols[i][pos-1]){
        // cout<<"o:"<<i<<" pos:"<<pos<<endl;
        c = cal(cols,pos-1,i+1);
    }
    if(cols[i][min(pos*2,20)]){
        b = cal(cols,min(pos*2,20),i+1);
    }
    //t
    for(int m = 1; m <= 20; m++){
        if(m != pos && m != pos+1 && m  !=pos-1 && m != min(pos*2,20) && cols[i][m]){
            // cout<<"t:"<<i<<" pos:"<<pos<<endl;
            t = min(cal(cols, m, i+1)+1,t);
        }
    }
    
    int res = std::min({o,a,b,c,t});
    dp[i][pos]=res;
    return res;
}

int solve(vector<vector<bool>>& cols,int T){
    dp = vector<vector<int>>(N,vector<int>(21,-1));
    int res = cal(cols, 1, 0);
    return res > T ? -1: res;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>N>>T;
	vector<vector<bool>> cols(N, vector<bool>(21, false));
	int M, pos;
	for(int i = 0; i < N; i++){
	    cin>>M;
	    for(int m = 0; m < M; m++){
	        cin>>pos;
	        cols[i][pos] = true;
	    }
	}
    cout<<solve(cols, T);
	return 0;
}