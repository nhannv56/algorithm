/******************************************************************************

https://www.acmicpc.net/problem/3745
Binary Search
Longest Increasing Sequence Problem
algo: LIS

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
long long T,N,K, a, b;

long long maxP = 1e10;
size_t solve(vector<long long>& stocks){
    size_t count = 0;
    vector<long long> lis;
    for(int i = 0; i < stocks.size(); ++i){
        
        if(lis.size() == 0 || lis[lis.size()-1] < stocks[i]){
            lis.push_back(stocks[i]);
        }else{
            // when replace, still keep sub array is correct
            // a b c stocks[i] d e f có chuỗi mới dài hơn -> ghi đè lên chuỗi cũ đảm bảo theo thứ tự
            auto it = lower_bound(lis.begin(), lis.end(),stocks[i]);
            *it = stocks[i];
        }
        
    }
    return lis.size();
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    string line;
    long long count = 0;
    vector<vector<long long>> p;
    long long N = -1;
    while(std::getline(std::cin, line)){
        //cout<<"line:"<<line<<endl;
        std::stringstream ss(line);
        long long number;
        while (ss >> number) {
            //cout<<"num:"<<number<<endl;
            if(N == -1 || p[p.size()-1].size() == N){
                N = number;
                //cout<<"N:"<<N<<endl;
                count = 0;
                p.push_back(vector<long long>());
            }else if(p[p.size()-1].size() < N){
                //cout<<number<<" ";
                p[p.size()-1].push_back(number);
                count++;
            }
        }
    }
	for(auto stock : p){
	    cout<<solve(stock)<<'\n';
	}
	return 0;
}