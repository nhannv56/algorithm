/***

https://www.acmicpc.net/problem/25789
algo: graph
algo: bfs
algo: shortest path
algo: line
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
//vector 4 chiều lưu possible đi từ x0,y0 di đến x1,y1 (0<=x,y <=999)
vector<vector<bool>> dis(12,vector<bool>(12,false));
int N;
//i, j is index of pos, not coordinate
bool haveWay(int i, int j, vector<vector<pair<int,int>>> &pos){
    auto x0 = pos[0][i].first;
    auto y0 = pos[0][i].second;
    auto x1 = pos[0][j].first;
    auto y1 = pos[0][j].second;

    int minX = min(x0,x1);
    int maxX = max(x0,x1);
    int minY = min(y0,y1);
    int maxY = max(y0,y1);
    for(int k = 0; k < N; ++k){
        int x2 = pos[1][k].first;
        int y2 = pos[1][k].second;
        if((x2-x1)*(y2-y0) == (x2-x0)*(y2-y1) &&
            minX <= x2 && x2 <= maxX &&
            minY <= y2 && y2 <= maxY){
            return false;
        }
    }
    for(int k = 0; k < N; ++k){
        if(k != i && k != j){
            int x2 = pos[0][k].first;
            int y2 = pos[0][k].second;
            if((x2-x1)*(y2-y0) == (x2-x0)*(y2-y1) &&
                minX <= x2 && x2 <= maxX &&
                minY <= y2 && y2 <= maxY){
                return false;
            }
        }
    }
    
    return true;
}
int getPass(vector<vector<pair<int,int>>> &pos){
    for(int i = 0; i < N; ++i){
        for(int j = i+1; j < N; ++j){
            dis[i][j] = haveWay(i,j,pos);
            dis[j][i] = dis[i][j];
        }
    }
    int passCount = -1;
    //bfs from 0 to N-1
    //queue is number of step to reach N-1, not index of pos
    vector<bool> visited(pos[0].size(),false);
    queue<pair<int,int>> q;
    q.push({0,0});
    visited[0] = true;
    while(!q.empty()){
        auto [u,steps] = q.front();
        q.pop();
        if(u == N-1){
            passCount = steps;
            break;
        }
        for(int v = 0; v < N; ++v){
            if(dis[u][v] && !visited[v]){
                visited[v] = true;
                q.push({v,steps+1});
            }
        }
    }
    return passCount;
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
    cin >> N;
    vector<vector<pair<int,int>>> pos(2,vector<pair<int,int>>(N));
    for(int i = 0; i < N; ++i){
        cin >> pos[0][i].first >> pos[0][i].second;
    }
    for(int i = 0; i < N; ++i){
        cin >> pos[1][i].first >> pos[1][i].second;
    }
    cout<<getPass(pos);
    return 0;
}
