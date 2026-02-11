/******************************************************************************

https://www.acmicpc.net/problem/13430
algo:matrix
algo:math

*******************************************************************************/
#include <stdio.h>
#include<iostream>
#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

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

long long solve(ll N,ll K, ll& P){
    if(K==0){
        return N%P;
    }
    //init matrix
    vector<vector<ll>> T(K+2, vector<long long>(K+2, 0));
    vector<vector<ll>> Sk1(K+2,vector<ll>(1,0)); //n=1
    for(int i = 0; i < Sk1.size(); i++){
        Sk1[i][0]=1;
        T[i][K+1]=1;
    }
    for(int i = 0; i < K+1; ++i){
        for(int j = 0; j <= i;++j){
            T[i][j] = 1;
        }
    }
    auto Tnmk = PowerMaxtrix(T, N-1, P);
    auto res = MultipleMatrix(Tnmk, Sk1, P);
    
    return res[K][0]%P;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll P = 10e8+7;
    ll N,K;
    cin>>K>>N;
    cout<<solve(N, K, P);
    return 0;
}

