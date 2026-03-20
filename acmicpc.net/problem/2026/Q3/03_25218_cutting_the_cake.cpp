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
int  prefixS[101][101],prefixB[101][101], prefixR[101][101];
string fi;
long long dp[10][100][100];
long long mod = 1e9+7;
inline long long cal(const int& i,const int& r,const int& c,const vector<string> & cake){
    // cout<<"i: "<<i<<" r: "<<r<<" c: "<<c<<'\n';
    if(i == N-1){
        bool valid = false;
        if(fi[i]=='S'){
            auto countS = prefixS[R][C]-prefixS[R][c]-prefixS[r][C]+prefixS[r][c];
            if(countS > 0){
                valid = true;
            }
        }else if(fi[i]=='B'){
            auto countB = prefixB[R][C]-prefixB[R][c]-prefixB[r][C]+prefixB[r][c];
            if(countB >0){
                valid = true;
            }
        }else if(fi[i]=='R'){
            auto countR = prefixR[R][C]-prefixR[R][c]-prefixR[r][C]+prefixR[r][c];
            if(countR >0){
                valid = true;
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
                if(!validRow){
                    if(fi[i]=='S'){
                        if(prefixS[rr][C]-prefixS[rr][c] - prefixS[r][C]+prefixS[r][c] >0){
                            validRow = true;
                        }
                    }else if(fi[i]=='B'){
                        if(prefixB[rr][C]-prefixB[rr][c] - prefixB[r][C]+prefixB[r][c] >0){
                            validRow = true;
                        }
                    }else if(fi[i]=='R'){
                        if(prefixR[rr][C]-prefixR[rr][c] - prefixR[r][C]+prefixR[r][c] >0){
                            validRow = true;
                        }
                    }
                }
               
                if(validRow){
                    dp[i][r][c]+= cal(i+1,rr,c,cake);
                    dp[i][r][c]%=mod;
                }
            }
            for(int cc = c+1; cc < C;++cc){
                //check condition
                if(!validCol){
                    if(fi[i]=='S'){
                        if(prefixS[R][cc]- prefixS[r][cc]-prefixS[R][c]+prefixS[r][c] >0){
                            validCol = true;
                        }
                    }else if(fi[i]=='B'){
                        if(prefixB[R][cc]-prefixB[r][cc] - prefixB[R][c]+prefixB[r][c] >0){
                            validCol = true;
                        }
                    }else if(fi[i]=='R'){
                        if(prefixR[R][cc]-prefixR[r][cc] - prefixR[R][c]+prefixR[r][c] >0){
                            validCol = true;
                        }
                    }
                }
                if(validCol){
                    dp[i][r][c]+= cal(i+1,r,cc,cake);
                    dp[i][r][c]%=mod;
                }               
            }
        }
        return dp[i][r][c];
    }
    return 1;
}
inline long long solve(vector<string>& cake){
    // vector<vector<vector<long long>>> dp(N, vector<vector<long long>>(R, vector<long long>(C,-1)));
    memset(dp, -1, sizeof(dp));
    // prefixS = vector<vector<int>>(R+1, vector<int>(C+1, 0));
    // prefixB = vector<vector<int>>(R+1, vector<int>(C+1, 0));
    // prefixR = vector<vector<int>>(R+1, vector<int>(C+1, 0));
    for(int i = 1; i <=R; ++i){
        for(int j = 1; j <=C; ++j){
            prefixS[i][j] = prefixS[i-1][j] + prefixS[i][j-1] - prefixS[i-1][j-1];
            prefixB[i][j] = prefixB[i-1][j] + prefixB[i][j-1] - prefixB[i-1][j-1];
            prefixR[i][j] = prefixR[i-1][j] + prefixR[i][j-1] - prefixR[i-1][j-1];
            switch (cake[i-1][j-1])
            {
            case 'S':
                ++prefixS[i][j];
                break;
            case 'B':
                ++prefixB[i][j];
                break;
            case 'R':
                ++prefixR[i][j];
                break;
            default:
                break;
            }
            // cout<<"( "<<prefixS[i][j]<<" "<<prefixB[i][j]<<" "<<prefixR[i][j]<<" ), ";            
        }
        // cout<<'\n';
    }
    return cal( 0, 0, 0, cake);
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
    memset(prefixS, 0, sizeof(prefixS));
    memset(prefixB, 0, sizeof(prefixB));
    memset(prefixR, 0, sizeof(prefixR));
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
