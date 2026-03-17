/******************************************************************************
https://www.acmicpc.net/problem/34648

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long N;

long long MOD = 1e9+7;
long long modpow( long long a,long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
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
    long long p,q,n;
    cin>>p>>q>>n;
    long long x=0, y=0, z=0, mz=1, mx=0,my=0,mz=1;
    long long total = 0;
    for(long long k = 1; k <=n;++k){
        long long cx = (x+1)*(x+2);
        long long cy = (y+1)*(y+2);
        long long cz = mz*p*modpow(q,MOD-2);
        
    }
	return 0;
}
