/******************************************************************************

https://www.acmicpc.net/problem/23000
prefix sum, grids
dùng prefix sum lưu tổng trái, phải, trên, dưới tại mỗi điểm
tính tại mỗi điểm là góc của chữ L tính số lượng

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
struct Node{
    int t=0,d=0,l=0,r=0;//top down, left right
};
int cal(int l1, int l2){
    int mi = min(l1,l2);
    int ma = max(l1,l2);
    int res = 0;
    //min là cạnh dài -> bỏ qua số chẵn 2 ko phải là cạnh dài
    if(mi>=4){
        res+=mi/2-1;
    }
    //cạnh max là cạnh dài  max >=4 và min >=2 là chữ L valid
    if(ma >= 4 && mi >=2){
        if(mi*2 >= ma){//cạnh ngắn thừa tính số lượng chữ L theo cạnh dài
            res+=ma/2-1;
        }else{// cạnh dài thừa -> count theo cạnh ngắn
            res+=mi-1;
        }
    }
    return res;
}
int solve(vector<vector<int>>& grids){
    int res = 0;
    vector<vector<Node>> counts(grids.size(), vector<Node>(grids[0].size()));
    //left to right
    int R = grids.size()-1;
    int C = grids[0].size()-1;
    for(int i = 0; i < grids.size(); ++i){
        for(int j = 0; j < grids[i].size();++j){
            if(grids[i][j]==1){
                if(j>0){
                    counts[i][j].l = counts[i][j-1].l + 1;
                }else{
                    counts[i][j].l = 1;
                }
            }
            if(grids[i][C-j]==1){
                if(C-j < C){
                    counts[i][C-j].r = counts[i][C-j+1].r + 1;
                }else{
                    counts[i][C-j].r = 1;
                }
            }
        }
    }
    //top to down
    for(int j = 0; j < grids[0].size();++j){
        for(int i = 0; i < grids.size(); ++i){
            if(grids[i][j]==1){
                if(i > 0){
                    counts[i][j].t = counts[i-1][j].t + 1;
                }else{
                    counts[i][j].t = 1;
                }
            }
            if(grids[R-i][j]==1){
                if(R-i < R){
                    counts[R-i][j].d = counts[R-i+1][j].d + 1;
                }else{
                    counts[R-i][j].d = 1;
                }
            }                            
        }
    }
    for(auto l : counts){
        for(auto c: l){
            // cout<<"("<<c.l<<","<<c.t<<","<<c.r<<","<<c.d<<") ";
            res+= cal(c.l,c.t)+cal(c.t, c.r)+cal(c.r,c.d)+cal(c.d, c.l);
        }
        //cout<<endl;
    }
    return res;
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
    int T,R,C;
    cin>>T;
    for(int t = 1; t <= T;++t){
        cin>>R>>C;
        vector<vector<int>> grids(R,vector<int>(C));
        for(int i = 0; i < R;++i){
            for(int j = 0; j < C;++j){
                cin>>grids[i][j];
            }
        }
        auto res = solve(grids);
        cout<<"Case #"<<t<<": "<<res<<endl;
    }
    return 0;
}
