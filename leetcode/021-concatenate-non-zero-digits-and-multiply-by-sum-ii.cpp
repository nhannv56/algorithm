/**
algo: string
algo: prefix
algo: precompute, module cua so lon
**/
const int MOD = 1e9 + 7;
const int MAX_N = 100001;
long long pow10[MAX_N];
int init = []() {
    pow10[0] = 1;
    for (int i = 1; i < MAX_N; ++i) {
        pow10[i] = (pow10[i - 1] * 10) % MOD;
    }
    return 0;
}();
class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        // init();
        int n = s.length();
        vector<long long> sum(s.length() + 1, 0), x(n + 1, 0), cnt(n + 1, 0);
        for (int i = 0; i < s.length(); ++i) {
            int d = s[i] - '0';
            sum[i + 1] = sum[i] + d;
            x[i + 1] = (d > 0) ? (x[i] * 10 + d) % MOD : x[i]; //?
            cnt[i + 1] = cnt[i] + (d > 0);
        }
        vector<int> res(queries.size(), 0);
        for (int i = 0; i < queries.size(); ++i) {
            int l = queries[i][0];
            int r = queries[i][1] + 1;
            int noneZeroCount = cnt[r] - cnt[l];
            long long sumlr = sum[r] - sum[l];
            long long valX = (x[r] - x[l] * pow10[noneZeroCount] % MOD + MOD) % MOD;
            res[i]=(valX*sumlr) %MOD;
        }
        return res;
    }
};
