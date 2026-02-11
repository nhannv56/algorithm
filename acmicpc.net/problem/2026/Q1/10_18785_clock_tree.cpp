/******************************************************************************

https://www.acmicpc.net/problem/18785
algo:dfs
algo:tree
algo:greedy

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>

using namespace std;
int N,M,K;
vector<bool> visited(2501, false);
int Cycle = 12;
int cnt = 0;
int dfs(int s,const vector<int>& clocks,const vector<vector<int>> & al){
    
    //calculation near
    int ts = clocks[s];//time start
    int nextVisit = 0;
    for(auto n : al[s]){
        if(!visited[n]) {
            nextVisit++;
            visited[n] = true;
            auto tn = dfs(n,clocks, al);
            ts +=(12-tn)%12;
            ts%=12;
            // cout<<"ts:"<<s<<" "<<ts<<endl;
        }
    }
    
    return ts;
}
int solve(const vector<int>& clocks,const vector<vector<int>>& al){
    int res=0;
    for(int i = 1; i < clocks.size();++i){
        // cout<<"----start:"<<i<<endl;
        // cnt = 0;
        visited.assign(2501, false);
        visited[i] = true;
        auto cr = dfs(i, clocks, al);
        if( cr %12== 0 ||cr % 12==1){
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

	cin>>N;
	vector<int> clocks(N+1);
	vector<vector<int>>al(N+1);
	for(int i = 1; i <= N; ++i){
	    cin>>clocks[i];
	}
	int a,b;
	for(int i = 1; i < N; ++i){
	    cin>>a>>b;
	    al[a].push_back(b);
	    al[b].push_back(a);
	}
	cout<<solve(clocks,al);
	return 0;
}