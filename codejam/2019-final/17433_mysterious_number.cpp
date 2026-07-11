/******************************************************************************

https://codejam.lge.com/problem/17430
algo: binary search
$A \equiv B \pmod M \iff M \mid (A - B)$
(Nghĩa là: $A$ đồng dư với $B$ theo mô-đun $M$ khi và chỉ khi $M$ là ước của hiệu $A - B$).
Bài toán này không mang tên một định lý riêng biệt (như định lý Fermat hay định lý số dư Trung Hoa), 
mà nó là bài toán kinh điển ứng dụng tính chất của Ước chung lớn nhất (UCLN / GCD) trên các hiệu số.
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, T;
bool sterious(vector<int>& nums, int mod){
    int m = nums[0] % mod;
    for(auto num : nums){
        if(num % mod != m){
            return false;
        }
    }
    return true;
}
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
        vector<int> nums(N);
        int l=1,r= 1e9;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < N;++i){
            cin>>nums[i];
        }
        if(nums[0] == nums[nums.size()-1]){
            cout<<"INFINITY\n";
        }else{
            vector<int> g(N-1);
            for(int i = 1; i < N;++i){
                g[i-1]= nums[i]-nums[i-1];
            }
            int res = g[0];
            for(int i = 1; i < g.size();++i){
                res = gcd(res,g[i]);
            }
            cout<<res<<'\n';
        }
        --T;
    }
    return 0;
}
