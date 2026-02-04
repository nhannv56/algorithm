/******************************************************************************

https://www.acmicpc.net/problem/12793
bfs, foodfill

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
int N,M;
void floodfill(const vector<string>& raw, vector<vector<int>> &data){
    int label = 0;
    for(int i = 1; i < raw.size(); i+=2){
        // cout<<raw[i]<<endl;
        for(int j = 1; j < raw[i].length(); j+=2){
            // cout<<raw[i][j]<<" ";
            if(raw[i][j]=='B' && data[i/2][j/2] == -1){
                deque<pair<int,int>> dq;
                dq.push_back({i,j});
                label++;
                //cout<<"start\n";
                set<pair<int,int>> visited;
                while(!dq.empty()){
                    auto [x,y] = dq.front();dq.pop_front();
                    //cout<<x<< " "<<y<<" "<<raw[x][y]<<" label:"<<label<<endl;
                    data[x/2][y/2] = label;
                    //travel next
                    int mv[2][4]={{0,0,1,-1},{-1,1,0,0}};
                    visited.insert({x,y});
                    for(int m = 0; m < 4; ++m){
                        int nx = x+mv[0][m];
                        int ny = y+mv[1][m];
                        if(nx>=0 && nx < data.size() && ny >=0 && ny <data[0].size()&&
                        raw[nx][ny] == '.'|| raw[nx][ny] == 'B'&&visited.find({nx,ny}) == visited.end()){
                            dq.push_back({nx,ny});
                        }
                    }                   
                }
            }else if(raw[i][j]== 'O'){
                data[i/2][j/2]=0;
            }
        }//cout<<endl;
    }
}
int solve(vector<vector<int>>& data, float k){
    int res = 0;
    //x0 < min(R,C);
    float minRC = min(data.size(), data[0].size());
    float x0,x1;
    set<int> collected;
    float y = 0;
    if(k != minRC){//x0+x1=2minRC
        x1 = k;
        x0 = minRC*2-x1;
        //first line y = -x + x0
        //2nd line y = -x + x0 
        //3th line y = x + x1
        for(auto x = x0; x > 0; x-=0.5){
            y = -x + x0;
            if(y >= data.size()){
                break;
            }
            int i = data.size()-1- floor(y);
            auto label = data[i][ceil(x)];
            if(label != 0){
                // cout<<"insert:"<<i<<" "<<ceil(x)<<" "<<label<<endl;
                collected.insert(label);
            }
        }
        
        for(auto x = x1; x > 0; x-=0.5){
            y = -x + x1;
            if(y >= data.size()){
                break;
            }
            int i = data.size()-1- floor(y);
            auto label = data[i][ceil(x)];
            if(label != 0){
                // cout<<"insert:"<<i<<" "<<ceil(x)<<" "<<label<<endl;
                collected.insert(label);
            }
        }
        for(float x = 0; x < minRC; x+=0.5){
            y = x + min(x0, x1);
            if(y >= data.size()){
                break;
            }
            int i= data.size()-1- ceil(y-0.5);
            auto label = data[i][ceil(x+0.5)];
            if(label != 0){
                // cout<<"insert:"<<i<<" "<<ceil(x+0.5)<<" "<<label<<endl;
                collected.insert(label);
            }
        }
    }else{//only 1 line
        for(auto x = k; x > 0; x-=0.5){
            y = -x + k;
            if(y >= data.size()){
                break;
            }
            int i = data.size()-1- floor(y);
            auto label = data[i][ceil(x)];
            if(label != 0){
                // cout<<"insert:"<<i<<" "<<ceil(x)<<" "<<label<<endl;
                collected.insert(label);
            }
        }
    }
    
    return collected.size();
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
    float K;
    cin>>N>>M>>K;
    vector<vector<int>> data(M,vector<int>(N,-1));//labeling 
    vector<string> raw(2*M+1);
    for(int i = 0; i < raw.size();++i){
        cin>>raw[i];
    }
    // for(int i = 0; i < raw.size();++i){
    //     cout<<raw[i]<<endl;
    // }
    floodfill(raw,data);
    // for(auto r : data){
    //     for(auto c : r){
    //         cout<<c<<" ";
    //     }cout<<endl;
    // }
    cout<<solve(data, K);
	return 0;
}
