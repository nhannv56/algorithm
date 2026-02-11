/******************************************************************************

https://www.acmicpc.net/problem/23019
codejam sort, math
algo:Bruteforcing
algo:Implementation
algo:Sorting

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
int T,N;

vector<vector<pair<string,string>>> dp;
pair<string,string> getOuterMost(const vector<string>& rows,const vector<string>& cols,const vector<string>& rrows,const vector<string>& rcols,int r, int c, int n){
    string rc = "";
    string lc = "";
    int rr = r,cc=c;
    if(rr==cc){
        if(rr >= N/2){
            rr = rr-n+1;
            cc = rr;
        }
    }else{
        rr = min(rr,cc);
        cc= rr;
    }
    string  ef1=rows[rr].substr(cc,n-1),
            ef2=cols[cc+n-1].substr(rr,n-1),
            ef3=rrows[rr+n-1].substr(cc,n-1),
            ef4=rcols[cc].substr(rr,n-1);//edge right clock
    string  eb1=cols[cc].substr(rr,n-1),
            eb2=rows[rr+n-1].substr(cc,n-1),
            eb3=rcols[cc+n-1].substr(rr,n-1),
            eb4=rrows[rr].substr(cc,n-1);//edge left clock
    if(r==c) {
        if(r < N/2){// top left
            rc = ef1 + ef2 + ef3 + ef4;
            lc = eb1 + eb2 + eb3 + eb4;
        }else{
            rc = ef3+ef4+ef1+ef2;
            lc = eb3+eb4+eb1+eb2;
        }
    }else{
        if(r < c){//top right
            rc = ef2+ef3+ef4+ef1;
            lc = eb4+eb1+eb2+eb3;
        }else{ //below left
            rc = ef4+ef1+ef2+ef3;
            lc = eb2+eb3+eb4+eb1;
        }
    }
    return {rc,lc};
}
pair<string,string> cal(const vector<string>& rows,const vector<string>& cols,const vector<string>& rrows,const vector<string>& rcols, int r, int c,int n){
   int mrc = max(r,c);
   if(n==0){
       return {"",""};
       
   }else if(n==1){
       return {std::string{rows[N/2][N/2]},std::string{rows[N/2][N/2]}};
   }
    auto [fc,bc] = getOuterMost(rows, cols, rrows, rcols, r, c, n);
    string maxS,minS;
    if(fc > bc){
        maxS= fc;
        minS = bc;
    }else{
        maxS=bc;
        minS=fc;
    }
    int nr=r,nc=c;
    if(r==c ){
        if(r < N/2){
            ++nr;++nc;
        }else{
            --nr;--nc;
        }
    }else if( r < c){
        ++nr;
        nc--;
    }else {
        --nr;
        ++nc;
    }
    auto [maxNS, minNS] = cal(rows, cols, rrows, rcols, nr, nc, n-2);
    return {maxS+maxNS,minS+minNS};
    
}
pair<string,string> solve(const vector<string>& rows,const vector<string>& cols,const vector<string>& rrows,const vector<string>& rcols, int r, int c){

    return cal(rows,cols, rrows, rcols, r, c, N);
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>T;
    while(T > 0){
        cin>>N;
        string str;
        vector<string> rows(N), cols(N,""), rrows(N,""),rcols(N,"");
        for(int i = 0; i < N; ++i){
            cin>>rows[i];
            rrows[i] = rows[i];
            std::reverse_copy(rows[i].begin(), rows[i].end(),rrows[i].begin());
            // cout<<rrows[i]<<endl;
        }
        for(int i = 0; i < N;i++){
            for(int j = 0; j < N;++j){
                cols[i]+=rows[j][i];
            }
            rcols[i] = cols[i];
            reverse_copy(cols[i].begin(),cols[i].end(),rcols[i].begin());
            // cout<<rcols[i]<<endl;
        }
        dp = vector<vector<pair<string,string>>>(N,vector<pair<string,string>>(N,{"",""}));
        pair<string,string> res;//max min
        vector<pair<int,int>> pos{{0,0},{0,N-1},{N-1,N-1},{N-1,0}};
        for(auto [r,c] : pos){
            auto cur =  solve(rows, cols, rrows, rcols, r, c);
            if(res.first.empty()){
                res.first = cur.first;
                res.second = cur.second;
            }else{
                res.first = max(res.first, cur.first);
                res.second = min(res.second, cur.second);
            }
        }
        cout<<res.first<<' '<<res.second<<'\n';
        --T;
    }
	return 0;
}