/******************************************************************************
https://www.acmicpc.net/problem/15770
algo: dp
Dùng dp để lưu đoạn từ i->j có phải là palidrome ko -> đoạn i-1 và j+1 có phải palindrome không
dùng index theo character đề lưu lại các điểm trước đó trùng lặp với điểm đang duyệt 
-> có khả năng là palindrome
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long N;

void solve(string & q,vector<vector<bool>>& dp){
    string cur = "";
    vector<vector<int>> cIndexs(27);// lưu lại index cùng ký tự để kiểm tra potential palindrome
    vector<int> res;
    for(int i = 0; i < q.length();++i){
        if(q[i]!='-'){
            cur.push_back(q[i]);
            res.push_back(res.size() > 0 ?res.back():0);
            
            int r = cur.length()-1;
            int cI = q[i]-'a';
            cIndexs[cI].push_back(r);
            dp[r][r]=true;
            // cout<<cur<<endl;
            for(auto l: cIndexs[cI]){
                if(l==r||l+1==r||dp[l+1][r-1] == true){     //là palindrome l->r               
                    ++res[res.size()-1];
                    dp[l][r]=true;
                }else{
                    dp[l][r] = false;
                }
            }
        }else{
            if(cur.length()>0){
                auto removeC = cur.back()-'a';cur.pop_back();
                res.pop_back();
                // fill(dp[cur.length()].begin(), dp[cur.length()].end(), false);
                int r = cIndexs[removeC].back();
                for(auto l : cIndexs[removeC]){// cập nhật dp khi 1 kí tự r bị xóa -> đoạn l->r ko còn là palindrome
                    dp[l][r] = false;
                }
                cIndexs[removeC].pop_back();
            }
        }
        if(res.size() > 0){
            cout<<res.back()<<" ";
        }else{
            cout<<0<<" ";
        }
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
    cin>>N;
    string q;
    cin>>q;
    vector<vector<bool>> dp(N, vector<bool>(N,false));
    solve(q, dp);
	return 0;
}
