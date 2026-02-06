/******************************************************************************

https://www.acmicpc.net/problem/1797
Data Structures
Sorting
Prefix Sum
Set / Map
Set / Map By Hashing

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int N;
vector<pair<int,int>> data;
void solve(){
    int res = 0;
    //unordered_map<int,int> um; //count and pos
    int um[2000000] = {-1};
    memset(um,-1, sizeof(int)*2000000);
    int cur = 0;
    int pre =0;
    for(int i = 0; i < ::data.size(); ++i){
        ::data[i].second == 0 ? --cur : ++cur;
        //auto it = um.find(cur);
        pre = cur+1000000;
        if(um[pre] == -1){
            um[pre] = i;
        }else{
            int index = um[pre];
            res = max(res,::data[i].first - ::data[index+1].first);
        }
        if(i> 0 && cur == 0){
            res = max(res, ::data[i].first - ::data[0].first);
        }
    }
    cout<<res<<'\n';
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N;
    int t,p;
    for(int i = 0; i < N;i++){
        cin>>t>>p;
        ::data.push_back({p,t});
    }
    sort(::data.begin(),::data.end());
    solve();
    return 0;
}
