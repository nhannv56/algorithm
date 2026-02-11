/******************************************************************************

https://www.acmicpc.net/problem/28094
Implementation
Bruteforcing
backtrack

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int T,N,M;


pair<int,int> backtrack(vector<vector<int>> & S, int pos, vector<bool>& visited) {    
    pair<int,int> result = {0,0};
    // int firstNum = 0;
    if(pos == N){
        return {0,1};
    }
    for(int i = 0; i < visited.size();++i){
        if(!visited[i]){
            int curRes = 0;
            for(int j = 0; j < visited.size(); j++){
                if(visited[j]){
                    curRes+=S[j][i];
                }
            }
            visited[i] = true;
            auto  nRes = backtrack(S, pos+1, visited);
            //cout<<"pos:"<<pos<<" i:"<<i<<" res:"<<nRes.first + curRes<<endl;
            if(nRes.first + curRes > result.first){
                result.first   = nRes.first+curRes;
                result.second = nRes.second;
            }else if(nRes.first + curRes == result.first){
                result.first   = nRes.first+curRes;
                result.second += nRes.second;
            }
            visited[i] = false;
        }
    }
    return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>T;
    
    for(int t = 0; t < T; t++){
        cin>>N>>M;
        vector<int> V = vector<int>(M),
                    A = vector<int>(M),
                    B = vector<int>(M);
        vector<vector<int>> S = vector<vector<int>>(N, vector<int>(N, 0));
        vector<bool>visited = vector<bool>(N, false);
        for(int i = 0; i < M;i++){
            cin>>V[i]>>A[i]>>B[i];
            --A[i];
            --B[i];
            S[A[i]][B[i]] +=V[i];
        }
        auto fn = backtrack(S, 0, visited);
        cout<<fn.first <<" "<<fn.second<<'\n';
    }
	return 0;
}