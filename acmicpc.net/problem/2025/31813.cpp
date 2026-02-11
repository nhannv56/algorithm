/******************************************************************************

https://www.acmicpc.net/problem/31813
Mathematics
Greedy
Constructive

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

long long T,N,K;
vector<long long> num;
//map<long long, long long> skills;//skill, count
bool solve(long long NumDigit, long long K, deque<long long> & output) {
    
    //cout<<"K:"<<K<<endl;
    if(K == 0){
        return true;
    }
    auto it = lower_bound(num.begin(), num.end(), K);
    if(it != num.end() && *it > K){
        it--;
    }
    int nextDigitSize = NumDigit-1;
    while(it >= num.begin()){
        //cout<<"find:"<<*it<<"\n";
        if(*it*nextDigitSize < K - *it){
            return false;
        }else{
            output.push_back(*it);
            bool res = solve(nextDigitSize, K - *it, output);
            if(res == true){
                return true;
            }else{
                output.pop_back();
            }
        }
        it--;
    }
    return true;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin>>T;
	
	//generate number
	for(long long i = 0; i < 17; ++i){
	    for(long long k = 1; k < 10; k++){
	        if(i > 0){
	            //cout<<i<< " "<<powl(10ll,i)*k<<"+"<<num[num.size()-9]<<" ";
	            num.push_back(powl(10ll,i)*k + num[num.size()-9]);
	        }else{
    	        num.push_back(k);
	        }
	        //cout<<num[num.size()-1]<<endl;
	    }
	}
	
	for(int t = 0; t < T; ++t) {
		cin>>N>>K;
		deque<long long> output;
		solve(N+1, K, output);
		cout<<output.size()<<'\n';
		for(auto it : output){
		    cout<<it<<" ";
		}
		cout<<'\n';
	}
	return 0;
}