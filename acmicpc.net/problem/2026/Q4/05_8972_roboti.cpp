/******************************************************************************

https://www.acmicpc.net/problem/8972

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int R,C;
typedef pair<int,int> POS;
pair<int,int> playerMove(int x, int y, char ways){
    if(ways == '1'||ways == '4'||ways=='7'){
        --y;
    }else if(ways =='9'||ways=='6'||ways=='3'){
        ++y;
    }
    if(ways=='7'||ways=='8'||ways=='9'){
        --x;
    }
    if(ways=='1'||ways=='2'||ways=='3'){
        ++x;
    }
    return {x,y};
}
void solve(vector<string> & grids, string moves){
    
    vector<vector<int>> mask(R,vector<int>(C,0));//position of robot and player

    deque<POS> robots;
    POS p;
    for(int i = 0; i < R;++i){
        for(int j = 0; j < C;++j){
            if(grids[i][j] == 'I'){
                p = {i,j};
            }else if(grids[i][j]=='R'){
                robots.push_back({i,j});
            }
        }
    }
    for(int i = 0; i < moves.length(); ++i){     
        //player move
        //condition 1 player move
        auto newPos = playerMove(p.first,p.second, moves[i]);
        grids[p.first][p.second]='.';
        p = {newPos.first, newPos.second};
        if(grids[p.first][p.second] == '.'){
            grids[p.first][p.second]='I';
        }else{
            //condition 2 move to robot cell ->end
            cout<<"kraj "<<i+1;
            return;
        }   
        map<POS, int> robotCount;//check collision
        for(auto & robot: robots){
            //condition 3
            int dx = p.first - robot.first;
            int dy = p.second - robot.second;
            if(dx != 0) dx /= abs(dx);
            if(dy != 0) dy /= abs(dy);
            auto newRobotPos = make_pair(robot.first + dx, robot.second + dy);
            //condition 4
            if(newRobotPos == make_pair(p.first, p.second)){
                cout<<"kraj "<<i+1;
                return;
            }
			//note lại vị trí robot sẽ đi tới
            grids[robot.first][robot.second]='.';
            if(robotCount.find(newRobotPos) != robotCount.end()){
                robotCount[newRobotPos]++;
            }else{
                robotCount[newRobotPos]=1;
            }
        }
        robots.clear();
		//cập nhật vị trí mới cho robot chỉ sau khi tất cả các robot di chuyển xong tránh wrong grid state
        for(auto & entry: robotCount){
            if(entry.second == 1){
                robots.push_back(entry.first);
                grids[entry.first.first][entry.first.second]='R';
            }else{
                grids[entry.first.first][entry.first.second]='.';
            }
        }

    }
    for(int i = 0; i < R; ++i){
        cout<<grids[i]<<endl;
    }
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
    cin>>R>>C;
    vector<string> grids(R);
    string moves;
    for(int i = 0; i < R; ++i){
        cin>>grids[i];
    }
    cin>>moves;
    solve(grids, moves);
	return 0;
}
