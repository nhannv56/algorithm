/******************************************************************************

https://www.acmicpc.net/problem/27281
bfs, prirority queue, binary search, Dijkstra's

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

long long N,M,T;

long long result = -1;
//map<long long, long long> skills;//skill, count
struct Node{
    long long p,t,s;
};
bool bfs(long long inc,const vector<vector<Node>>& data){//inconvenience 
    priority_queue<pair<long long, long long>> pq;
    
    pq.push({T,1});
    
    long long visited[50001]={0,};
    visited[1] = T;
    long long nTime = 0;
    long long inQueue[50001]={0,};
    while(pq.size()>0){
        long long cTime, pos;
        tie(cTime, pos) = pq.top();pq.pop();
        inQueue[pos]=0;
        if(cTime < visited[pos]){
            continue;
        }
        if(pos == N){
            return true;
        }
        
        for(Node n : data[pos]){ 
            nTime = cTime - n.t;
            if(n.s > inc){
                nTime -= (n.s-inc);
            }
            if(visited[n.p] == 0 ){
                if(nTime >= 0){
                    visited[n.p] = nTime;
                    pq.push({nTime, n.p});
                }
            }else if(nTime > visited[n.p]){
                visited[n.p] = nTime;
                if(inQueue[n.p]==0){
                    pq.push({nTime,n.p});
                }
            }
        }
    }
    return false;
}
void binary_search(vector<vector<Node>>& data, long long sp, long long ep) {
    if(sp > ep){
        return;
    }
    long long mid=0;
    while(sp <= ep){
        mid = (sp+ep)/2;
        if(bfs(mid, data)){
            result = mid;
            ep = mid-1;
        }else{
            sp = mid+1;
        }
    }
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>N>>M>>T;
	vector<vector<Node>> data(N+1);
	long long u,v,t,s;
	long long maxS =0;
	for(int i = 0; i < M; i++){
	    cin>>u>>v>>t>>s;
	    data[u].push_back({v,t,s});
	    data[v].push_back({u,t,s});
	    maxS+=s;
	}
	binary_search(data, 0, maxS);
	cout<<result<<"\n";
	return 0;
}