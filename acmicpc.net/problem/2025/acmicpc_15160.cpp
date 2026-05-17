/**
  graph, dijktra, shortest path, bfs 0-1
  algo: dijktra
  algo: graph
*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
struct State {
    int row;
    int col;
    int countO;
    // add more fields if needed
    bool operator > (const State& other) const {
        return countO > other.countO;
    }
};

    //travel from first atum
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    int R, C;
    std::cin >> R >> C;
    std::vector<string> grid = vector<string>(R);
    vector<pair<int, int>> atums;
    //input grid & find atum positions
    for(int i = 0; i < R; ++i) {
        cin>>grid[i];
        for(int c = 0; c < C; ++c){
            if(grid[i][c] == 'A'){
                atums.push_back(pair<int,int>(i,c));
            }
        }
    }
    int result = -1;
    for( int i = 0; i < 4; i++ ) {
        //min heap
        priority_queue<State, vector<State>, greater<State>> pq;
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        vector<pair<int, int>> startPoints;
        visited[atums[0].first][atums[0].second] = true;

        //push first atum's adjacent cells
        //check possible moves
        //up, down, left, right
        //if cell is 'O' increase coutnter, and push to pq
        //if cell is '#' ignore
        // if cell is '.' can move to  the empty cell
        //if cell is 'A' check counter even update result = counter/2
        //if cell is 'A' check counter odd check cand find more 'O' cells if possible result = counter/2 + 1 if not move to 
        int nr = atums[0].first + dr[i];
        int nc = atums[0].second + dc[i];
        if(nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
            //cout<<grid[nr]<<endl;
            int cO = 0;
            if(grid[nr][nc] == 'O'){
                cO=1;
                //++counterOTotal;
            }
            pq.push({nr, nc, cO});
            visited[nr][nc] = true;
        }
        int counterOTotal = 0;
        int counterA2A = 0;
        bool haveReachedA  = false;
        while(!pq.empty()) {
            auto current = pq.top();
            pq.pop();
            int cr = current.row;
            int cc = current.col;
            int countO = current.countO;
            //cout<<"x:"<<cr<<",y:"<<cc<<",val:"<<grid[cr][cc]<<" o:"<<countO<<endl;
            if(grid[cr][cc] == 'O'){
                ++counterOTotal;
            }
            //check if current cell is 'A'
            if(grid[cr][cc] == 'A' && !haveReachedA) {
                haveReachedA = true;
                counterA2A = countO;
            }
            if(haveReachedA) {
                //cout<<"reached:"<<counterA2A<<endl;
                if(counterA2A % 2 == 0){
                    if(result == -1){
                        result = counterA2A /2  +1;
                    }else{
                        result = min(result, counterA2A/2 +1);
                    }
                    break;
                }else if(counterOTotal > counterA2A){
                    if(result == -1){
                        result = counterA2A /2  +2;
                    }else{
                        result = min(result, counterA2A/2 +2);
                    }
                    break;
                }
            }
            //check possible moves
            if(grid[cr][cc] == 'A') continue;
            for(int j = 0; j < 4; ++j) {
                int nr = cr + dr[j];
                int nc = cc + dc[j];
                if(nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr][nc] && grid[nr][nc] != '#') {
                    //cout<<"grid:"<<nr<<","<<nc<<":"<<grid[nr][nc]<<endl;
                    int counterONext = ((grid[nr][nc] == 'O') ? 1 : 0) + countO;
                    pq.push({nr,nc,counterONext});
                    visited[nr][nc] = true;
                }
            }
        }    
        //cout<<"end:"<<sr<<","<<sc<<endl;
        
    }
    cout <<result << endl;
    return 0;
}
