/******************************************************************************

https://www.acmicpc.net/problem/34490


*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
unordered_set<long long> valid;
unordered_set<long long> invalid;
vector<vector<vector<vector<int>>>> dp(60, vector<vector<vector<int>>>(60,vector<vector<int>>(60,vector<int>(60,-1))));
bool canReduce(long long a2, long long a3, long  long a5, long long a7){
    if(dp[a2][a3][a5][a7] != -1){
        return dp[a2][a3][a5][a7] == 1;
    }else{
        long long cur = pow(2,a2)*pow(3,a3)*pow(5,a5)*pow(7,a7);
        set<int> digits;
        while(cur > 0){
            digits.insert(cur%10);
            cur/=10;
        }
        //a2 - 1
        long long result = false;
        if(digits.find(2) != digits.end()){
            result |= canReduce(a2-1,a3,a5,a7);
        }
        //a3 - 1

        //a5 - 1

        //a7 -1
    }
    
    return false;
}
long long solve(const long long N){
    //các số thỏa mãn phải có dạng 1^a1*2^a2*... 9^a9
    //khởi tạo DP
    dp[0][0][0][0] = 1;
    long long res = 0;
    for(long long a7 = 0; pow(7,a7) <= N; ++a7){
        long long m5 =N/pow(7,a7);
        for(long long a5 = 0; pow(5,a5) <= m5; a5++){
            long long m3 = m5/ pow(5,a5);
                for(long long a3 = 0; pow(3,a3) <= m3; ++a3){
                    long long m2 = m3/pow(3,a3);
                    for(long long a2 = 0; pow(2,a2) <= m2; ++a2){
                        auto cur = pow(2,a2)*pow(3,a3)*pow(5,a5)*pow(7,a7);
                        // if(canReduce(cur) && check.find(cur)==check.end()){
                        //     cout<<cur<<endl;
                        // }
                        if(canReduce(a2,a3,a5,a7)){
                            ++res;
                        }
                    }
                }
        }
    }

    return res;
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

    long long N;
    cin>>N;
    
    auto res =solve(N);
    cout<<res;
	return 0;
}