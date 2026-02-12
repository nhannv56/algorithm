/******************************************************************************

https://www.acmicpc.net/problem/27281
bfs, prirority queue, binary search, Dijkstra's

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

long long N,M,T;

vector<long long> solve(map<long long, long long>& mp,vector<long long>& students){
    vector<long long> res(students.size(), 0);
    
    // for(auto [a, b]: mp){
    //     cout<<a<<" "<<b<<endl;

    // }
    for(int i = 0; i < students.size();++i){
        auto it = mp.lower_bound(students[i]);
        // cout<<"find:"<<students[i]<<endl;
        if(it != mp.end()){//have item more than student
            // cout<<"right:"<<it->first<<" "<<it->second<<endl;
            if(it->first == students[i]){
                res[i]=it->first;
                auto a = it->first, b = it->second;
                mp.erase(it);
                if(a != b){                    
                    mp[a+1]= b;
                }
            }else{
                if(mp.size() >= 2 && it != mp.begin()){ // có phần tử phía trước
                    auto l = it;
                    --l;
                    // cout<<"left:"<<l->first<<" "<<l->second<<endl;
                    if(l->second == students[i]){
                        res[i] = students[i];
                        auto a = l->first, b = l->second;
                        mp.erase(l);
                        if(a != b){
                            mp[a] =  b - 1;
                        }
                    }else if(l->second > students[i]){
                        res[i] = students[i];
                        auto a = l->first, b = l->second;
                        mp.erase(l);
                        mp[a] = students[i]-1;
                        mp[students[i]+1] = b;
                    }else{
                        //a1 b1 s a2 b2
                        // cout<<l->first<<" "<<l->second<< " "<<students[i]<<" "<<it->first<<" "<<it->second<<endl;
                        if(students[i] - l->second <= it->first - students[i]){
                            res[i] = l->second;
                            auto a = l->first, b = l->second;
                            mp.erase(l);
                            // cout<<"compare:"<<a<<" "<<b<<endl;
                            if(a != b){
                                mp[a] = b-1;
                                // cout<<"insert:"<<a<<" "<<b-1<<endl;
                            }
                        }else{
                            res[i]=it->first;
                            auto a = it->first, b = it->second;
                            mp.erase(it);
                            if(a != b){
                                mp[a+1] = b;
                            }
                        }
                    }
                }else{//at begin
                    res[i]=it->first;
                    auto a = it->first, b = it->second;
                    mp.erase(it);
                    if(a != b){
                        mp[a+1] = b;
                    }
                }
            }
        }else{// all less than students[s]
            if(mp.size() > 0){
                --it;
                res[i] = it->second;
                auto a = it->first, b = it->second;
                mp.erase(it);
                if(a != b){
                    mp[a] = b-1;
                }
            }
        }
        // cout<<"find:"<<students[i]<<" "<<res[i]<<endl;
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