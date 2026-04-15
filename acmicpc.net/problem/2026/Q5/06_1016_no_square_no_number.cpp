/***
https://www.acmicpc.net/problem/1016

**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
#endif
    long long mi,ma;
    cin>>mi>>ma;
    long long maxNum = sqrt(ma);
    long long sNum = 0;
    for(long long num = mi; num <= ma; ++num){
        for(int d =2; d <= maxNum;++d){
            if(num %(d*d)== 0){
                sNum++;
                break;
            }
        }
    }
    cout<<ma-mi+1-sNum;
    return 0;
}
