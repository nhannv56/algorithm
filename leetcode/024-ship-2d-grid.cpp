/**
dịch ma trận k bước
**/
class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> res(m, vector<int>(n));
        vector<int> buf(n * m);
        int nm = n * m;
        // cout<<m<<" "<<n<<endl;
       //làm phẳng để có cycle dịch
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                buf[(i * n + j + k) % nm] = grid[i][j];
                // cout<<i<<" "<<j<<endl;
                
            }
        }
      //fill lại vào ma trận
        for(int i = 0; i < m;++i){
            for(int j = 0; j < n;++j){
                res[i][j]= buf[i*n+j];
            }
        }
        return res;
    }
};
