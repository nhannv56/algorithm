/******************************************************************************
https://www.acmicpc.net/problem/27357

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long T, N;
pair<double, double> cal(double sum, double tax){
    double t1,t2;
    t1 = (sum*tax)/100;
    t2 = (sum*tax)/100;
    t1 = floor(t1*100)/100;
    t2 = ceil(t2*100)/100;
    return {t1+sum, t2+sum};
}
pair<long long, long long> solve(double sum,const double X){
    long long l = -1, r=-1;
    for(long long i = 0; i <= 1e4; ++i){
        auto [mi,ma] = cal(sum, i);
        if( (long long)mi == (long long)X || (long long)ma == (long long)X){
            // cout<<"solve:"<<i<<" mi:"<<mi<<" ma:"<<ma<<" x:"<<X<<endl;
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
    double X;
    // cout<<"ceil:"<<ceil(99.9)<<endl;
    while(T > 0){
        cin>>N>>X;
        double sum = 0;
        double x;
        for(long long i= 0; i < N; ++i){
            cin>>x;
            sum+=x;
        }
        auto [l, r] = solve(sum, X);
        cout<<l<<' '<<r<<'\n';
        --T;
    }
	return 0;
}
