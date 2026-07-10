/******************************************************************************
https://codejam.lge.com/problem/16201
Fun With Tiles Success
algo: modulo
algo: math
algo: mod_pow, mul_mod
xếp gạch vào lưới và số cách xếp
gạch size 1x2
lưới có 1 số ô không bị hỏng
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long R,C,K;
long long MOD = 1e9+7;
long long pow_mod(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}
long long mul_mod(long long a, long long b, long long mod)
{
    long long res = 0;

    while (b)
    {
        if (b & 1)
            res = (res + a) % mod;

        a = (a + a) % mod;
        b >>= 1;
    }

    return res;
}

pair<long long,long long> solve(map<long long,vector<long long>> &a)
{
    long long numTile = 0;
    long long numWays = 1;
    for(auto& [r,cols] : a){
        sort(cols.begin(), cols.end());
        long long s = 0;  
        cols.push_back(C);
        for(auto e : cols){
            long long si = e-s;
            numTile+=si/2;
            if(si>=2 && si%2!=0){
                // numWays*=(si/2+1);
                // numWays=(numWays+MOD)%MOD;
                numWays = (numWays * (si/2+1)) % MOD;
                
            }
            s=e+1;
        }
    }
    long long goodRow = R- a.size();
    // cout<<"num:"<<numTile<<endl;
    numTile+=(C/2)*goodRow;
    if(C%2!=0)
    {
        // while(goodRow > 0){
        //     numWays*=(C/2+1);
        //     numWays=(numWays+MOD)%MOD;
        //     goodRow--;
        // }
        auto goodNum = pow_mod(C/2+1,goodRow,MOD);
        numWays = mul_mod(numWays,goodNum,MOD);
    }
    return {numTile, numWays};
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> R>>C>>K;
    map<long long ,vector<long long>> gcells;
    long long r,c;
    for (int i = 0; i < K; ++i)
    {
        cin>>r>>c;
        gcells[r-1].push_back(c-1);
    }
    auto [a,b] = solve(gcells);
    cout<<a<<' '<<b;
    return 0;
}
