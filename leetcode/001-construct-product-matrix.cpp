/***
https://leetcode.com/problems/construct-product-matrix/
algo : kandanes
algo:  product matrix except
  **/
class Solution {
    int MOD = 12345;

public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int product = 1;
        int n = grid.size();
        int m = grid[0].size();
        vector<int> v1(n * m, 1), v2(n * m, 1);
        vector<vector<int>> res(n, vector<int>(m));
        // cout<<n<<"x"<<m<<endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int vi = i * m + j;
                if (vi == 0) {
                    v1[0] = grid[0][0] % MOD;
                } else {
                    v1[vi] = (v1[vi - 1] * (grid[i][j] % MOD)) % MOD;
                }
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int vi = i * m + j;
                if (vi == n * m - 1) {
                    v2[n * m - 1] =
                        grid[n - 1][m - 1] % MOD;
                } else {
                    v2[vi] = (v2[vi + 1] * (grid[i][j] % MOD)) % MOD;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int vi = i * m + j;
                if (vi == 0) {
                    res[i][j] = v2[vi + 1];
                }else if (vi == n * m - 1) {
                    res[i][j] = v1[vi - 1];
                } else {
                    res[i][j] = (v1[vi - 1] * v2[vi + 1]) % MOD;
                }
            }
        }
        return res;
    }
};
