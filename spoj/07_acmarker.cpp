/******************************************************************************

https://spoj.com/problems/ACMAKER/
algo: dp
viết lại dp vì mỗi chữ cần đóng góp it nhất 1 ký tự
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <cctype>
using namespace std;
long long N, Q;
int cal(const string &text, const string &target,const int i,const int j, vector<vector<int>>& dp){
    if(i < text.size() && j < target.size()){
        if(dp[i][j] == -1){
            if(i == text.length()-1 && j == target.length()-1){
                if(text[i] == target[j]){
                    return 1;
                }else{
                    return 0;
                }
            }else{
                dp[i][j]=0;
                if(j == target.size()-1 && text[i]==target[j]){
                    dp[i][j]++;
                }
                if(text[i]==target[j]){
                    dp[i][j]+= cal(text,target,i+1,j+1,dp);
                }
                dp[i][j]+=cal(text,target,i+1,j,dp);
            }
        }
        return dp[i][j];
    }else{
        return 0;
    }
}
void solve(const string &text, string &target)
{
    int res = 0;
    vector<vector<int>> dp(text.size(), vector<int>(target.size(), -1));
    std::transform(target.begin(), target.end(), target.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    res = cal(text, target, 0, 0, dp);

    if(res == 0){
        cout<<target<<" is not a valid abbreviation\n";
    }else{
        cout<<target<<" can be formed in "<<res<<" ways\n";
    }
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
    while(true){
        string ns;
        std::getline(std::cin, ns);
        N = stoi(ns);
        if(N == 0) break;
        set<string> ignoredWords;
        string w;
        for(int i =0; i<N; ++i){
            std::getline(std::cin, w);
            ignoredWords.insert(w);
        }
        std::string line;
        while(true){
            std::getline(std::cin, line);
            if(line == "LAST CASE"){
                break;
            }else{
                stringstream ss(line);
                string Target,word;
                ss>> Target;
                string text="";
                while(ss>>word){
                    if(ignoredWords.find(word) == ignoredWords.end()){
                        text+=word;
                    }
                }                
                cout<<text<<" "<<Target<<"\n";
                solve(text, Target);
            }
        }
    }
    
    return 0;
}
