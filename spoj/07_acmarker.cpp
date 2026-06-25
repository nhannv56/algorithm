/******************************************************************************

https://spoj.com/problems/ACMAKER/
algo: dp string
algo: dp 4 chiều
mỗi từ đóng góp ít nhất 1 ký tự
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <cctype>
using namespace std;
long long N, Q;
int cal_word(const string &text, const string &target,const int i,const int j, vector<vector<int>>& dp){
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
                    dp[i][j]+= cal_word(text,target,i+1,j+1,dp);
                }
                dp[i][j]+=cal_word(text,target,i+1,j,dp);
            }
        }
        return dp[i][j];
    }else{
        return 0;
    }
}
//tìm số cách ghép target từ text
int dp_word(const string &text, string &target)
{
    int res = 0;
    vector<vector<int>> dp(text.size(), vector<int>(target.size(), -1));
    
    res = cal_word(text, target, 0, 0, dp);
    // cout<<"dp_word: find:"<<target<<" in:"<<text<<" res: "<<res<<"\n";
    return res;
}
int solve(const vector<string> &text, string target, int wi, vector<vector<int>>& dp)
{
    // cout<<"wi: "<<wi<<" target: "<<target<<"\n";
    // if(target.length() > text.size() - wi){
    //     cout<<target<<" case text too short\n";
    //     return 0;
    // }
    if(wi == text.size() -1 && target.length() > 0){
        return dp_word(text[wi], target);//nếu chỉ còn 1 từ cuối cùng thì tìm cách ghép target với từ cuối cùng
    }
    if(dp[wi][target.length()] != -1){//nếu đã tính toán trước đó thì trả về kết quả
        return dp[wi][target.length()];
    }
    int res = 0;
    int maxlen = target.length() - (text.size() - wi -1);
    // cout<<"target: "<<target<<" maxlen: "<<maxlen<<"\n";
    for(int i = 0; i<maxlen; ++i){ //duyệt tất cả các ký tự của target để tìm cách ghép với text[wi]
        string t = target.substr(0, i+1);
        int left = dp_word(text[wi], t);
        if(left > 0){
            res += left * solve(text, target.substr(i+1), wi+1, dp);//tìm cách ghép phần còn lại của target với các từ còn lại
        }
    }
    dp[wi][target.length()] = res;
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
                string ltarget = Target;
                for(int i =0; i<Target.length(); ++i){
                    ltarget[i] = std::tolower(Target[i]);
                }
                vector<string> text;
                while(ss>>word){
                    if(ignoredWords.find(word) == ignoredWords.end()){
                        text.push_back(word);
                    }
                }                
                // cout<<Target<<"\n";
                vector<vector<int>> dp(text.size()+1, vector<int>(ltarget.size()+1, -1));
                int res = solve(text, ltarget, 0, dp);
                if(res > 0){
                    cout<<Target<<" can be formed in "<<res<<" ways\n";
                }else{
                    cout<<Target<<" is not a valid abbreviation\n";
                }
                // cout<<"--------------------------------\n";
            }
        }
    }
    
    return 0;
}
