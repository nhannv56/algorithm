/******************************************************************************

https://www.acmicpc.net/problem/21982
monotonic stack

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

long long T,N,X;
//map<long long, long long> skills;//skill, count
void solve(long long h[],long long v[], long long X) {
    

	deque<int> mono;
    
	long long result=-1;
	mono.push_back(0);
	int j = 0;
	//cout<<"v0 "<<v[0]<<endl;
	for(int i = 1; i < N; ++i){
	    
	    while(h[i]-h[j] > X){
	        ++j;
	    }
	    while(mono.size() > 0 && mono.front() < j){
           mono.pop_front();
        }
        
	    if(i-j >= 1){
	        if(mono.size()>0){
	            result = max(result, v[i] + v[mono.front()]);
	        }
	    }
	    while(mono.size() > 0 && v[mono.back()] < v[i]){
	        mono.pop_back();
	    }
	    mono.push_back(i);
	    
	}
	cout<<result<<'\n';
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin>>T;
	
	long long hs,ha,hb,hc;
	long long ws,wa,wb,wc;
	for(int t = 0; t < T; ++t) {
		cin>>N>>X;
		
		long long H[N];
		long long W[N];
		long long V[N];
		
		cin>>hs>>ha>>hb>>hc;
		cin>>ws>>wa>>wb>>wc;
		
		H[0] = hs % hc + 1;
        W[0] = ws % wc + 1;
		V[0]= H[0]*W[0];
		
		for(int i = 1; i < N; ++i){
		    H[i] = H[i-1] + 1 + (H[i-1] * ha + hb) % hc;
            W[i] = (W[i-1] * wa + wb) % wc + 1;
            V[i] = H[i]* W[i];
            //cout<<"V"<<i<<" "<<V[i]<<endl;
		}
		solve(H, V, X);
	}
	return 0;
}