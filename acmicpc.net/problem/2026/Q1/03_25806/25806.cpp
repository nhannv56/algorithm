/******************************************************************************

https://www.acmicpc.net/problem/25806
binary search

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;

int binary_search(int N, int K){
    if(N <= 2){
        return 1;
    }
    if(K==1){
        return N-1;
    }else{
        //chẵn thì 2 phần giống nhau 
        //lẻ thì check phần lớn hơn -> remain phần nhỏ hơn
        double sqrtN = sqrt(N);
        --K;
        return binary_search(int(sqrtN),K)+int(sqrtN);
    }
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
    int N, K;
    cin>>N>>K;
    if(K < ceil(log2(N))){
        cout<<binary_search(N,K);
    }else{
        cout<<ceil(log2(N));
    }
	return 0;
}
