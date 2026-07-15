/******************************************************************************

https://codejam.lge.com/problem/17431
Quy về bài toán ước chung lớn nhất gcd
vì bắt đầu bằng 1,1 xây lên các cặp 
X, và Y số nữa luôn chỉ có gcd là 1 -> xét x là số lớn vì số bước tối thiểu

xét Y là số nhỏ 1-> X/2
Tìm cặp có số bước nhỏ nhất -> đáp án
tỉa nhánh: 
+ cặp có số bước lớn hơn số bước hiện tại -> bỏ qua
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, T;
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> T;
    while(T > 0){
        cin>>N;
        int mid = N/2;
        
        string res = "";
        while(mid > 0){
            string cur = "";
            int a = N, b=mid, c;
            if(gcd(a,b)==1){
                while(a!=b){
                    // cout<<a<<' '<<b<<endl;
                    c = abs(a-b);
                    if(a > b){
                        a = c;
                        cur.push_back('R');
                    }else{
                        b = c;
                        cur.push_back('B');
                    }
                    if(res.length() > 0 && cur.length() >= res.length()){
                        break;
                    }
                } 
                if(res.empty() || res.length() > cur.length()){
                    // cout<<"cur:"<<cur<<endl;
                    res = cur;
                }
            }
            --mid;
        }
        std::reverse(res.begin(), res.end());
        cout<<res<<endl;
        --T;
    }
    return 0;
}
