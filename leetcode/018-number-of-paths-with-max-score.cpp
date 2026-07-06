/**
algo: dp trên lưới, dp on grid
algo: tìm đường đi trên lưới nhiều lựa chọn
Đi từ N-1,N-1 đến 0, 0
tìm đường đi có sum lớn nhất
số lượng đường đi -> dp vì 3^1000 trường hợp
**/

class Solution {
public:
    int N;
    
    long long MOD = 1e9 + 7;
    int mv[2][3] = {
        {-1, 0, -1},
        {-1, -1, 0},
    };
    pair<int,int> cal(int x,int y,vector<vector<pair<int,int>>> & dp, vector<string>& board){
        if(x==N-1 && y == N-1){
            return {0,1};
        }
        if(dp[x][y].first == -1){
            pair<int, int> res({0,0});
            dp[x][y]= res;
            int curS = 0;
            if(board[x][y]!='E'||board[x][y]!='E'){
                curS+=(board[x][y]-'0');
            }
            for(int i = 0; i < 3; ++i){
                int nx = x-mv[0][i];
                int ny = y-mv[1][i];
                if(nx < N && ny < N && board[nx][ny]!= 'X'){
                    res = cal(nx, ny, dp, board);
                    if(res.second > 0){ //có đường đi
                        if(res.first + curS > dp[x][y].first){
                            dp[x][y] = res;
                            dp[x][y].first = res.first+curS;
                        }else if(res.first + curS == dp[x][y].first){
                            dp[x][y].first = res.first+curS;
                            dp[x][y].second += res.second;
                            dp[x][y].second %=MOD;
                        }
                    }
                }
            }
        }
        
        return dp[x][y];
    }
    vector<int> pathsWithMaxScore(vector<string>& board) {
        N = board.size();
        //run dp to find dp[0][0];
        vector<vector<pair<int,int>>> dp(N, vector<pair<int,int>>(N, {-1,-1}));//score and way
        cal(0,0,dp, board);
        return {dp[0][0].first,dp[0][0].second};
        
    }
};
