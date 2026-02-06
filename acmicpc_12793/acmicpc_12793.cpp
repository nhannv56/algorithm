/******************************************************************************

https://www.acmicpc.net/problem/12793
bfs, foodfill, tọa độ đường đi

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
int N,M;
void floodfill(const vector<string>& raw, vector<vector<int>> &data){
    int label = 0;
    vector<vector<bool>> visited(raw.size(), vector<bool>(raw[0].length(), false));
    for(int i = 1; i < raw.size(); i+=2){
        // cout<<raw[i]<<endl;
        for(int j = 1; j < raw[i].length(); j+=2){
            // cout<<raw[i][j]<<" ";
            if(raw[i][j]=='B' && data[i/2][j/2] == -1){
                deque<pair<int,int>> dq;
                dq.push_back({i,j});
                visited[i][j] = true;
                label++;
                //cout<<"start\n";
                
                while(!dq.empty()){
                    auto [x,y] = dq.front();dq.pop_front();
                    //cout<<x<< " "<<y<<" "<<raw[x][y]<<" label:"<<label<<endl;
                    if(raw[x][y]=='B'){
                        data[x/2][y/2] = label;
                    }
                    //travel next
                    int mv[2][4]={  {0,0,1,-1},
                                    {-1,1,0,0}};
                    
                    for(int m = 0; m < 4; ++m){
                        int nx = x+mv[0][m];
                        int ny = y+mv[1][m];
                        if(nx>=0 && nx < raw.size() && ny >=0 && ny <raw[0].length()&&
                        (raw[nx][ny] == '.'|| raw[nx][ny] == 'B')&& !visited[nx][ny]){
                            dq.push_back({nx,ny});
                            visited[nx][ny] = true;
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

    set<int> collected;
    float mx[2]={-0.5, 0.5};
    float my[2]={-0.5, 0.5};
    //0 up left 
    //1 up right 
    //2 down left 
    //3 down right
    int MAX_X= data[0].size();
    int MAX_Y = data.size();
    float y = 0, x = k;
    int mvx= 0, mvy=1;
    while(true){
        float nx = x+ mx[mvx];
        float ny = y+ my[mvy];
        //lấy tâm của 2 điểm -> chắc chắn nằm trong 1 ô -> chuyển về tọa độ ô và check label
        int i = data.size()-1-int((y+ny)/2);
        int j = (x+nx)/2;
        // cout<<x<< " "<< y<< " " <<data[i][j]<<endl;
        if(data[i][j]!=0)collected.insert(data[i][j]);
        x = nx; y = ny;
        if(x < 0 || y == 0){// điều kiện biên nếu xuất phát từ 0, 0  hoặc kết thúc khi y = 0
            break;
        }
		// chuyển hướng
        if(x==0){
            mvx=1;
        }
        if(x==MAX_X){
            mvx=0;
        }
        if(y == MAX_Y){
            mvy = 0;
        }
    }
    return collected.size();
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    float K;
    cin>>N>>M>>K;
    vector<vector<int>> data(M,vector<int>(N,-1));//labeling 
    vector<string> raw(2*M+1);
    for(int i = 0; i < raw.size();++i){
        cin>>raw[i];
    }

    floodfill(raw,data);
    
    cout<<solve(data, K);
	return 0;
}
