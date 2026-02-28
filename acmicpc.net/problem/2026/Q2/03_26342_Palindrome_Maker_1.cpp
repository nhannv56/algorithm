/******************************************************************************
https://www.acmicpc.net/problem/26342
algo:lcs

Tìm lcs longest common subsequence từ 2 chuỗi cho sẵn và i-j không quá 100
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

int lenlcs(vector<int>& s1, vector<int> &s2){
    int m = s1.size();
    int n = s2.size();
    
    // Sử dụng 2 dòng để tiết kiệm bộ nhớ
    vector<int> prev(n + 1, 0);
    vector<int> curr(n + 1, 0);
    int band = 100; // Vì đề bài giới hạn tối đa 99 chỗ chèn
    for (int i = 1; i <= m; i++) {
       //xóa sạch dòng hiện tại để không dính rác từ i-1
        fill(curr.begin(), curr.end(), 0);

        int start = max(1, i - band);
        int end = min(n, i + band);

        for (int j = start; j <= end; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                // j-1 có thể nằm ngoài band (khi đó curr[j-1] đã được reset về 0 ở trên)
                curr[j] = max(prev[j], (j > start ? curr[j - 1] : 0));
            }
        }
        prev = curr; // Cập nhật dòng cũ cho lần lặp kế tiếp
    }

    return prev[n];
}
int solve(vector<int>& l1){
    auto l2 = l1;
    
    reverse(l1.begin(), l1.end());
   
    return l1.size()-lenlcs(l1,l2);
    
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

    int N, K;
    cin>>N;
    for(int i = 1; i <= N; ++i){
        cin>>K;
        vector<int> arr(K);
        for(int j =0; j < K;++j){
            cin>>arr[j];
        }
        auto res =solve(arr);
        cout<<"Sequence #"<<i<<": "<<res<<"\n\n";
    }
	return 0;
}