/******************************************************************************
https://www.acmicpc.net/problem/27357

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long T, N;
pair<long long, long long> cal(long long sum, long long tax){
    long long t1,t2;
    t1 = (sum*tax);
    t2 = t1;
    t1/=100;
    if(t2 % 100 != 0){//round up
        t2 = t1+1;
    }else{
        t2=t1;
    }
    return {t1+sum, t2+sum};
}
pair<long long, long long> solve(long long sum,const long long X){
    long long l = -1, r=-1;
    for(long long i = 0; i <= 1e4; ++i){
        auto [mi,ma] = cal(sum, i);
        if( mi/100 == X || ma/100 == X){
            // cout<<i<<" sum:"<<sum<<" X:"<<X<<" mi:"<<mi<<" ma:"<<ma<<endl;
            if(l == -1){
                l = i;
                r = i;
            }else{
                r = i;
            }
        }
    }
    return {l,r};
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
    cin>>T;
    long long  X;
    // cout<<"ceil:"<<ceil(99.9)<<endl;
    while(T > 0){
        cin>>N>>X;
        long long sum = 0;
        double x;
        for(long long i= 0; i < N; ++i){
            cin>>x;
            sum+=round(x*100.0);
            // cout<<(long long)(x*100)<< " "<<sum<<endl;
        }
        auto [l, r] = solve(sum, X);
        cout<<l<<' '<<r<<'\n';
        --T;
    }
	return 0;
}
