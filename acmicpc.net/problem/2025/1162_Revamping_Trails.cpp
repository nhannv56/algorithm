/******************************************************************************

https://www.acmicpc.net/problem/1162
Dynamic Programming
Graph Theory
Shortest Path
Dijkstra's

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
long long N,M,K;

struct Node{
    long long len, pos, k;
};



struct CompareNode {
    bool operator()(const Node& x, const Node& y) const {
        return x.len > y.len; // min-heap theo a
    }
};

long long solve(vector<vector<Node>>& al){
    //vector<vector<long long>> dp(N, vector<long long>(K));
    vector<vector<long long>> visited(N, vector<long long>(21, LLONG_MAX));
    priority_queue<Node, vector<Node>, CompareNode> mq;
    
    mq.push({0, 0, K});// len, pos, K
    long long last = N-1;
    long long nextLen = 0;
    while(mq.size() > 0){
        auto [len, pos, k] = mq.top(); mq.pop();
        //cout<<"pos:"<<pos<<",len:"<<len<<",k:"<<k<<endl;
        if(pos == last){
            return len;
        }
        if(len >= visited[pos][k]){
            //cout<<"contine:"<<len<<" "<<visited[pos][k]<<endl;
            continue;
        }
        visited[pos][k] = len;
        for(auto [nlen, npos, nk]: al[pos]){
            //cout<<"next: pos:"<<npos<<",len:"<<nlen<<",k:"<<k<<endl;
           nextLen = len+nlen;
           if(k > 0){
               if(nextLen < visited[npos][k] ){// shorter
                   mq.push({nextLen, npos, k});
               }
               if(len < visited[npos][k-1] ){
                   mq.push({len, npos, k-1});
               }
           }else{
               mq.push({nextLen, npos, 0});
           }
        }
    }
    return 0;
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>N>>M>>K;
    long long p1, p2;
    long long t;
    
    vector<vector<Node>> al(N);
    for(int i = 0; i < M;++i){
        cin>>p1>>p2>>t;
        al[p1-1].push_back({t,p2-1,0});
        al[p2-1].push_back({t,p1-1,0});
    }
    // for(int i = 0; i < N;++i){
    //     cout<<"i:"<<i<<":";
    //     for(auto it : al[i])
    //         cout<<it.pos<<" ";
    //     cout<<endl;
    // }
    cout<<solve(al);
	return 0;
}