/******************************************************************************

https://www.acmicpc.net/problem/9077
Bruteforcing
Prefix Sum

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int T;
bool arr[10001][10001];
int res = 0;
unordered_map<int,int> dp;
int N;
void squareCount(int right, int top){
    int cnt = 0;
    if(right >=10 && top >=10){
        if(dp.find((right*N)+top) == dp.end()){
            for(int x = right - 10; x <= right; ++x){
                for(int y = top -10; y <= top; ++y){
                       //cout<<"count:"<<x<<y<<endl;
                   if(arr[x][y]){
                       ++cnt;
                   } 
                }
            }
            dp[(right*N)+top] = cnt;
            res = max(cnt, res);
            //return cnt;
        }else{
            //return dp[right*top];
        }
    }else{
        //return -1;
    }
}

/**
 * x,y start with top, left and move up, right 
 * move up y+1, check and remove y-10 line, add x+1 line
 * move right x+1, check and remove x-10 line and add x+1 line;
 * **/
void cal(const int & x,const int & y){
    int top = x;
    int right = y;
    int maxX = x+10;
    int maxY = y+10;
    for(int i = x; i <= maxX && i <=10000; ++i){
        for(int j = y; j <=maxY && j <=10000;++j){
            if(i >= 10 && j >=10){
                //cout<<"top:"<<i<<" right:"<<j<<endl;
                int dpI=i*N+j;
                int dpIi1j = (i-1)*N+j;
                int dpIij1 = i*N+j-1;
                if(dp.find(dpI) == dp.end()){
                    // if(dp.find(dpIi1j) != dp.end()){
                    //     dp[dpI] = dp[dpIi1j];
                    //     for(int k = 0; k <= 10; k++){
                    //         dp[dpI] += (arr[i-11][k] ? -1 : 0) + (arr[i][k] ? 1 : 0);
                    //     }
                    //     res = max(dp[dpI], res);
                    // }else if(dp.find(dpIij1) != dp.end()){
                    //     dp[dpI] = dp[dpIij1];
                    //     for(int k = 0; k <= 10; k++){
                    //         dp[dpI] += (arr[k][j-11] ? -1 : 0) + (arr[k][j] ? 1 : 0);
                    //     }
                    //     res = max(dp[dpI], res);
                    // }else{
                    //     squareCount(i, j);
                    // }
                    
                    squareCount(i, j);
                }
            }else{
                //it is not a square
            }
        }
    }
}
void solve(vector<pair<int,int>> & mines){
    res = 0;
    
    dp.clear();
    
    for(auto [x, y] : mines){
        cal(x,y);
    }
    
    cout<<res<<'\n';
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>T;
    int x, y;
    for(int i = 0; i < T;++i){
        memset(arr, false, 10001*10001*sizeof(bool));
        vector<pair<int,int>> mines;
        cin>>N;
        for(int j = 0; j <N; ++j){
            cin>>x>>y;
            mines.push_back({x,y});
            arr[x][y] = true;
        }
        solve(mines);
    }
    return 0;
}
