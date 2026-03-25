/***
 * https://www.acmicpc.net/problem/28311
 * algo: bfs
 * algo: graph
 * algo: dp
 * dùng bfs nhiều lần tính từ pawn đến mọi vị trí,
 * từ destiation đến mọi vị tri
 * khi w bị xóa phần reduce  -> pawn -> empty cell gần w bị xóa -> w -> destation vs pawn -> destiation
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
int bfs(const pair<int,int>& s,const vector<string>& grid, vector<vector<int>>& dist,const vector<vector<int>> & pawnGrid){
    deque<std::pair<int, pair<int,int>>> pq;
    int res = 0;
    pq.push_back({0,s});
    vector<vector<bool>> visited(R,vector<bool>(C, false));
    visited[s.first][s.second] = true;
    while(!pq.empty()){
        auto [step, pos] = pq.front();pq.pop_front();
        // cout<<"cur:"<<pos.first<<" "<<pos.second<<'\n';
        if(pawnGrid[pos.first][pos.second]!=-1){
            res+= step;
        }
        dist[pos.first][pos.second] = step;
        for(int i = 0; i < 4; ++i){
            int nx = pos.first+mv[i][0];
            int ny = pos.second+mv[i][1];
            if(nx>=0 && nx <R && ny >=0 && ny<C && !visited[nx][ny] && grid[nx][ny]!='W'){
                pq.push_back({step+1,{nx,ny}});
                visited[nx][ny] = true;
            }
        }
    }
    return res;
}
// Tính toán từ pawn -> w -> destiation reduce
int cal(const pair<int,int>& s, const vector<string>& grid,const vector<vector<int>>& dist,vector<vector<int>> &pawnGrid,
    const vector<vector<vector<int>>>& pte, const vector<pair<int,int>>& pawn){
    int wtd = INT_MAX;
    int reduce = 0;
    //min reduce từ wall bị xóa đến dest
    for(int i = 0; i < 4; ++i){
        int nx = s.first+mv[i][0];
        int ny = s.second+mv[i][1];
        if(nx>=0 && nx <R && ny >=0 && ny<C && grid[nx][ny]!='W'&& dist[nx][ny]!= INT_MAX){
            // cout<<"wtd:"<<wtd<<endl;
            wtd = min(wtd,dist[nx][ny]+1);
            
        }
    }
    //tính lượng reduce pawn -> empty cell gần w -> w -> dest
    vector<int> ptdreduce(N, 0);//pawn to destiation reduce
    if(wtd != INT_MAX){
        for(int i = 0; i < 4; ++i){
            int nx = s.first+mv[i][0];
            int ny = s.second+mv[i][1];
            if(nx>=0 && nx <R && ny >=0 && ny<C && grid[nx][ny]!='W'){
                for(int j = 0; j < N;++j){
                    int newDis = INT_MAX;
                    if(pte[j][nx][ny]!= INT_MAX){
                        newDis = wtd + pte[j][nx][ny]+1;
                    }
                    if(newDis < dist[pawn[j].first][pawn[j].second]){
                        // Lưu mức reduce tối đa có thể cho 4 lựa chọn
                        ptdreduce[j] = max(ptdreduce[j], dist[pawn[j].first][pawn[j].second]-newDis);
                    }
                }
            }
        }
    }
    for(auto it : ptdreduce){
        reduce+=it;
    }
    return reduce > 0 ? reduce: 0;
}
pair<int,int>solve(const vector<string>& grid,const vector<pair<int,int>>& pawn, int r, int c){
    origin = 0;
    net = 0;
    vector<vector<int>> dist(grid.size(),vector<int>(grid[0].length(),INT_MAX));
    vector<vector<int>> pawnGrid(R,vector<int>(C, -1));
    for(int i = 0; i < pawn.size();++i){
        pawnGrid[pawn[i].first][pawn[i].second]= i;
    }
    origin = bfs({r,c}, grid, dist, pawnGrid);
    //pawn to every w
    vector<vector<vector<int>>> pte(N,vector<vector<int>>(grid.size(),vector<int>(grid[0].length(),INT_MAX)));
    for(int i = 0; i < pawn.size();++i){
        bfs(pawn[i],grid,pte[i],pawnGrid);
    }
    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C; ++j){
            if(grid[i][j]=='W'){
                net+=cal({i,j},grid,dist,pawnGrid,pte, pawn);
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