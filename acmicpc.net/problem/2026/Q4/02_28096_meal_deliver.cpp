/******************************************************************************

https://www.acmicpc.net/problem/28096
bitmask dp traveling sale mans
algo: dp
algo: tsp

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int T,N,F,W,L;
int maxlen= 17*1000000;
struct POS{
    int z,x,y;
};
//khoảng cách từ vị trí i đến j trong pos

//có thể tính trước để tránh tính lại
int dis(int i, int j, vector<POS>& pos){
    int res = 0;
    int dzij = pos[i].z - pos[j].z;
    //đi xuống
    int zmove = 0;
    if(dzij >= 0){
        zmove+= dzij;
    }else{
        zmove+= abs(dzij)*2;
    }
    //1,1
    int op0=INT_MAX;
    if(dzij == 0){
        op0 = abs(pos[i].x-pos[j].x)+abs(pos[i].y-pos[j].y);
        return op0;
    }
    int op1 = abs(pos[i].x-1)+abs(pos[j].x-1) + abs(pos[i].y-1)+abs(pos[j].y-1);
    int op2 = abs(pos[i].x-W)+abs(pos[j].x-W) + abs(pos[i].y-1)+abs(pos[j].y-1);
    int op3 = abs(pos[i].x-1)+abs(pos[j].x-1) + abs(pos[i].y-L)+abs(pos[j].y-L);
    int op4 = abs(pos[i].x-W)+abs(pos[j].x-W) + abs(pos[i].y-L)+abs(pos[j].y-L);
    res=min({op0,op1,op2,op3,op4})+zmove;
    return res;
}
vector<vector<int>> dp = vector<vector<int>>(1<<16, vector<int>(16, -1));
int resolve(int mask, int u, vector<POS>& pos) {    
    //cout<<"mask:"<<std::bitset<8>(mask)<<" u:"<<u<<endl;
    if(dp[mask][u] != -1){
        return dp[mask][u];
    }
    // khoảng cách thành phố 0 -> u ->...
    if(mask == 1){
        return dis(0, u, pos);
    }
    int result  = maxlen;
    //mask &= ~(1<<u);
    //từ v -> u khác từ u->v
    //xét từ v-> u
    for(int v = 1; v < N; ++v){
        if((mask & (1<<v)) != 0 ){// in list and have way revert trace
            int nMask = (mask & ~(1<<v));
            // nMask &= ~(1<<u);
            result = min(result, resolve(nMask, v, pos) + dis(v,u,pos));
            //cout<<u<<" "<<v<<" mask:"<<std::bitset<8>(nMask)<<" cost:"<<result<<endl;
        }
    }
    //cout<<"u:"<<u<<" "<<result<<endl;
    dp[mask][u]=result;
    return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
    #endif
	cin>>T;
    while(T>0){
        cin>>F>>W>>L>>N;
        int result = INT_MAX;
        ++N;
        vector<POS> emp(N);
        for(int i = 0; i < N; ++i){
            cin>>emp[i].z>>emp[i].x>>emp[i].y;
        }
        int m = 1<<N;
        
        //cout<<"m:"<<std::bitset<8>(m)<<endl;
        //result cấu hình mask thiếu v nhỏ nhất đến v
        dp = vector<vector<int>>(1<<16, vector<int>(16, -1));
        for(int v = 1; v < N; ++v){
            // cout<<"last: "<<std::bitset<8>(m-1)<<" "<<v<<" " <<dp[m][v]<<endl;
            result = min(result, resolve((m-1)&~(1<<v), v, emp));
        }
        cout<<result<<'\n';
        --T;
    }
	return 0;
}
