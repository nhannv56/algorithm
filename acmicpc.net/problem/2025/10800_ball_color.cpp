/******************************************************************************

https://www.acmicpc.net/problem/10800
Implementation
Sorting
Prefix Sum

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int N;

unordered_map<int, vector<pair<int,int>>> dataCSI;//color,size, index

vector<long long> sums(2001,0); //sum by size_t


void cal(vector<long long> & result ){
    
    for(auto [c, si] : dataCSI){
        long long res = 0;
        //cout<<"C:"<<c<<endl;
        sort(si.begin(), si.end());
        long long preS = 1;
        long long preColorSum = 0;
        for(auto [s, i] : si){
            //cout<<"s: "<<s<<" i:"<<i<<endl;
            
            if(s == preS){
                result[i] = res;
                preColorSum+=s;
            }else{
                for(long long ss = s-1; ss >=preS; --ss){
                    res+=sums[ss]*ss;
                }
                preS = s;
                res-=preColorSum;
                preColorSum=s;
            }
            result[i]=res;
        }
    }
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>N;
    for(int i = 0; i < N; ++i){
        long long c, s;
        cin>>c>>s;
        dataCSI[c].push_back({s,i});
        ++sums[s];
    }
    vector<long long> result(N,0);
    cal(result);
    for(auto r : result){
        cout<<r<<'\n';
    }
	return 0;
}