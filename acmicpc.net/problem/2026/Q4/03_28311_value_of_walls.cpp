/***
 * https://www.acmicpc.net/problem/28311
 * algo: bfs
 * algo: graph
 */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;
int R,C,N,r,c;
int origin = 0, net=0;
int mv[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
int bfs(pair<int,int> s,pair<int,int> e, const vector<string>& grid){
    priority_queue<std::pair<int, pair<int,int>>, 
                    std::vector<std::pair<int, pair<int,int>>>, 
                    std::greater<std::pair<int, pair<int,int>>>> pq;

    pq.push({0,s});
    vector<vector<bool>> visited(R,vector<bool>(C, false));
    visited[s.first][s.second] = true;
    while(!pq.empty()){
        auto [step, pos] = pq.top();pq.pop();
        // cout<<"cur:"<<pos.first<<" "<<pos.second<<'\n';
        if(pos.first == e.first && pos.second == e.second){
            return step;
            break;
        }
        for(int i = 0; i < 4; ++i){
            int nx = pos.first+mv[i][0];
            int ny = pos.second+mv[i][1];
            if(nx>=0 && nx <R && ny >=0 && ny<C && !visited[nx][ny] && grid[nx][ny]!='W'){
                pq.push({step+1,{nx,ny}});
                visited[nx][ny] = true;
            }
        }
    }
    return 0;
}
int cal(pair<int,int> s, pair<int,int> e, const vector<string>& grid,const vector<int>& dist,vector<vector<int>> &pawnGrid){
    int wtd = 0;
    int reduce = 0;
    priority_queue<std::pair<int, pair<int,int>>, 
                    std::vector<std::pair<int, pair<int,int>>>, 
                    std::greater<std::pair<int, pair<int,int>>>> pq;

    pq.push({0,s});
    vector<vector<bool>> visited(R,vector<bool>(C, false));
    visited[s.first][s.second] = true;
    wtd = bfs(s,e,grid);
    while(!pq.empty()){
        auto [step, pos] = pq.top();pq.pop();
        // cout<<"cur:"<<pos.first<<" "<<pos.second<<'\n';
        
        if(pawnGrid[pos.first][pos.second]!=-1){
            int item = pawnGrid[pos.first][pos.second];
            if(step+wtd < dist[item]){
                reduce+=dist[item] - (step+wtd);
            }
        }
        for(int i = 0; i < 4; ++i){
            int nx = pos.first+mv[i][0];
            int ny = pos.second+mv[i][1];
            if(nx>=0 && nx <R && ny >=0 && ny<C && !visited[nx][ny] && grid[nx][ny]!='W'){
                pq.push({step+1,{nx,ny}});
                visited[nx][ny] = true;
            }
        }
    }
    return reduce;
}
pair<int,int>solve(const vector<string>& grid,const vector<pair<int,int>>& pawn, int r, int c){
    origin = 0;
    net = 0;
    vector<int> dist(N, INT_MAX);
    for(int i = 0; i < N;++i){
        int dis = bfs(pawn[i],{r,c},grid);
        dist[i] = dis;            
        origin+=dis;
    }
    vector<vector<int>>pawnGrid(R,vector<int>(C, -1));
    for(int i = 0; i < pawn.size();++i){
        pawnGrid[pawn[i].first][pawn[i].second]= i;
    }
    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C; ++j){
            if(grid[i][j]=='W'){
                net+=cal({i,j},{r,c},grid,dist,pawnGrid);
            }
        }
    }
    return {origin,net};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
    #endif
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        cin>>R>>C>>N>>r>>c;
        vector<string> grid(R);
        vector<pair<int,int>> pawn(N);
        for(int i = 0; i < N; ++i){
            cin>>pawn[i].first>>pawn[i].second;
            pawn[i].first--;
            pawn[i].second--;
        }
        for(int i = 0; i < R;++i){
            cin>>grid[i];
        }
        auto res = solve(grid,pawn, r-1,c-1);
        cout<<res.first<<" "<<res.second<<'\n';
    }

    return 0;
}