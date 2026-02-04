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
                while(!dq.empty()){
                    auto [x,y] = dq.front();dq.pop_front();
                    //cout<<x<< " "<<y<<" "<<raw[x][y]<<" label:"<<label<<endl;
                    data[x/2][y/2] = label;
                    //travel next
                    int nx = x+1, ny=y+1;
                    if(x+1 < raw.size()){
                        if(raw[nx][y] == '.'|| raw[nx][y] == 'B'){
                            dq.push_back({nx,y});
                        }
                    }
                    if(y+1 < raw[0].size()){
                        if(raw[x][ny] == '.'|| raw[x][ny] == 'B'){
                            dq.push_back({x,ny});
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
