/******************************************************************************

https://codejam.lge.com/problem/17430
algo: binary search
aglo: map
algo: sort
algo: no bondary
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, T;

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
    while(T > 0){
        cin>>N;
        vector<pair<int,int>> poles(N);
        
        int x,y;
        
        map<int,vector<int>> mp;
        for(int i =  0 ; i < N;++i){
            cin>>x>>y;
            poles[i]={x,y};
            mp[x].push_back(y);
        }
        for(auto& [k,vt] : mp){
            sort(vt.begin(), vt.end());
        }
        bool balanced = true;
        for(int i = 0; i < N;++i){
            for(int j = i+1; j < N;++j){
                int xi=poles[i].first, yi = poles[i].second;
                int xj=poles[j].first, yj = poles[j].second;
                int mask = 0;
                auto fxi = mp.find(xi);
                auto fxj = mp.find(xj);
                if(fxi != mp.end() && fxi != mp.end()){
                    auto lpyi = lower_bound(fxj->second.begin(), fxj->second.end(),yi);
                    auto lpyj = lower_bound(fxi->second.begin(), fxi->second.end(),yj);
                    if(lpyi != fxj->second.end() && lpyj != fxi->second.end() && *lpyi == yi && *lpyj == yj){
                        break;
                    }else{
                        balanced = false;
                        break;
                    }                    
                }
            }
            if(!balanced){
                break;
            }
        }
        cout<< (balanced?"BALANCED": "NOT BALANCED")<<'\n';
        --T;
    }
    return 0;
}
