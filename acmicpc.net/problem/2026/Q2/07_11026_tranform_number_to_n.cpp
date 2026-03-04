/******************************************************************************
https://www.acmicpc.net/problem/11026
N*N

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
vector<int> comutation(1e6,-1);
int solve(int N){
    int res=N;
    int k = N/2;
    if(N==1){
        return 0;
    }
    if(comutation[N]!=-1){
        return comutation[N];
    }
    for (int k = N - 1; k >= 1; --k) {
        int a = N, b = k;
        //  cout<<"a:"<<a<<" b:"<<b<<endl;
        if(a/b > res){
            break;
        }
        int steps=0;
        while(b > 0) {
            // cout<<"b::"<<b<<endl;
            steps+=a/b;
            a=a%b;
            swap(a,b);
            if(steps >= res){
                break;
            }
        }
        // cout<<" s:"<<steps<<endl;
        if(a==1){
            res = min(res, steps-1);
        }        
    }
    comutation[N]=res;
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
    int T, N;
    cin>>T;
    while(T > 0){
        cin>>N;
        cout<<solve(N)<<'\n';
        --T;
    }
	return 0;
}
