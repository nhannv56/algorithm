/**
https://leetcode.com/problems/find-the-safest-path-in-a-grid/?envType=daily-question&envId=2026-07-01
You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:

A cell containing a thief if grid[r][c] = 1
An empty cell if grid[r][c] = 0
You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.

The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.

Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.

The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.
algo: bfs 2 lần
algo: priority queue
1 lần để tính khoảng cách an toàn của 1 điểm bất kỳ
priority quêu tìm đường đi an toàn nhất
**/
class Solution {
public:
    int N=0;
    int mv[2][4] = {
                {1,-1, 0, 0},
                {0, 0,-1, 1}};
    vector<vector<int>> safe;
    void bfs(vector<pair<int,int>> t){
        safe = vector<vector<int>>(N,vector<int>(N,-1));
        queue<pair<int,pair<int,int>>> q;
        for(auto [i,j]:t){
            q.push({0,{i,j}});
            safe[i][j]=0;
        }
        while(!q.empty()){
            auto [c,pos] = q.front();  q.pop();
            for(int i =0; i < 4; ++i){
                int nx = pos.first+mv[0][i];
                int ny = pos.second+mv[1][i];
                if(0<=nx && nx <N && 0<=ny && ny < N && safe[nx][ny]==-1){                    
                    q.push({c+1,{nx,ny}});
                    safe[nx][ny]= c+1;
                    
                }
            }
        }
    }
    
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int res = 0;
        N = grid.size();
        // vector<vector<int>> rowsT(N),colsT(N);
        vector<pair<int,int>> thief;
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid.size();++j){
                if(grid[i][j]==1){
                    thief.push_back({i,j});
                }
            }
        }
        bfs(thief);
        vector<vector<bool>> visited(N,vector<bool>(N,false));
        priority_queue<pair<int,pair<int,int>>> pq;
        int dis = safe[0][0];
        // cout<<"dis:"<<dis<<endl;
        visited[0][0]=true;
        if(dis!=0){
            pq.push({dis,{0,0}});
            while(!pq.empty()){
                auto [d,pos] = pq.top(); pq.pop();
                // cout<<"cur:"<<pos.first<<" "<<pos.second<<" "<<d<<endl;
                if(pos.first==N-1 && pos.second==N-1){
                    res=d;
                    break;
                }
                for(int i =0; i < 4; ++i){
                    int nx = pos.first+mv[0][i];
                    int ny = pos.second+mv[1][i];
                    if(0<=nx && nx <N && 0<=ny && ny < N && !visited[nx][ny]){
                        int nd = min(d,safe[nx][ny]);
                        pq.push({nd,{nx,ny}});
                        visited[nx][ny] = true;
                        // cout<<"push:"<<nd<<" pos:"<<nx<<" "<<ny<<endl;
                    }
                }
            }
        }
        return res;
    }
};
