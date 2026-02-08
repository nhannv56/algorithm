/******************************************************************************

https://www.acmicpc.net/problem/34649
string, prefix sum, greedy

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
int T;
//verify anagram sử dụng prefix sum
bool isAnagrams(int s1, int e1, int s2, int e2, vector<vector<int>> & prefix,const string& data){
    if(e1-s1==e2-s2){
        for(int i = 0; i < 26;++i){
            int c1 = prefix[i][e1]- prefix[i][s1] + (data[s1]-'a' == i ? 1:0);
            int c2 = prefix[i][e2]- prefix[i][s2] + (data[s2]-'a' == i ? 1:0);
            if( c1 != c2){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}
int solve(const string &data, vector<vector<int>> &prefix)
{
    auto res = 1;
    
    int s1=0,e1=0,s2=1,e2=1;
    
    while(e2 < data.length()){
        // cout<<data.substr(s1,e1-s1+1)<<" " <<data.substr(s2,e2-s2+1)<<endl;
        if(isAnagrams(s1,e1,s2,e2,prefix,data)){
            ++e2;
        }else{
            s1=s2;
            e1=e2;
            s2=e2+1;
            e2=s2;
            ++res;
        }
    }
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
    cin >> T;
    string data;
    while (T > 0)
    {
        --T;
        cin >> data;
        // build prefix tổng số ký tự từ 0 đến i
        vector<vector<int>> prefix(26, vector<int>(data.length(), 0));
        for (int i = 0; i < data.length(); ++i)
        {
            int jTarget = data[i] - 'a';
            for (int j = 0; j < 26; ++j)
            {
                if (i > 0)
                {
                    prefix[j][i] = prefix[j][i - 1] + (j == jTarget ? 1 : 0);
                }
                else
                {
                    prefix[j][i] = (j == jTarget ? 1 : 0);
                }
                // cout<<prefix[j][i];
            }
            // cout<<endl;
        }
        cout << solve(data, prefix) << '\n';
    }
    return 0;
}