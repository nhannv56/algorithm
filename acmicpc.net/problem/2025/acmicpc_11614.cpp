/******************************************************************************
https://www.acmicpc.net/problem/11614
Binary Search
Prefix Sum

*******************************************************************************/
#include <iostream>
#include<vector>
#include <string>
#include<sstream>
#include<string.h>
#include<algorithm>

using namespace std;

int a, b;
string s;
vector<string> words;
vector<int> prefix; //at i store string until word + space 
void solve(const int& len){
    int res = 0;
    auto start = prefix.begin();
    
    int cLen = len;
    
    auto it = upper_bound(start,prefix.end(), cLen);
    //cout<<"solve:"<<cLen<<endl;
    res = words[0].length();
    //cout<<words[0]<<endl;
    while(it != prefix.end()){
        int i = it - prefix.begin();
        //cout<<"solve:w:"<<i<<endl;
        if(words[i] == " "){
            res+=words[i+1].length()+1;
            start = it+1;
            cLen = *it+len;
            //cout<<words[i+1]<<endl;
        }else{
            res+=words[i].length()+1;
            start = it;
            cLen = *it-words[i].length() + len;
            //cout<<words[i]<<endl;
        }
        it = upper_bound(start,prefix.end(), cLen);
    }
    cout<<res<<'\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    std::getline(std::cin,s);
    cin>>a>>b;
    
    stringstream ss(s);
    std::string word;
    //cout<<"s:"<<s<<endl;
    
    while(ss>>word){
        //cout<<word<<endl;
        words.push_back(word);
        words.push_back(" ");
        if(prefix.size()==0){
            prefix.push_back(word.length());
            prefix.push_back(word.length()+1);
        }else{
            prefix.push_back(prefix[prefix.size()-1]+word.length());
            prefix.push_back(prefix[prefix.size()-1]+1);
        }
        //cout<<"pre:"<<prefix[prefix.size()-1]<<endl;
    }
    prefix.pop_back();
    words.pop_back();
    //cout<<"a: "<<a<< " "<<b<<endl;
    
    //memset(::prefix, 0, 500000*sizeof(int));
    for(int i = a; i<=b; i++){
        solve(i);
    }
    
    return 0;
}
