/******************************************************************************

https://www.acmicpc.net/problem/25093
Greedy
String

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int T;

void solve(int i, const string &s){
    string result(1,s[0]);
    string pre;
    pre.push_back(s[0]);
    for(int i = 1; i < s.length(); ++i){
        
        if(s[i] == pre[0]){ //aa
            result.push_back(s[i]);
        }else if(pre[0] < s[i]){ //a b
            
            result.append(pre);
            result.push_back(s[i]);
            pre = "";
            
        }else{//ba
            pre = "";
            result.push_back(s[i]);
        }
        pre.push_back(s[i]);
    }
    cout<<"Case #"<<i+1<<": "<<result<<'\n';
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>T;
    string s;
    for(int i = 0; i < T;++i){
        cin>>s;
        solve(i,s);
    }
    return 0;
}
