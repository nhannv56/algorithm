/******************************************************************************

https://www.acmicpc.net/problem/8972

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
int R,C;
struct POS{
    int x, y, m;
};
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
const int PLAYER_POS = 10000;
const int DESTROY_POS = 10000-1;
void solve(vector<string> & grids, string moves){
    
    vector<vector<int>> mask(R,vector<int>(C,0));//position of robot and player

    deque<POS> robots;
    POS p;
    for(int i = 0; i < R;++i){
        for(int j = 0; j < C;++j){
            if(grids[i][j] == 'I'){
                p = {i,j,1};
                mask[i][j]=PLAYER_POS;
            }else if(grids[i][j]=='R'){
                robots.push_back({i,j,1});
                mask[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < moves.length(); ++i){     
        //player move
       
        auto newPos = playerMove(p.x,p.y, moves[i]);
        mask[p.x][p.y]=0;
        p = {newPos.first, newPos.second,1};
        if(mask[p.x][p.y] == 0){
            mask[p.x][p.y] = PLAYER_POS;
        }else{
            cout<<"kraj "<<i+1;
            return;
        }   
        if(robots.size() > 0){
            const auto round = robots.front().m;
            while(!robots.empty() && robots.front().m == round){
                const auto cur = robots.front(); robots.pop_front();
                //bug => cung 1 round 2 roboot di den 1 o co roboot -> o co roboot chua di bi bo qua
                // if(mask[cur.x][cur.y] == DESTROY_POS){
                //     mask[cur.x][cur.y]=0;
                //     continue; //Ô nhiều robot bị phá hủy
                // }
                //=> xử lý xóa 1 roboot enqueue -> nhưng nó nên đã bị phá hủy
                POS ne = {cur.x, cur.y, cur.m+1};
                if(p.x != cur.x) {
                    cur.x > p.x ? ne.x--:ne.x++;
                }
                if(p.y != cur.y) {
                    cur.y > p.y ? ne.y--:ne.y++;
                }
                if(mask[ne.x][ne.y]==PLAYER_POS){
                    cout<<"kraj "<<i+1;
                    return;
                }
                mask[cur.x][cur.y]=0;
                if(mask[ne.x][ne.y] == ne.m || mask[ne.x][ne.y] == DESTROY_POS){
                    // cout<<"destroy:"<<ne.x<<" "<<ne.y<<endl;
                    mask[ne.x][ne.y] = DESTROY_POS;//ô roboot bị hủy                    
                }else{
                    mask[ne.x][ne.y] = ne.m;
                    robots.push_back(ne);
                }
            }
        }
        
    }
    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C;++j){
            char val = '.';
            if(mask[i][j] == PLAYER_POS){
                val = 'I';
            }else if(mask[i][j] > 0 && mask[i][j] != DESTROY_POS){
                val = 'R';
            }
            cout<<val;
        }cout<<'\n';
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
