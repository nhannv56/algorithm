/***

https://www.acmicpc.net/problem/25334
algo: Fermat's Little Theorem
algo: ckn Combinatorics
algo: Prefix Sum
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
long long N, K;
using namespace std;
long long MOD = 1e9 + 7;
//precompute factorials and inverse factorials for C(n,k) mod MOD
static vector<long long> fact(1000001,1),invfact(1000001,1);

long long modpow( long long a,long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}
void buildFact(){
    for(long long i = 1; i <= 1000000; ++i){
        fact[i] = fact[i-1] * i % MOD;
    }
    invfact[1000000] = modpow(fact[1000000], MOD-2);
    for (long long i = 999999; i >= 0; --i) {
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }
}

//ckn tổ hợp
long long Cmod(const long long& n,const long long& k) {
    auto res =  fact[n] * invfact[k] % MOD * invfact[n-k] % MOD;
    //cout<<"ckn"<<n<<" "<<k<< "="<<res<<endl;
    return res;
}

void solve(const string &cake)
{
    int toppingCount = 0;
    for (int i = 0; i < N; i++)
    {
        if (cake[i] == '1')
        {
            ++toppingCount;
        }
    }
    if(K==1){
        cout<<"1\n";
        return;
    }
    //ko có topping nào thì chỉ cần chọn K-1 vị trí chia bánh trong N-1 vị trí giữa các miếng bánh
    if(toppingCount ==0){
        cout<<Cmod(N-1,K-1)<<endl;
        return;
    }
    long long toppingPiece = toppingCount / K;
    long long res = 0;
    // số toping có thể chia đều
    // cout<<"T K p:"<<toppingCount<<" "<<K<<" "<<toppingPiece<<endl;
    if (toppingPiece * K == toppingCount)
    {
        res = 1;
        long long cTop = 0;
        long long cNoTop = 0;
        for (int i = 0; i < N; ++i)
        {
            if (cake[i] == '1')
            {
                if(cTop == toppingPiece){
                    res *= (cNoTop + 1);
                    res %= MOD;
                    cTop=1;
                    cNoTop=0;
                }else{
                    ++cTop;
                }
            }
            else if(cTop == toppingPiece)
            {
                cNoTop++;    
            }
            
        }
    }
    cout << res << '\n';
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
    int T;
    cin >> T;
    buildFact();
    while (T--)
    {
        cin >> N >> K;
        string cake;
        cin >> cake;
        solve(cake);
    }
    return 0;
}
