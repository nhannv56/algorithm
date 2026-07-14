/******************************************************************************

https://codejam.lge.com/problem/17432
Cho N số 1 -> N, và M
thuật toán xếp Insertion Sort
Tìm dãy số mà sau M lần hoán vị thành chuỗi đã sắp xếp
Ý tưởng: Nếu M > N -1
Số lớn nhất cần hoán vị N -1 lần -> bài toán giảm xuống
Xét dãy kích thước N-1 với M -(N-1) lần cần hoán vị tiếp
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long T,N, M;

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
        cin>>N>>M;
        vector<int> nums(N);
        int cur = N;
        int i = 0;
        while(M >= 0 && i < nums.size()){
            if(M >= N-1){
                nums[i]=N;
                M-=(N-1);
                i++;
                N--;
            }else{
                nums[i]=M+1;
                int k = 1;
                ++i;                
                for(; i < nums.size();++i){
                    if(k == M+1){                        
                        k++;
                    }
                    nums[i]=k;
                    ++k;
                }
                M=0;
            }
        }
        for(auto num : nums){
            cout<<num<<' ';
        }
        cout<<'\n';
        --T;
    }
    return 0;
}
