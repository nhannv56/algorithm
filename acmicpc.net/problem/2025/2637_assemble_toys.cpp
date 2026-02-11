/******************************************************************************

https://www.acmicpc.net/problem/2637

Dynamic Programming
Graph Theory
Directed Acyclic Graph
Topological Sorting

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;

int N,M;
int X,Y, K;

vector<vector<pair<int,int>>> form(101); // y,k
bool NoBase[101]={false,};
vector<map<int,int>> TBase(101);//toy index :base & count

map<int,int> cal(int x){ // base and count
    map<int,int> res;
    if(!NoBase[x]){//base
        res[x] = 1;
        return res;
    }
    if(TBase[x].empty()){
        for(auto [y, k] : form[x]){
            //cout<<"form:"<<x<<" part:"<<y<<" count:"<<k<<endl;
            auto childP = cal(y);
            for(auto [yy,kk] : childP){
                if(res.find(yy) == res.end()){
                    res[yy] = kk*k;
                }else{
                    res[yy] += kk*k;
                }
            }
        }
        for(auto it: res){
            //cout<<"res:"<<it.first<<" "<<it.second<<endl;
        }
        TBase[x]=res;
    }
    return TBase[x];
        
    
}
int main(){
    
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>N>>M;
	
	for(int i =0; i < M; i++){
	    cin>>X>>Y>>K;
	    NoBase[X] = true;
	    form[X].push_back({Y,K});
	}
	
	auto result = cal(N);
	for(auto [b, c]:result){
	    cout<<b<<' '<<c<<'\n';
	}
	return 0;
}