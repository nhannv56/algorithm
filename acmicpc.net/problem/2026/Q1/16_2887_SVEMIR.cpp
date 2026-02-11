/******************************************************************************

https://www.acmicpc.net/problem/2887
sử dụng thuật toán prime trong không gian
algo:Minimum Spanning Tree
algo:prime
algo:graph

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
int N;
vector<unordered_map<int, int>> O(3); //real possition to compressed O0 =Ox, O1 = Oy, O2 = Oz
vector<bool> visited(100000, false);
// tọa độ chưa visit
pair<int,int> nextNotVisit(int pos, int o, vector<vector<pair<long long, long long>>>& Oxyz){
    int l=-1,r=-1;
    // cout<<"nextNotVisit:"<<pos<<endl;
    // for(int i = 0; i < N; i++){
    //     cout<<visited[i]<<" ";
    // }cout<<endl;
    for(int i = pos-1; i >=0;--i){
        //origiginal compress
        auto cPos = Oxyz[o][i].second;
        if(!visited[cPos]){
            l=i;break;
        }
    }
    
    for(int i = pos+1; i < N; ++i){
        auto cPos = Oxyz[o][i].second;
        // cout<<"cpos:"<<cPos<<endl;
        if(!visited[cPos]){
            r=i;break;
        }
    }
    return {l,r};
}

int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>N;
    vector<vector<long long>> p(N,vector<long long>(3,0));//postion x,y,z
    vector<vector<pair<long long, long long>>> Oxyz(3, vector<pair<long long, long long>>(N, {0,0}));//sort by Oxyz
    for(int i = 0; i < N; ++i){
        cin>>p[i][0]>>p[i][1]>>p[i][2];
        Oxyz[0][i] = {p[i][0],i};//x
        Oxyz[1][i] = {p[i][1],i};//y
        Oxyz[2][i] = {p[i][2],i};//z
    }
    sort(Oxyz[0].begin(), Oxyz[0].end());// tọa độ đã nén theo trục -> tọa độ nén
    sort(Oxyz[1].begin(), Oxyz[1].end());
    sort(Oxyz[2].begin(), Oxyz[2].end());
    for(int i = 0; i < N; ++i){//tọa độ nén -> tọa đọ theo trục đã nén
        O[0][Oxyz[0][i].second] = i;//
        O[1][Oxyz[1][i].second] = i;//
        O[2][Oxyz[2][i].second] = i;//
    }
    // for(auto [pos, label] : Oxyz[1]){
    //     cout<<pos<<" "<<label<<endl;
    // }
    
    int count = 0;
    long long res = 0;
    //long long cost = 0;
    std::priority_queue<
    std::pair<long long, long long>,                // Data type
    std::vector<std::pair<long long, long long>>,   // Container type
    std::greater<std::pair<long long, long long>>   // Comparator (greater makes it a min heap)
    > pq; //store distance and next position
    pq.push({0,0});
    while(!pq.empty()){
        auto [len, pos] = pq.top(); pq.pop();
        if(visited[pos]){
            continue;
        }
        visited[pos] = true;
        //cout<<"check---------------:pos"<<pos<<" len:"<<len<<endl;
        count++;
        res+=len;
        if(count == N){
            cout<<res;
            break;
        }
        //Ox duyệt theo trục
        for(int o = 0; o < 3; ++o){// duyệt trục
            auto oPos = O[o][pos];//tọa độ nén theo trục
            auto [l,r] = nextNotVisit(oPos, o, Oxyz);// theo trục
            // cout<<"o:"<<o<<" oPos:"<<oPos<<" lr:"<<l<<" "<<r<<endl;
            if(l != -1){
                // auto oN = getPos(l,o,p);
                auto nlen = abs(Oxyz[o][oPos].first- Oxyz[o][l].first);
                pq.push({nlen,Oxyz[o][l].second});
                //  cout<<"push l:"<<len<<"+("<<Oxyz[o][oPos].first<<" - "<<Oxyz[o][r].first<<") "<<Oxyz[o][r].second<<endl;
                // cout<<"o:"<<o<<" "<<"oPos:"<<oPos<<" oN:"<<oN<<endl;
                
            }
            if(r != -1){
                // auto oN = getPos(r,o,p);
                auto nlen = abs(Oxyz[o][oPos].first- Oxyz[o][r].first);
                pq.push({nlen,Oxyz[o][r].second});
                // cout<<"push r:"<<len<<"+("<<Oxyz[o][oPos].first<<" - "<<Oxyz[o][r].first<<") "<<Oxyz[o][r].second<<endl;
                // cout<<"o:"<<o<<" "<<"oPos:"<<oPos<<" oN"<<oN<<endl;
            }
        }
        
    }
	return 0;
}