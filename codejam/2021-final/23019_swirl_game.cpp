/******************************************************************************

https://codejam.lge.com/problem/23019
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, T;
pair<string,string> cal(vector<string> & row,vector<string> & cols,vector<string> & rrow,vector<string> & rcols, int a, int b,const int s){
    if(s==1){
        string s = "";
        s.push_back(row[a][a]);
        return {s,s};
    }
    if(s==0){
        return {"",""};
    }
    int i = (N-s)/2;
    string ri = row[i].substr(i,s-1)+cols[N-i-1].substr(i,s-1)+rrow[N-i-1].substr(i,s-1)+rcols[i].substr(i,s-1);
    ri+=ri;
    string le = cols[i].substr(i,s-1)+row[N-i-1].substr(i,s-1)+rcols[N-i-1].substr(i,s-1)+rrow[i].substr(i,s-1);
    le+=le;
    string s1,s2;
    int na,nb;
    if(a==b ){
        if(a < N/2)
        {
            s1 = ri.substr(0,s*4-4);
            s2= le.substr(0,s*4-4);
            na=a+1;
            nb=b+1;
        }else{
            s1=ri.substr(2*s-2,s*4-4);
            s2=le.substr(2*s-2,s*4-4);
            na=a-1;
            nb=b-1;
        }
    }else{
        if(a < b){
            s1 = ri.substr(s-1,s*4-4);
            s2= le.substr(3*s-3,s*4-4);
            na = a+1;
            nb=b-1;
        }else{
            s1 = ri.substr(3*s-3,s*4-4);
            s2= le.substr(s-1,s*4-4);
            na=a-1;
            nb=b+1;
        }
    }
    auto [ma,mi] = cal(row,cols,rrow,rcols,na,nb,s-2);
    auto r1 = max(s1,s2)+ma, r2 = min(s1,s2)+mi;
    return {r1,r2};
}
pair<string, string> solve(vector<string> & row){
    vector<string> cols(row[0].length()), rcols(row[0].length()), rrow(row.size());
    for(int i = 0; i < row[0].length();++i){
        for(int j = 0; j < row.size(); ++j){
            cols[i].push_back(row[j][i]);
        }
        rcols[i]= cols[i];
        reverse(rcols[i].begin(), rcols[i].end());
        // cout<<rcols[i]<<endl;
    }
    for(int i = 0; i < row.size();++i){
        rrow[i]= row[i];
        reverse(rrow[i].begin(), rrow[i].end());
    }
    vector<pair<int,int>> points = {{0,0},{0, N-1},{N-1,0},{N-1,N-1}};
    string mi, ma;
    for(auto [x,y] : points){
        // cout<<"solve:"<<x<<" "<<y<<endl;
        auto [a,b] = cal(row,cols, rrow,rcols, x,y,N);
        if(mi.empty()){
            ma = a;
            mi = b;
        }
        ma = max(ma,a);
        mi = min(mi,b);
    }
    return{ma,mi};
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
    double X,Y;
    while(T > 0){
        cin>>N;
        vector<string> gr(N);
        for(int i = 0; i < N; ++i){
            cin>>gr[i];
        }
        auto [ma,mi] = solve(gr);
        cout<<ma<<" "<<mi<<endl;
        --T;
    }
    return 0;
}
