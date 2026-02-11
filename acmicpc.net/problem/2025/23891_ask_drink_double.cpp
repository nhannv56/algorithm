/******************************************************************************

https://www.acmicpc.net/problem/23819
algo:matrix

*******************************************************************************/
#include <stdio.h>
#include<iostream>
#include<bits/stdc++.h>

typedef long long ll;

using namespace std;
vector<vector<ll>> T0;
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
vector<vector<ll>> PowerMaxtrix( vector<vector<ll>> A, ll exp, ll& P){
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
long long solve(ll N, ll K, vector<vector<ll>>& A, ll& P){
    
    if(N <= K){
        return A[N-1][0];
    }
    vector<vector<ll>> T(K, vector<long long>(K, 0));
    for(int i = 0; i < K; i++){
        T[0][i] = 1;
    }
    for(int i = 1; i < K; ++i){
        T[i][i-1] = 1;
    }
    
    auto Tnmk = PowerMaxtrix(T, N-K, P);
    auto res = MultipleMatrix(Tnmk, A, P);
    return res[0][0];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll N, K, P = 10e8+7;
    
    
    cin>>N>>K;
    vector<vector<ll>> A(K, vector<ll>(1));
    for(int i = K-1; i >=0 ;i--){
        cin>>A[i][0];
    }
    cin>>P;
    cout<<solve(N, K, A, P);
    return 0;
}

