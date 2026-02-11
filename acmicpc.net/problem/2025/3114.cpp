/******************************************************************************

https://www.acmicpc.net/problem/3114
dp, prefix sum

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
struct Node{
    long long s, r, c;
     bool operator<(const Node& other) const {
        return s < s; // Max-priority by priority_factor
    }
};
int R,C;
//string lands[1500][1500] ;
long long dp[1500][1500]={-1,};

long long resolve(int x, int y, vector<vector<pair<long long ,long long>>>& cells,vector<vector<pair<long long, long long>>>&  lands) {
    //cout<<"xy:"<<x<<" "<<y<<endl;
    long long result = 0, ml=0, mt=0, mtl=0;
    if(x==0 && y==0){
        dp[0][0] =  lands[0][C-1].second- cells[0][0].second;
        return dp[0][0];
    }
    if(dp[x][y] != -1){
        return dp[x][y];
    }else{
        if(y > 0){//right to left
            ml = resolve(x, y-1, cells, lands) - cells[x][y].second;
            //cout<<"l:"<<ml<<endl;
        }
        if(x > 0){//down to up
            mt = resolve(x-1, y, cells, lands) 
            + lands[x][y].first - cells[x][y].first //apple
            + lands[x][C-1].second - lands[x][y].second; //banana
            //cout<<"t:"<<mt<<endl;
        }
        if(x > 0 && y > 0){//up left
            mtl = resolve(x-1,y-1, cells, lands) 
            + lands[x][y].first - cells[x][y].first //apple
            + lands[x][C-1].second - lands[x][y].second; //banana
            //cout<<"tl:"<<mtl<<endl;
        }
    }
    dp[x][y] = max({ml, mt, mtl});
    
    //stop and last -> no destroy 1 of 2 side can get that
    return dp[x][y];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>R>>C;
	string cell;
	vector<vector<pair<long long ,long long>>>  lands = vector<vector<pair<long long,long long>>>(R, vector<pair<long long,long long>>(C));
	vector<vector<pair<long long ,long long>>>  cells = vector<vector<pair<long long,long long>>>(R, vector<pair<long long,long long>>(C));
	memset(dp,-1, sizeof(long long)*1500*1500);
	
	long long preA, preB, cur;
	for(int i = 0; i < R; ++i){
	    for(int j = 0; j < C; ++j){
	        cin>>cell;
	        lands[i][j].first = j > 0 ? lands[i][j-1].first : 0;
	        lands[i][j].second = j > 0 ? lands[i][j-1].second : 0;
	        cur = stol(cell.substr(1));
	        
	        if(cell[0] == 'A'){
	            lands[i][j].first += cur;    
	            cells[i][j].first=cur;
	        }else{
	            lands[i][j].second += cur;
	            cells[i][j].second = cur;
	        }
	        //cout<<"("<<lands[i][j].first<<","<<lands[i][j].second<<") ";
	    }
	    //cout<<endl;
	}
	cout<<resolve(R-1, C-1, cells, lands);
	//cout<<dp[R-1][C-1];
	return 0;
}