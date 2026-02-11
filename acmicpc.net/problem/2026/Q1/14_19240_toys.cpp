/******************************************************************************

https://www.acmicpc.net/problem/19240
algo:dfs
algo:Bipartite Graph(đồ thị 2 phía)

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
int T,N,M;

bool solve(vector<vector<int>>& aj){
    vector<vector<bool>> gr(2,vector<bool>(N+1,false));
    deque<pair<int,int>> dq;
    int count=0;
    for(int i = 1; i <=N;++i){
        if(count == N){//terminate corner case soon
            return true;
        }
        if(!gr[0][i] &&!gr[1][i]){
            dq.push_back({i, 0});
            while(!dq.empty()){
                auto [cur, grI] = dq.front(); dq.pop_front();
                // cout<<"g:"<<grI<<" "<<cur<<endl;
                if(!gr[0][cur] && !gr[1][cur]){// item not in any group, choose 1
                    gr[grI][cur] = true;
                    ++count;
                    grI = (grI+1)%2;
                    for(auto n : aj[cur]){//thăm điểm chưa thăm
                        if(!gr[0][n] && !gr[1][n]){
                            dq.push_back({n, grI});
                        }
                    }
                }else{
                    //nằm sai group -> không thể thỏa mãn
                    if(gr[(grI+1)%2][cur]){// cannot in correct group;
                        return false;
                    }
                }
            }
            
        }
    }
    return true;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>T;
    while(T>0){
        cin>>N>>M;
        vector<vector<int>> unfriend(N+1);
        int a,b;
        for(int i = 0; i < M;++i){
            cin>>a>>b;
            unfriend[a].push_back(b);
            unfriend[b].push_back(a);
        }
        auto res = solve(unfriend)?"YES":"NO";
        cout<<res<<'\n';
        --T;
    }
	return 0;
}