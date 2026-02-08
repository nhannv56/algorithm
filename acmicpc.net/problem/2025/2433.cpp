/******************************************************************************

https://www.acmicpc.net/problem/2433
Data Structures
Deque
Sliding Window
Deque Range Maximum Trick

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int N,M,C;
//map<long long, long long> skills;//skill, count

void solve(int arr[]) {
	int res = 0;
	map<int, int> pmin;
	map<int, int, std::greater<int>> pmax;
	bool none = true;
	for(int i = 0; i < N; ++i){
	    // remove first and add 1 more
	    if(i >= M){
	        int lastIndex = i - M;//last should remove
	        //max heap
	        if(pmax[arr[lastIndex]] == 1){
	            pmax.erase(arr[lastIndex]);
	        }else{
	            --pmax[arr[lastIndex]];
	        }
	        //min heap
	        if(pmin[arr[lastIndex]] == 1){
	            pmin.erase(arr[lastIndex]);
	        }else{
	            --pmin[arr[lastIndex]];
	        }
	    }
        if(pmax.find(arr[i]) == pmax.end()){
            pmax[arr[i]]=1;
        }else{
            ++pmax[arr[i]];
        }
        if(pmin.find(arr[i]) == pmin.end()){
            pmin[arr[i]]=1;
        }else{
            ++pmin[arr[i]];
        }
        //cout<<"i:"<<i<<" max:"<<pmax.begin()->first<<" min:"<<pmin.begin()->first<<endl;
        if(i >= M-1 && pmax.begin()->first - pmin.begin()->first <= C){
            cout<<i-M+2<<'\n';
            none = false;
        }
	}
	if(none){
        cout<<"NONE\n";
    }
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>N>>M>>C;
	int arr[N];
	for(int i = 0; i < N; ++i) {
		cin>>arr[i];
	}
	solve(arr);
	return 0;
}
