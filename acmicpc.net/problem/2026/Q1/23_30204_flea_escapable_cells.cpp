/******************************************************************************

https://www.acmicpc.net/problem/30294
algo: dp
algo: bfs
bài toán là 1 con bọ có thể nhảy tối đa K ô
theo hướng mà nó đang đứng tại ô đó
nếu nhảy ra ngoài mảng -> có thể thóat
tìm số ô mà từ đó có thể thoát

Solution:
Tính trước các ô gần nhất có thể nhảy đến ô hiện tại i,j theo 4 hướng
tìm các điểm mà có thể nhảy ra ngoài trực tiếp
loang từ điểm đó đến hết

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
vector<vector<vector<pair<int,int>>>> nearest;
int N,M,K;
int res = 0;
vector<vector<int>> dp;
vector<string> cells;
int DEFAULT = 0;
int NOT_ESC = 1;
int CAN_ESC = 2;
bool canEscape(int i, int j){
    switch (cells[i][j])
    {
    case 'U':
        return i-K < 0;    
    case 'D':
        return i+K >=N;
    case 'L':
        return j-K < 0;
    case 'R':
        return j+K >=M;
    }
    return false;
}

void nextPos(const int i,const int j,deque<pair<int,int>>& dq){
    for(auto it : nearest[i][j]){
        if(it.first != -1 && it.second != -1 && dp[it.first][it.second] == DEFAULT && 
        abs(it.first - i) <= K && abs(it.second - j) <= K){
            dq.push_back(it);
            res++;
            dp[it.first][it.second] = CAN_ESC;
        }
    }
    
}
void bfs(deque<pair<int,int>>& dq){
    while(!dq.empty()){
        auto [ii,jj] = dq.front(); dq.pop_front();
        nextPos(ii,jj,dq);
    }
}
void solve(){
    dp = vector<vector<int>>(N, vector<int>(M, DEFAULT));
    deque<pair<int,int>> dq;
    for(int i  = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(dp[i][j]==DEFAULT){
                if(canEscape(i,j)){
                    dq.push_back({i,j});
                    dp[i][j] = CAN_ESC;
                    ++res;
                }
            }            
        }        
    }
    bfs(dq);
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

    cin>>N>>M>>K;
    cells = vector<string>(N);
    nearest = vector<vector<vector<pair<int,int>>>>(N, vector<vector<pair<int,int>>>(M, vector<pair<int,int>>(4,{-1,-1})));
    for(int i = 0; i < N; ++i){
        cin>>cells[i];
    }
    for(int i = 0; i  < N; ++i){
        for(int j = 0; j < M; ++j){
            if(cells[i][j] == 'R'){
                if(j < M-1){
                    nearest[i][j+1][0] = {i,j};
                }
            }else{
                if(j < M-1){
                    nearest[i][j+1][0] = nearest[i][j][0];
                }
            }
            if(cells[i][j] == 'D'){
                if(i < N-1){
                    nearest[i+1][j][1] = {i,j};
                }
            }else{
                if(i < N-1){
                    nearest[i+1][j][1] = nearest[i][j][1];
                }
            }
            int ri = N-1-i;
            int rj = M-1-j;
            if(cells[ri][rj] == 'L'){
                if(rj > 0){
                    nearest[ri][rj-1][2] = {ri,rj};
                }
            }else{
                if(rj > 0){
                    nearest[ri][rj-1][2] = nearest[ri][rj][2];
                }
            }
            if(cells[ri][rj] == 'U'){
                if(ri > 0){
                    nearest[ri-1][rj][3] = {ri,rj};
                }
            }else{
                if(ri > 0){
                    nearest[ri-1][rj][3] = nearest[ri][rj][3];
                }
            }
        }        
    }
    solve();
    cout<<res;
	return 0;
}