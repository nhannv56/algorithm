/******************************************************************************

https://www.acmicpc.net/problem/34490


*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
bool canReduce(long long N){
    if(N==1){
        return true;
    }
    std::vector<int> digits;
    long long dN = N;
    while(dN > 0){
        digits.push_back(dN%10);
        dN/=10;
    }
    for(auto d : digits){
        if(d != 0 && d != 1){
            if(N % d == 0 && canReduce(N/d)){
                return true;
            }
        }
    }
    return false;
}
long long solve(long long N){
    long long res = 0;//các số thỏa mãn điều kiên
    long long count = 0;//các số đã duyệt
    long long cur = 1;
    for(int i = 1; i <=N; ++i){
        if(canReduce(i)){
            ++res;
        }
    }
    return res;
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

    long long N;
    cin>>N;
    
    auto res =solve(N);
    cout<<res;
	return 0;
}