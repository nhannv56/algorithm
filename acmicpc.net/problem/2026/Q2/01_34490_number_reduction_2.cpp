/******************************************************************************

https://www.acmicpc.net/problem/34490
algo:dp
algo:math

Bài toán tìm các số đến N mà số đó đệ quy có thể giảm về 1 bằng cách chia cho các chữ số khác 0 và 1 của nó. 
Số đó phải có dạng 2^a2*3^a3*5^a5*7^a7. 
Ta sẽ dùng DP để lưu trữ kết quả của việc có thể giảm được số có dạng 2^a2*3^a3*5^a5*7^a7 về 1 hay không. 
Kết quả cuối cùng sẽ là tổng số các bộ (a2,a3,a5,a7) thỏa mãn điều kiện trên.

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
//dp[a2][a3][a5][a7] lưu trữ kết quả của việc có thể giảm được số có dạng 2^a2*3^a3*5^a5*7^a7 về 1 hay không
vector<vector<vector<vector<int>>>> dp(61, vector<vector<vector<int>>>(61,vector<vector<int>>(61,vector<int>(61,-1))));
//lưu trữ các lũy thừa của 2,3,5,7 để tránh phải tính lại nhiều lần
long long p2[62], p3[40],p5[28],p7[24];
bool canReduce(const long long& a2, const long long& a3, const long long& a5, const long long& a7){
    long long result = false;

    if(dp[a2][a3][a5][a7] != -1){
        return dp[a2][a3][a5][a7]==1;
    }else{
        long long cur = p2[a2]*p3[a3]*p5[a5]*p7[a7];
        set<int> digits;
        while(digits.size()<9 && cur > 0){
            auto d = cur%10;
            if(d != 0 && d!=1)
                digits.insert(d);
            cur/=10;
        }
        if(digits.find(2) != digits.end() && a2 >= 1){
            result |= canReduce(a2-1,a3,a5,a7);
        }
        if(digits.find(3) != digits.end() && a3 >= 1){
            result |= canReduce(a2,a3-1,a5,a7);
        }
        if(digits.find(4) != digits.end() && a2 >= 2){
            result |= canReduce(a2-2,a3,a5,a7);
        }
        if(digits.find(5) != digits.end() && a5 >= 1){
            result |= canReduce(a2,a3,a5-1,a7);
        }
        if(digits.find(6) != digits.end() && a2 >= 1 && a3 >= 1){
            result |= canReduce(a2-1,a3-1,a5,a7);
        }
        if(digits.find(7) != digits.end() && a7 >= 1){
            result |= canReduce(a2,a3,a5,a7-1);
        }
        if(digits.find(8) != digits.end() && a2 >= 3){
            result |= canReduce(a2-3,a3,a5,a7);
        }
        if(digits.find(9) != digits.end() && a3 >= 2){
            result |= canReduce(a2,a3-2,a5,a7);
        }
    }
    dp[a2][a3][a5][a7] = result?1:0;
    return result;
}
long long solve(const long long N){
    //các số thỏa mãn phải có dạng 1^a1*2^a2*... 9^a9
    //khởi tạo DP
    dp[0][0][0][0] = 1;
    long long res = 0;
    p2[0] = 1;
    p3[0] = 1;
    p5[0] = 1;
    p7[0] = 1;
    for(int i = 1; i < 62; ++i){
        p2[i] = p2[i-1]*2;
    }
    for(int i = 1; i < 40; ++i){
        p3[i] = p3[i-1]*3;
    }
    for(int i = 1; i < 28; ++i){
        p5[i] = p5[i-1]*5;
    }
    for(int i = 1; i < 24; ++i){
        p7[i] = p7[i-1]*7;
    }
    for(long long a7 = 0; p7[a7] <= N; ++a7){
        long long m5 = N/p7[a7];
        for(long long a5 = 0; p5[a5] <= m5; ++a5){
            long long m3 = m5/ p5[a5];
            for(long long a3 = 0; p3[a3] <= m3; ++a3){
                long long m2 = m3/p3[a3];
                for(long long a2 = 0; p2[a2] <= m2; ++a2){
                    if(canReduce(a2,a3,a5,a7)==1){
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
