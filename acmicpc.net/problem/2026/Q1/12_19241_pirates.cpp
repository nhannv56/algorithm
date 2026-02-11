/******************************************************************************

https://www.acmicpc.net/problem/19241
algo:sort
algo:greedy
codejam sort, math

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int T,N;
int solve(int A[],int B[],int N){
    int AmB = 0;
    vector<pair<long long,int>> ab(N,{0,0});// store a-b and index
    for(int i = 0; i < N;++i){
        ab[i]= {(long long)(A[i]+B[i]),i};
    }
    sort(ab.begin(),ab.end(),std::greater<std::pair<long long, int>>());
    // for(int i = 0; i < N;++i){
    //     cout<<ab[i].first<<" "<<ab[i].second<<endl;
    // }
    long long sumA=0,sumB=0;
    for(int i = 0; i < N;i++){
        if(i%2==0){
            sumA+=A[ab[i].second];
        }else{
            sumB+=B[ab[i].second];
        }
        
    }
    return sumA-sumB;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>T;
    while(T > 0){
        cin>>N;
        int A[N]={0,},B[N];
        vector<int> cards(N);
        for(int i=0; i < N; i++){
            cin>>A[i]>>B[i];
        }
        cout<<solve(A,B,N)<<'\n';
        --T;
    }
	return 0;
}