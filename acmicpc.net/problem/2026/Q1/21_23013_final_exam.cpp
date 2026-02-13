/******************************************************************************

https://www.acmicpc.net/problem/27281
bfs, prirority queue, binary search, Dijkstra's

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

long long N,M,T;

vector<long long> solve(map<long long, long long>& mp,const vector<long long>& students){
    vector<long long> res(students.size(), 0);
    for(int i = 0; i < students.size();++i){
        const auto s = students[i];
        auto r = mp.lower_bound(s);
        auto l = r;
        if(mp.size() > 0 && r == mp.end()){  //a < s <= b -> end, a <=b < s -> end
            auto last = std::prev(mp.end());
            auto a = last->first, b = last->second;
            if(s <= b){
                res[i]=s;
                mp.erase(last);
                if(a < s){
                    mp[a]=s-1;
                }
                if(s < b){
                    mp[s+1]=b;
                }
            }else{
                res[i] = b;
                if(a < b){
                    mp[a]=b-1;
                }else{
                    mp.erase(last);
                }
            }            
            continue;
        }
        if(l != mp.begin()){
            --l;
        }
        if(l==r){// không có item nào bên trái
            auto a2 = r->first, b2= r->second;
            res[i] = a2;
            //đoan a2 < b2 bỏ a2
            mp.erase(r);
            if(a2 < b2){ 
                mp[a2+1] = b2;
            }
        }else{
            auto a1 = l->first, b1 = l->second, a2 = r->first, b2 = r->second;
            if(s == a2){
                res[i] = a2;
                mp.erase(r);
                if(a2 < b2 ){
                    mp[a2+1] = b2;
                }
            }else{ // s < a2
                if(s <= b1){
                    res[i] = s;
                    mp[a1] = s-1;
                    if(s < b1){
                        mp[s+1] = b1;
                    }
                }else{ //b1 < s < a2
                    if(s-b1 <= a2-s){
                        res[i]=b1;
                        if(a1 < b1){
                            mp[a1]=b1-1;
                        }else{
                            mp.erase(l);
                        }
                    }else{
                        res[i] = a2;
                        if(a2 < b2){
                            mp[a2+1]=b2;
                        }
                        mp.erase(r);
                    }
                }
                
            }
        }
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

    cin>>T;
	for(int t = 1; t <=T; ++t){
        cin>>N>>M;
        map<long long, long long> sets;
        vector<long long> students(M);
        long long a, b;
        for(int n = 0; n < N; ++n){
            cin>>a>>b;
            sets[a]=b;
        }
        for(int m = 0; m < M; ++m){
            cin>>students[m];
        }
        auto res = solve(sets,students);
        cout<<"Case #"<<t<<": ";
        for(auto it : res){
            cout<<it<<' ';
        }
        cout<<'\n';
    }
	return 0;
}