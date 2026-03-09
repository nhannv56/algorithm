/******************************************************************************

https://www.acmicpc.net/problem/27362

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int N, K;
long long solve(int A[], int B[]){
    int res = 0;
    int AB[N];
    for(int i = 0; i < N; ++i){
        AB[i]=A[i]-B[i];
    }
    //special case Z[i,j] = |X(i,j)- Y(i.j))| = |Ai - Aj - Bi + Bj| = (Ai-Bi)-(Aj-Bj)
    //K = |a-b|
    if(K > 2e5){
        return 0;
    }
    vector<vector<int>> counts(2e5+1);
    for(int i = 0; i < N;++i){
        counts[AB[i]+1e5].push_back(i);
    }
    for(int i = 0; i < N; ++i){
        int a = AB[i];
        int b1 = a-K;
        int b2 = a+K;
        if(b1 >= -1e5 ){
            auto find = upper_bound(counts[b1+1e5].begin(), counts[b1+1e5].end(), i);
            if(find != counts[b1+1e5].end()){
                // cout<<"found:\n";
                res+= counts[b1+1e5].size()-distance(counts[b1+1e5].begin(),find);
            }
        }
        if(b2 >= -1e5 ){
            auto find = upper_bound(counts[b2+1e5].begin(), counts[b2+1e5].end(), i);
            if(b2 >= -1e5 &&find != counts[b2+1e5].end()){
                // cout<<"found:\n";
                res+= counts[b2+1e5].size()-distance(counts[b2+1e5].begin(),find);
            }
        }
    }
    return res == 0 ? -1 : res;
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
    int T = 0;
    cin>>T;
    while(T > 0){
        cin>>N>>K;
        int A[N], B[N];
        for(int i = 0; i < N;++i){
            cin>>A[i];
        }
        for(int i = 0; i < N;++i){
            cin>>B[i];
        }
        cout<<solve(A,B)<<'\n';
        --T;
    }
	return 0;
}
