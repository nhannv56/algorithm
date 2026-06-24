class Solution {
public:
    long long MOD = 1e9+7;
    /***
    algo: dp
    algo: prefix
    thuật toán dp, với độ dài x từ 2->n với xu hướng tăng/giảm thì hiện tại có bao nhiêu chuỗi
    có bao nhiêu chuỗi có thể sinh ra tiếp theo kết thúc bằng i có độ dài x+1
    Tính với độ dài x kết thúc bởi phần tử giá trị i có bao nhiêu cách vs 2 xu hướng
    **/
    int zigZagArrays(int n, int l, int r) {
        int k = r-l+1;
        vector<vector<vector<long long>>> dp(n+1, vector<vector<long long>>(2, vector<long long>(k+1,0)));
        vector<vector<long long>> prefix(2, vector<long long>(k+1,0));
        for(int i = 1; i <= k; ++i){
            dp[2][0][i]= k-i;// với n = 2 xu hướng trước đó là giảm kết thúc bởi i thì có bao nhiêu cách
            dp[2][1][i]=i-1; // với n = 2 xu hướng trước đó là tăng kết thúc bởi i thì có bao nhiêu cách
            //
            prefix[0][i] = prefix[0][i-1]+k-i;
            prefix[1][i] = prefix[1][i-1]+i-1;
        }
        // cout<<"range:1 to "<<k<<endl;
        // for(int i = 1; i <= k ; ++i){
        //     cout<<"desc:"<<i<<" :"<<dp[2][0][i]<<endl;
        // }
        // for(int i = 1; i <= k ; ++i){
        //     cout<<"inc:"<<i<<" :"<<dp[2][1][i]<<endl;
        // }
        for(int s = 3; s <= n; ++s){
            for(int i = 1; i <=k;++i){
                dp[s][0][i]= (prefix[1][k] - prefix[1][i]) % MOD;
                dp[s][1][i]= (prefix[0][i-1] - prefix[0][0]) % MOD;
            }
            for(int i = 1; i <=k; ++i){
                prefix[0][i] = prefix[0][i-1]+dp[s][0][i];
                prefix[1][i] = prefix[1][i-1]+dp[s][1][i];
            }
        }
        long long res = 0;
        for(int i = 1; i <= k; ++i){
            res = (res+dp[n][0][i]+dp[n][1][i])%MOD;
        }
        return res;

    }
};
