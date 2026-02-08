/******************************************************************************

https://www.acmicpc.net/problem/3151
Bruteforcing
Sorting
Binary Search
Two-pointer

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int N;
map<long long, long long> skills;//skill, count

void solve() {
	long long res = 0;
	for(auto f = skills.begin(); f !=skills.end() ; ++f) {
	    if(f->first > 0){
	        break;
	    }
		for(auto s = f; s !=skills.end(); ++s) {
			auto target =  skills.find(-(f->first + s->first));
			//cout<<f->first<<" "<<s->first<<endl;
			if(target != skills.end()) { //found and avoid duplicate
			    if(target->first - s->first >= 0 ){
    				if(target->first == 0 && s->first == 0){
    				    res+=f->second*(f->second-1)*(f->second-2)/6;
    				}else if(f->first == s->first) {
    					res+=target->second * f->second*(f->second-1ll)/2ll;
    				} else if(s->first == target->first) {
    					res+=f->second * target->second*(target->second-1ll)/2ll;
    				} else {
    					res+= f->second*s->second*target->second;
    				}
			    }else{
			        break;
			    }
			}
		}
	}
	cout<<res<<'\n';
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>N;
	long long sk;
	for(int i = 0; i < N; ++i) {
		cin>>sk;
		if(skills.find(sk) == skills.end()) {
			skills[sk] = 1ll;
		} else {
			++skills[sk];
		}
	}
	solve();
	return 0;
}
