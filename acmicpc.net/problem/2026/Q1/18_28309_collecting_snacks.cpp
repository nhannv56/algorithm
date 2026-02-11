/******************************************************************************

https://www.acmicpc.net/problem/23019
algo:dp
algo:ckn
algo:compress
algo:sorting
algo:matrix

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
long long T,R,C,N;

long long mod = 1000003;

long long modpow( long long a,long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}
//ckn tổ hợp
long long Cmod(const long long& n,const long long& k) {
    
    static vector<long long> fact(1,1), invfact(1,1);
    long long need = n;
    while ((long long)fact.size() <= need) {
        fact.push_back(fact.back() * fact.size() % mod);
    }
    while ((long long)invfact.size() <= need) {
        invfact.push_back(modpow(fact[invfact.size()], mod-2));
    }
    auto res =  fact[n] * invfact[k] % mod * invfact[n-k] % mod;
    //cout<<"ckn"<<n<<" "<<k<< "="<<res<<endl;
    return res;
}

struct Node{
    long long c=0,w=1; //total ways from bottom right to cur position
    bool cal = false;
    set<pair<long long,long long>> pre;
    pair<long long, long long> cur;
};
Node builDP(vector<vector<Node>>& dp,vector<vector<int>>& mt,vector<vector<long long>>& compress,const long long& x,const long long& y){
    //cout<<"buildDP:"<<x<<" "<<y<<endl;
    if(!dp[x][y].cal){
        Node up,left, cur;
        if(y-1 >= 0){
            up = builDP(dp,mt,compress, x, y-1);
        }
        if(x-1 >= 0){
            left = builDP(dp,mt,compress, x-1, y);
        }
       //tổng hợp cá đường đi trên/phải
        if(up.c == left.c){
            cur.c = up.c;
            cur.pre = left.pre;
            //cur.pre.insert(cur.pre.end(),up.pre.begin(), up.pre.end());
            for(auto it : up.pre){
                cur.pre.insert(it);
            }
        }else{
            cur = up.c < left.c ? left: up;
        }
       
        cur.c += mt[x][y];
        //nếu 1 điểm chứa snack
        //tính số cách từ điểm trước đó đến điểm hiện tại
        if(mt[x][y]){
            auto rx = compress[0][x], ry = compress[1][y];
            cur.w = 0;
            for(auto [nx,ny] : cur.pre){
               
                auto rnx = compress[0][nx], rny = compress[1][ny];
                
                cur.w += Cmod(abs(rx - rnx) + abs(ry -rny), abs(rx -rnx))*dp[nx][ny].w;
                cur.w%=mod;
                // cout<<"from:"<<rnx<<" "<<rny<<"->"<<rx<<" "<<ry<<":"<<Cmod(abs(rx - rnx) + abs(ry -rny), abs(rx -rnx))<<endl;
            }
            //clear điểm cũ và chèn điểm hiện tại vào cho lần đi tiếp theo từ điểm hiện tại tới điểm kế tiếp
            cur.pre.clear();
            cur.pre.insert({x,y});
        }
        dp[x][y] = cur;
        dp[x][y].cal = true;
    }
    return dp[x][y];
}
long long solve(vector<vector<Node>>& dp,vector<vector<int>>& mt,vector<vector<long long>>& compress){
    
    dp[0][0].c=1;
    dp[0][0].cal = true;
    dp[0][0].pre.insert({0,0});
    auto res = builDP(dp,mt,compress, dp.size()-1, dp[0].size()-1);
    // cout<<"solve:\n";
    // for(auto rows : dp){
    //     for(auto c : rows){
    //         cout<<c.c<<" ";
    //     }cout<<endl;
    // }
    return res.w%mod;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    
    cin>>T;
    for(int t = 0; t < T; ++t){
        cin>>R>>C>>N;
        vector<vector<long long>> compress(2);
        
        long long x, y;
        vector<pair<long long,long long>> pos;
        unordered_map<long long, long long> x2c, y2c;
        
        compress[0].push_back(1);
        compress[1].push_back(1);
        compress[0].push_back(R);
        compress[1].push_back(C);
        pos.push_back({1,1});
        pos.push_back({R,C});
        
        for(int i = 0; i < N; ++i){
            cin>>x>>y;
            if((x==1&&y==1)||(x==R&&y==C)){
                continue;
            }
            pos.push_back({x,y});
            compress[0].push_back(x);
            compress[1].push_back(y);
        }
        sort(compress[0].begin(), compress[0].end());
        sort(compress[1].begin(), compress[1].end());
        
        auto last = std::unique(compress[0].begin(), compress[0].end());
        compress[0].erase(last, compress[0].end());
        
        last = std::unique(compress[1].begin(), compress[1].end());
        compress[1].erase(last, compress[1].end());
        
        for(int i = 0; i < compress[0].size();++i){
            x2c[compress[0][i]] = i;
        }
        
        for(int i = 0; i < compress[1].size();++i){
            y2c[compress[1][i]] = i;
        }
        long long MaxX =compress[0].size();
        long long MaxY =compress[1].size();
        
        vector<vector<int>> mt(MaxX, vector<int>(MaxY, 0));
        for(auto [x,y]: pos){
            auto cx = x2c[x];
            auto cy = y2c[y];
            //cout<<"label:"<<x<<y <<" to "<<cx<<" "<<cy<<endl;
            mt[cx][cy] = 1;
        }
        // cout<<"compress:"<<endl;
        // for(auto rows : mt){
        //     for(auto c : rows){
        //         cout<<c<<" ";
        //     }
        //     cout<<endl;
        // }
        //dp
        
        
        //from 0 0 to m-1,n-1
        //dp đường số điểm tối đa có thể collected
        // tính số cách tại mỗi điểm collect luôn
        vector<vector<Node>> dp(MaxX,vector<Node>(MaxY));
        
        long long res =  solve(dp,mt,compress);
        cout<<res%mod<<'\n';
    }
    
	return 0;
}