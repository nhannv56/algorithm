/******************************************************************************
https://www.acmicpc.net/problem/24579
N*N

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
//p thời gian mở cửa mỗi ngày
//k số ngày mở cửa
//d số thời gian cần cho 1 người
vector<long long> dp(1e5,-1);
bool satify(int f,const vector<int> &d, int p, int k){
    
    return false;
}
long long solve(vector<long long>& d, long long p, long long k){
    long long n = d.size();
    vector<long long> prefix(2*d.size(),0);
    //double prefix sum
    //0 1 2 3 4 0 1 2 3 4
    //chỉ số 2n+i = i
    for(int i = 0; i < prefix.size();++i){
        prefix[i] = i > 0 ?prefix[i-1]:0 + d[(i%n)-1];
    }
    long long i = 0, c = 0, m =  0;//i là chỉ số bắt đầu
    long long t = p;// t là thời gian cần check
    if(t >= prefix[n] && t% prefix[n]==0){
        return ((long long)(t/prefix[n]))*k;
    }
    while( t >= d[0]){//điều kiện với c full cần m day
        if(t >= prefix[n-1]){
            c+= t/prefix[n-1];
            t%= prefix[n-1];
        }
        auto last = upper_bound(prefix.begin()+i, prefix.end(), t);
        --last;
        i = last - prefix.begin()-i;

        ++m;
    }
    
    return 0;
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
    int n,p,k;
    cin>>n>>p>>k;
    vector<int> d(n);
    for(int i = 0; i < n; ++i){
        cin>>d[i];
    }
    cout<<solve(d, p, k);
	return 0;
}
