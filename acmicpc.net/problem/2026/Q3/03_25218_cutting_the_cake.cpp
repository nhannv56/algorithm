/******************************************************************************
https://www.acmicpc.net/problem/25218
algo: dp
algo: prefix sum
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long T,R,C,N;
vector<vector<int>> prefixS,prefixB, prefixR;
string fi;
long long cal( int i, int r,int c,const vector<string> & cake, vector<vector<vector<long long>>>& dp){
    if(i == N-1){
        bool valid = true;
        if(fi[i]=='S'){
            if((prefixS[R-1][C-1]-prefixS[r][c] + (cake[r][c]=='S'?1:0))==0){
                valid = false;
            }
        }else if(fi[i]=='B'){
            if((prefixB[R-1][C-1]-prefixB[r][c] + (cake[r][c]=='B'?1:0))==0){
                valid = false;
            }
        }else if(fi[i]=='R'){
            if((prefixR[R-1][C-1]-prefixR[r][c] + (cake[r][c]=='R'?1:0))==0){
                valid = false;
            }
        }
        return valid?1:0;
    }
    if(r<R && c< C){
        if(dp[i][r][c] == -1){
            dp[i][r][c]=0;
            for(int rr = r+1; rr < R;++rr){
                //check condition
                bool valid = true;
                if(fi[i]=='S'){
                    if((prefixS[rr][C-1]-prefixS[r][c] + (cake[r][c]=='S'?1:0))==0){
                        valid = false;
                    }
                }else if(fi[i]=='B'){
                    if((prefixB[rr][C-1]-prefixB[r][c] + (cake[r][c]=='B'?1:0))==0){
                        valid = false;
                    }
                }else if(fi[i]=='R'){
                    if((prefixR[rr][C-1]-prefixR[r][c] + (cake[r][c]=='R'?1:0))==0){
                        valid = false;
                    }
                }
                if(valid){
                    dp[i][r][c]+= cal(i+1,rr,c,cake, dp);
                }
            }
            for(int cc = c+1; cc < C;++cc){
                //check condition
                bool valid = true;
                if(fi[i]=='S'){
                    if((prefixS[R-1][cc]-prefixS[r][c] + cake[r][c]=='S'?1:0)==0){
                        valid = false;
                    }
                }else if(fi[i]=='B'){
                    if((prefixB[R-1][cc]-prefixB[r][c] + cake[r][c]=='B'?1:0)==0){
                        valid = false;
                    }
                }else if(fi[i]=='R'){
                    if((prefixR[R-1][cc]-prefixR[r][c] + cake[r][c]=='R'?1:0)==0){
                        valid = false;
                    }
                }else{
                    valid = false;
                }
                if(valid){
                    dp[i][r][c]+= cal(i+1,r,cc,cake, dp);
                }
               
            }
        }
        return dp[i][r][c];
    }
    return 1;
}
long long solve(vector<string> cake){
    vector<vector<vector<long long>>> dp(N, vector<vector<long long>>(R, vector<long long>(C,-1)));
    prefixS = vector<vector<int>>(R, vector<int>(C, 0));
    prefixB = vector<vector<int>>(R, vector<int>(C, 0));
    prefixR = vector<vector<int>>(R, vector<int>(C, 0));
    for(int i = 0; i <R; ++i){
        for(int j = 0; j < C;++j){
            switch (cake[i][j])
            {
            case 'S':
                /* code */
                prefixS[i][j]=1;
                break;
            case 'B':
                prefixB[i][j]=1;
                break;
            case 'R':
                prefixR[i][j]=1;
                break;
            default:
                break;
            }
            if(i > 0){
                prefixS[i][j]+=prefixS[i-1][j];
                prefixB[i][j]+=prefixB[i-1][j];
                prefixR[i][j]+=prefixR[i-1][j];
            }
            if(j> 0){
                prefixS[i][j]+=prefixS[i][j-1];
                prefixB[i][j]+=prefixB[i][j-1];
                prefixR[i][j]+=prefixR[i][j-1];
            }
            if(i > 0 && j > 0){    
                prefixS[i][j]-=prefixS[i-1][j-1];
                prefixB[i][j]-=prefixB[i-1][j-1];
                prefixR[i][j]-=prefixR[i-1][j-1];
            }
        }
    }
    // cout<<"prefixS\n";
    // for(int i = 0; i < R;++i){
    //     for(int j = 0; j < C;++j){
    //         cout<<prefixS[i][j]<<' ';
    //     }
    //     cout<<'\n';
    // }
    // cout<<"prefixB\n";
    // for(int i = 0; i < R;++i){
    //     for(int j = 0; j < C;++j){
    //         cout<<prefixB[i][j]<<' ';
    //     }
    //     cout<<'\n';
    // }
    // cout<<"prefixR\n";
    // for(int i = 0; i < R;++i){
    //     for(int j = 0; j < C;++j){
    //         cout<<prefixR[i][j]<<' ';
    //     }
    //     cout<<'\n';
    // }
    return cal( 0, 0, 0, cake, dp);
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
    cin>>T;
    while(T>0){
        cin>>R>>C>>N;
        vector<string> cake(R);
        for(int i = 0 ; i < R;++i){
            cin>>cake[i];
        }
        
        cin>>fi;
        cout<<solve(cake)<<'\n';
        --T;
    }
	return 0;
}
