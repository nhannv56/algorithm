/******************************************************************************

https://www.acmicpc.net/problem/5719
djkstra, traceback, graph

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int N=-1,M=-1;
int S,D;
int u,v,l;
bool blocked[500][500];
void bfs(int s, int end, vector<vector<int>> & tb, vector<vector<pair<int,int>>> & vetexs){
    // reset blocked chỉ theo N hiện tại
    // for (int i = 0; i < N; ++i) {
        memset(blocked, 0, 500*500 * sizeof(bool));
    // }
    // cout<<"traceBack:start"<<endl;
    deque<int> dq;
    vector<int> insited(N, false);
    dq.push_back(end);
    while(dq.size()>0){
        int cur = dq.front(); dq.pop_front();
        if(cur == s){
            continue;
        }
        for(auto pr : tb[cur]){
            //cout<<"pr:"<<pr.first<<" "<<cur<<endl;
            // for (auto it = vetexs[pr].begin(); it != vetexs[pr].end();)
            // {
            //     if (it->first == cur ){
                    blocked[pr][cur] = true;
                    // it = vetexs[pr].erase(it);
                    //cout<<"erase:"<<pr.first<<" "<<cur<<endl;
                    if(insited[pr] == false){
                        insited[pr] = true;
                        dq.push_back(pr);
                    }
                // }
                // ++it;
            // }
            
        }
        
    }
    // cout<<"traceBack:end"<<endl;
}
void dijkstra(const int& s,const int& e, vector<vector<pair<int,int>>> & vetexs){
    
    
    vector<int> dist = vector<int>(N, INT_MAX);
    //cout<<"N:"<<dist[0]<<endl;
    vector<vector<int>> minEdges = vector<vector<int>>(N);

    priority_queue<std::pair<int, int>, 
                    std::vector<std::pair<int, int>>, 
                    std::greater<std::pair<int, int>>> pq;
    pq.push({0,s});
    int minLen = INT_MAX;
    dist[s]=0;
    while(pq.size() > 0){
        auto [len, pos] = pq.top();pq.pop();
        //cout<<"cmp:"<<pos<<" "<<len<<" "<<dist[pos]<<endl;
        if(len > dist[pos]){
            continue;
        }
        if(pos == e){
            //cout<<"min:"<<dist[pos]<<endl;
            if(dist[pos] < len){
                break;
            }
        }
        for(auto [nextPos, ndis] : vetexs[pos]){
            int nextLen = len+ ndis;
            if(dist[nextPos] > nextLen){// update shorter path
                dist[nextPos] = nextLen;
                minEdges[nextPos].clear();
                minEdges[nextPos].push_back(pos);
                pq.push({nextLen, nextPos});
                //cout<<"push1:"<<pos<<" "<<nextPos<<" len:"<<nextLen<< endl;
            }else if(dist[nextPos] == nextLen){//same len path
                minEdges[nextPos].push_back(pos);
                //pq.push({nextLen, nextPos});
                //cout<<"push2:"<<pos<<" "<<nextPos<<" len:"<<nextLen<< endl;
            }
        }
    }
    bfs(s, e, minEdges, vetexs);
}
int dijkstra2(int s, int e, vector<vector<pair<int,int>>> & vetexs){
   // cout<<"bfs2:"<<s<<" "<<e<<endl;
    priority_queue<std::pair<int, int>, 
                    std::vector<std::pair<int, int>>, 
                    std::greater<std::pair<int, int>>> pq;
    vector<int> dist = vector<int>(N, INT_MAX);
    pq.push({0,s});
    dist[s]=0;
    while(pq.size()> 0){
        auto [len, pos] = pq.top(); pq.pop();
        //cout<<"dj2:"<<pos<<endl;
        if(len > dist[pos]){
            continue;
        }
        if(pos == e ){
            return len;
        }
        for(auto [np, nd] : vetexs[pos]){
            //cout<<"np:"<<np<<endl;
            if(dist[np] > len+nd && !blocked[pos][np]){
                dist[np] = nd+len;
                pq.push({dist[np],np});
            }
        }
    }
    return -1;
}
void resolve(int s, int d, vector<vector<pair<int,int>>> & vetexs) {    
    
    dijkstra(s, d,vetexs);
    cout<<dijkstra2(s,d,vetexs)<<'\n';
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while( true){
	    cin>>N>>M;
	    cin>>S>>D;
	    if(N==0 && M==0){
	        break;
	    }

	    vector<vector<pair<int,int>>> vetexs = vector<vector<pair<int,int>>>(N);
	    for(int i = 0; i < M; ++i){
	        cin>>u>>v>>l;
	        vetexs[u].push_back({v,l});
	    }
	    resolve(S,D,vetexs);
	}
	
	return 0;
}