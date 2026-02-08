/******************************************************************************

https://www.acmicpc.net/problem/1800
Graph Theory
Binary Search
Shortest Path
Dijkstra's
Parametric Search

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
struct Node{
    int p;
    long long l;
};

int N,P,K;
vector<vector<pair<int,int>>> cables(1001);
vector<int> lengths;
int maxL = 0;
int visited[1001], cnt = 0 ;
bool check(int len){
    //cout<<"check:"<<len<<endl;
    deque<pair<int,int>> queue;
    queue.push_back({1, 0});
    ++cnt;
    //memset(visited, false, 1001*sizeof(bool));
    //visited[1] = true;
    while(!queue.empty()){
        auto [pos,count] = queue.front();queue.pop_front();
        
        if(pos == N) { //with len -> can go to N
            return count <= K;
        }
        visited[pos] = cnt;
        for(int i = 0; i < cables[pos].size();++i){
            if(visited[cables[pos][i].first] != cnt){
                if(cables[pos][i].second > len){
                    //if(count < K){
                        queue.push_back({cables[pos][i].first,count+1});
                        //visited[cables[pos][i].p] = true;
                        
                    //}else{
                        //ignore do not satify
                    //}
                }else{
                    queue.push_front({cables[pos][i].first,count});
                    
                    //visited[cables[pos][i].p] = true;
                }
            }
        }
    }
    
    return false;   
}

void solve(){
    int left = 0;
    int right = maxL;
    int result = -1;
    while(left <= right){
        int mid = (left + right)/2;
        if(check(mid)){
            result = mid;
            right = mid-1;    
        }else{
            left = mid+1;
        }
    }
    cout<<result<<'\n';
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N>>P>>K;
    //Node cur;
    int a,b,l;
    //lengths.push_back(0);
    
    for(int i = 0; i < P; ++i){
        cin>>a>>b>>l;
        cables[a].push_back({b,l});
        cables[b].push_back({a,l});
        maxL = max(l, maxL);
        //lengths.push_back(l);
    }
    //length unique
    //sort(lengths.begin(),lengths.end());
    //auto it = std::unique(lengths.begin(), lengths.end());
    //lengths.erase(it, lengths.end());
    
    solve();
    
    return 0;
}
