/******************************************************************************

https://www.acmicpc.net/problem/11440
algo:matrix
algo:fibo
algo:math

*******************************************************************************/
#include <stdio.h>
#include<iostream>
#include<bits/stdc++.h>

typedef long long ll;

using namespace std;
std::istream& operator>>(std::istream& is, __int128& t) {
    std::string s;
    is >> s; // Read the number as a string

    t = 0;
    bool neg = false;
    int startIndex = 0;
    if (!s.empty() && s[0] == '-') {
        neg = true;
        startIndex = 1;
    }

    for (int i = startIndex; i < s.length(); ++i) {
        t = t * 10 + (s[i] - '0');
    }

    if (neg) t = -t;
    return is;
}

vector<vector<ll>> T0;
//A size mxm
//B size mx1
vector<vector<ll>> MultipleMatrix(const vector<vector<ll>> & A,const vector<vector<ll>> & B,const ll& P){
    vector<vector<ll>> m(A.size(), vector<ll>(B[0].size(),0));
    for(int r = 0; r < m.size(); ++r){
        for(int c = 0; c < m[0].size(); ++c){
            for(int j = 0; j < A[0].size(); ++j){
                m[r][c] = (m[r][c]+(A[r][j]*B[j][c])%P) %P;
            }
        }
    }
    return m;
}
vector<vector<ll>> PowerMaxtrix( vector<vector<ll>> A, __int128 exp, ll& P){
    int K = A.size();
    vector<vector<ll>> Result(K, vector<ll>(K, 0));
    for(int i = 0; i < K; ++i) Result[i][i] = 1;
    
    while (exp > 0) {
        if (exp & 1) {
            Result = MultipleMatrix(Result, A, P);
        }
        A = MultipleMatrix(A, A, P);
        exp >>= 1; // exp = exp / 2
    }
    return Result;
}
long long solve(__int128 N, ll& P){
    //matrix size K = 2
    //1 1
    //1 0
    vector<vector<ll>> T(2, vector<long long>(2, 0));
    for(int i = 0; i < 2; i++){
        T[0][i] = 1;
    }
    for(int i = 1; i < 2; ++i){
        T[i][i-1] = 1;
    }
    vector<vector<ll>> A(2,vector<ll>(1));
    A[0][0]=1;
    A[0][1]=0;

    auto Tnp1mk = PowerMaxtrix(T, N, P);// 2 is size of matrix
    // for(auto r : Tnp1mk){
    //     for(auto c: r){
    //         cout<<c<<" ";
    //     }
    //     cout<<endl;
    // }
    auto fn = MultipleMatrix(Tnp1mk, A, P);
    // cout<<"fn:"<<fn[0][0]<<" "<<fn[1][0]<<endl;
    return (fn[0][0]* fn[1][0])%P;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll P = 10e8+7;
    __int128 N;
    cin>>N;
    cout<<solve(N, P);
    return 0;
}

