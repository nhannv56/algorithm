/******************************************************************************

https://www.acmicpc.net/problem/13141
algo:bfs
algo:Shortest Path
algo:Floyd–warshall

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
long long N,M;


//chải time ra từ 0 -> 200*100
//lưu vào vector 2 chiều, time và danh sách  casd điểm kế tiếp
//tại 1 điểm check time -> nếu đã visit -> tính time, nếu chưa visit -> add vào next time
float bfs(int s,vector<vector<pair<int,int>>>& al){
    float res = 0;
    vector<int> visited(N*100, -1);
    vector<vector<int>> timing(N*100+1);//store distance and next position to check
    int cur = s;
    timing[0].push_back(s);
    for(int t = 0 ; t < timing.size(); ++t){
        for(auto node : timing[t]){// at time d d have node f to fire in same time
           if(visited[node] == -1) {
               res = max((float)t,res);
               visited[node] = t;
               for(auto [np, nl] : al[node]){
                  if(visited[np] == -1){
                       timing[t+nl].push_back(np);
                  }else{
                       if(t < visited[np]+nl){
                           float edgeFireTime = (float)t+((float)(visited[np] + nl - t))/2.0;
                           res = max(res,edgeFireTime);
                       }
                  }
               }
           }
        }
    }
    return res;
}
float solve(int N, vector<vector<pair<int,int>>>& al){
    vector<int> distanceF(N+1,INT_MAX);//store min distance from s to i
    float res = N*100;
    
    for(int i = 1; i <= N; ++i){
        
        float cur = bfs(i,al);
        res = min(cur, res);
        // cout<<"solve:"<<i<<" "<<std::fixed << std::setprecision(1)<<res<<endl;
    }
    return res;
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>N>>M;
    vector<vector<pair<int,int>>> al(N+1); //đỉnh kề
    int s,e,l;
    for(int i = 0; i < M; ++i){
        cin>>s>>e>>l;
        al[s].push_back({e,l});
        al[e].push_back({s,l});
    }
    cout<<std::fixed << std::setprecision(1)<<solve(N, al);
	return 0;
}