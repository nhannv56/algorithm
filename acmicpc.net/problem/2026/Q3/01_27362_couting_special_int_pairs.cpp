/******************************************************************************

https://www.acmicpc.net/problem/27362
algo: binary search
algo: two pointer
algo: sort
dùng two pointer để tìm số cặp l, r
l với các cặp tới r
binary search để tìm thỏa mãn

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int N, K;
int countPair(vector<int> AB, int D){
    int count = 0;
    int r = 0;
    for(int l=0; l < N; ++l){
        while(r < N && AB[r]-AB[l]<=D){
            r++;
        }
        count+=(r-l-1);
    }
    return count;
}
long long solve(int A[], int B[]){
    int res = -1;
    vector<int> AB(N);
    // vector<int> Z(N,0);
    
    //special case Z[i,j] = |X(i,j)- Y(i.j))| = |Ai - Aj - Bi + Bj| = |(Ai-Bi)-(Aj-Bj)|
    //K = |a-b|
    // he uses $Z$ to define a function C: C(D) = | {(i, j) : Z(i, j) <= D } |. 
    for(int i = 0; i < N; ++i){
        AB[i]=A[i]-B[i];
    }
    sort(AB.begin(), AB.end());
    int l = 0;
    int r = AB[N-1] - AB[0];
    while(l <= r){
        int mid = l+(r-l)/2;
        int tmpCount = countPair(AB,mid);
        if( tmpCount >= K){
            if(tmpCount == K){
                res = mid;
            }
            r = mid-1;
        }else{
            l = mid+1;
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
