/***
  algo: bfs
  algo: priority queue
  **/
class Solution {
public:
    int mv[2][4] = {{1,-1,0,0},{0,0,1,-1}};
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(),false));
        priority_queue<pair<int,pair<int,int>>> pq;
        pq.push({health-grid[0][0],{0,0}});
        int m = grid.size();
        int n = grid[0].size();
        int res = false;
        while(!pq.empty()){
            auto [h, pos] = pq.top();pq.pop();
            if(pos.first == m-1 && pos.second == n-1){
                res = true;
                break;
            }
            for(int i = 0; i < 4;++i){
                int nx = pos.first +mv[0][i];
                int ny = pos.second +mv[1][i];
                if(0<=nx && nx <m && 0<=ny && ny < n && !visited[nx][ny]){
                    int nh = h-grid[nx][ny];
                    if(nh>0){
                        pq.push({nh,{nx,ny}});                        
                    }
                    visited[nx][ny]=true;
                }
            }
        }
        return res;
    }
};
