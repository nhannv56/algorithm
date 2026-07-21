/******************************************************************************

https://codejam.lge.com/problem/23019
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, T;
pair<string,string> cal(vector<string> & row,vector<string> & cols,vector<string> & rrow,vector<string> & rcols, int a, int b,int s){
    if(N%2==1 && a==b && a==N/2){
        return {to_string(row[a][a]),to_string(row[a][a])};
    }
    if(s==0){
        return {"",""};
    }
    int i = N-s;
    string ri = row[i].substr(i,s)+cols[s-1].substr(i+1,s-1)+rrow[s-1].substr(i+1,s-1)+rcols[i].substr(i+1,s-2);
    string le = cols[i].substr(i,s)+row[s-1].substr(i+1,s-1)+rcols[s-1].substr(i+1,s-1)+rrow[i].substr(i+1,s-2);
    cout<<ri<<" "<<le<<endl;
    // if(a==b){
    //     if(a < N/2){
    //         string ri = row[a].substr(b,s)+cols[s-1].substr(a+1,s-1)+rrow[N-a].substr(b+1,s-1)+rcols[a].substr(b+1,s-2);
    //         string le = cols[b].substr(a,s)+row[s-1].substr(b+1,s-1)+rcols[s-1].substr(b+1,s-1)+rrow[a].substr(b+1,s-2);
    //         auto [mi,ma] = cal(row,cols,rrow,rcols,a+1,b+1,s-2);
    //         return {min(ri,le)+mi,max(ri,le)+ma};
    //     }else{
    //         string ri = rrow[N-a].substr(b+1,s-1)+rcols[a].substr(b+1,s-2)+row[a].substr(b,s)+cols[s-1].substr(a+1,s-1);
    //         string le = rcols[s-1].substr(b+1,s-1)+rrow[a].substr(b+1,s-2)+cols[b].substr(a,s)+row[s-1].substr(b+1,s-1);
    //         auto [mi,ma] = cal(row,cols,rrow,rcols,a-1,b-1,s-2);
    //         return {min(ri,le)+mi,max(ri,le)+ma};
    //     }
    // }else{
    //     if(a < b){
    //         string ri = row[a].substr(b,s)+cols[s-1].substr(a+1,s-1)+rrow[N-a].substr(b+1,s-1)+rcols[a].substr(b+1,s-2);
    //         string le = cols[b].substr(a,s)+row[s-1].substr(b+1,s-1)+rcols[s-1].substr(b+1,s-1)+rrow[a].substr(b+1,s-2);
    //         auto [mi,ma] = cal(row,cols,rrow,rcols,a+1,b+1,s-2);
    //         return {min(ri,le)+mi,max(ri,le)+ma};
    //     }else{

    //     }
    // }
    return {"",""};
}
pair<string, string> solve(vector<string> & row){
    vector<string> cols(row[0].length()), rcols(row[0].length()), rrow(row.size());
    for(int i = 0; i < row[0].length();++i){
        for(int j = 0; j < row.size(); ++j){
            cols[i].push_back(row[j][i]);
        }
        rcols[i]= cols[i];
        reverse(rcols[i].begin(), rcols[i].end());
    }
    for(int i = 0; i < row.size();++i){
        rrow[i]= row[i];
        reverse(rrow[i].begin(), rrow[i].end());
    }
    vector<pair<int,int>> points = {{0,0},{0, N-1},{N-1,0},{N-1,N-1}};
    string mi, ma;
    for(auto [x,y] : points){
        auto [a,b] = cal(row,cols, rrow,rcols, x,y,N);
        mi = min(mi,a);
        ma = max(ma,b);
    }
    return{mi,ma};
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> T;
    int N;
    double X,Y;
    while(T > 0){
        cin>>N;
        vector<string> gr(N);
        for(int i = 0; i < N; ++i){
            cin>>gr[i];
        }
        auto [ma,mi] = solve(gr);
        cout<<ma<<' '<<mi<<endl;
        --T;
    }
    return 0;
}
