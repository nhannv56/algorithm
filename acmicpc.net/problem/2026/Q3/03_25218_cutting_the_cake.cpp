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
vector<vector<pair<int,int>>> prefixS,prefixB, prefixR;
string fi;
long long cal( int i, int r,int c,const vector<string> & cake, vector<vector<vector<long long>>>& dp){
    if(i == N-1){
        bool valid = false;
        if(fi[i]=='S'){
            for(auto rr : prefixS){
                if(rr[C].second-rr[c].second > 0){
                    valid = true;
                    break;
                }
            }
        }else if(fi[i]=='B'){
            for(auto rr : prefixB){
                if(rr[C].second-rr[c].second >0){
                    valid = true;
                    break;
                }
            }
        }else if(fi[i]=='R'){
            for(auto rr : prefixR){
                if(rr[C].second-rr[c].second >0){
                    valid = true;
                    break;
                }
            }
        }
        return valid?1:0;
    }
    if(r<R && c< C){
        if(dp[i][r][c] == -1){
            dp[i][r][c]=0;
            bool validRow = false,validCol = false;
            for(int rr = r+1; rr < R;++rr){
                //check condition
                for(int t = r+1; t < rr+1;++t){
                    if(fi[i]=='S'){
                        if(prefixS[t][C].second-prefixS[t][c].second >0){
                            validRow = true;
                            break;
                        }
                    }else if(fi[i]=='B'){
                        if(prefixB[t][C].second-prefixB[t][c].second >0){
                            validRow = true;
                            break;
                        }
                    }else if(fi[i]=='R'){
                        if(prefixR[t][C].second-prefixR[t][c].second >0){
                            validRow = true;
                            break;
                        }
                    }
                }
               
                if(validRow){
                    dp[i][r][c]+= cal(i+1,rr,c,cake, dp);
                }
            }
            for(int cc = c+1; cc < C;++cc){
                //check condition
                for(int t = c+1; t < cc+1;++t){
                    if(fi[i]=='S'){
                        if(prefixS[R][t].first-prefixS[r][t].first >0){
                            validCol = true;
                            break;
                        }
                    }else if(fi[i]=='B'){
                        if(prefixB[R][t].first-prefixB[r][t].first >0){
                            validCol = true;
                            break;
                        }
                    }else if(fi[i]=='R'){
                        if(prefixR[R][t].first-prefixR[r][t].first >0){
                            validCol = true;
                            break;
                        }
                    }
                }
                
                if(validCol){
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
    prefixS = vector<vector<pair<int,int>>>(R+1, vector<pair<int,int>>(C+1, {0,0}));
    prefixB = vector<vector<pair<int,int>>>(R+1, vector<pair<int,int>>(C+1, {0,0}));
    prefixR = vector<vector<pair<int,int>>>(R+1, vector<pair<int,int>>(C+1, {0,0}));
    for(int i = 1; i <=R; ++i){
        for(int j = 1; j <=C; ++j){
            prefixS[i][j].first  =  prefixS[i-1][j].first;//prefix theo cot
            prefixS[i][j].second =  prefixS[i][j-1].second;//theo hang
            prefixB[i][j].first  =  prefixB[i-1][j].first;//prefix theo cot
            prefixB[i][j].second =  prefixB[i][j-1].second;//theo hang
            prefixR[i][j].first  =  prefixR[i-1][j].first;//prefix theo cot
            prefixR[i][j].second =  prefixR[i][j-1].second;
            switch (cake[i-1][j-1])
            {
            case 'S':
                /* code */
                ++prefixS[i][j].first;//prefix theo cot
                ++prefixS[i][j].second;//theo hang
                break;
            case 'B':
                ++prefixB[i][j].first;//prefix theo cot
                ++prefixB[i][j].second;
                break;
            case 'R':
                ++prefixR[i][j].first;//prefix theo cot
                ++prefixR[i][j].second;
                break;
            default:
                break;
            }            
        }
    }
    // cout<<"prefixS\n";
    // for(int i = 0; i <= R;++i){
    //     for(int j = 0; j <= C;++j){
    //         cout<<'('<<prefixS[i][j].first<<", "<<prefixS[i][j].second<<") ";
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
