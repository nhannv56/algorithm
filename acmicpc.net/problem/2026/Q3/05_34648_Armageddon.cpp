/******************************************************************************
https://www.acmicpc.net/problem/34648
algo: math
algo: Fermat's Little Theorem (fermat nhỏ)
algo: greedy
algo: tối ưu tích khi a*b*c -> tiến gần đến a=b=c 
Suy ra tiến gần tăng 1
Chú ý tràn số khi nhân

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
    long long x=1, y=1, z=0;
    long long total = 1;
    // cout<<"n="<<n<<endl;
    if(1<=n)cout<<"0 ";
    if(2<=n)cout<<"1 ";
    for(long long k = 3; k <=n;++k){
        double dx = double(x+2)/x;
        double dy = double(y+2)/y;
        double dz = (double(p)/q);
        // cout<<"x:"<<x<<" dz:"<<dz<<endl;
        // cout<<x<<" "<<y<<" "<<z<<"|"<<cx<<' '<<cy<<' '<<cz<<endl;
        if(dx > dy && dx > dz){
            total= (total*(x+2))%MOD;
            total =(total*modpow(x,MOD-2))%MOD;
            ++x;
        }else{
            if(dy > dz){
                total= (total*(y+2))%MOD;
                total =(total*modpow(y,MOD-2))%MOD;
                ++y;
            }else{
                total= (((total*p)%MOD)*modpow(q,MOD-2))%MOD;
                ++z;
            }
        }
        cout<<total<<' ';
    }
	return 0;
}
