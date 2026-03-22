/******************************************************************************
https://www.acmicpc.net/problem/8895
algo: dp
Nếu đặt thanh gỗ 1 ở ngoài cùng bên trái: Nó sẽ luôn được nhìn thấy từ bên trái $\rightarrow$ 
=>Bài toán trở thành xếp $n-1$ thanh còn lại với $(l-1, r)$.
Nếu đặt thanh gỗ 1 ở ngoài cùng bên phải: Nó sẽ luôn được nhìn thấy từ bên phải $\rightarrow$ 
=>Bài toán trở thành xếp $n-1$ thanh còn lại với $(l, r-1)$.
Nếu đặt thanh gỗ 1 ở giữa ($n-2$ vị trí): Nó sẽ bị che khuất từ cả hai phía $\rightarrow$ 
=>Bài toán trở thành xếp $n-1$ thanh còn lại với $(l, r)$ và nhân với $(n-2)$ cách đặt.
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long T,n, l, r;
vector<vector<vector<long long>>> dp(21, vector<vector<long long>>(21,vector<long long>(21,-1)));
long long pre[21];
long long solve(long long n, long long l, long long r){
    //khi n và (l|r)giảm
    if(n==0||(l+r>n+1)||l>n|r>n){
        return 0;
    }
    // điều kiện check cho chỉ giảm n
    //chọn l-1 phần tử bên trái C(l-1)(n-1) phần tử xếp bên trái
    //phần tử cao nhất ở giữa
    //bên trái không có lựa chọn
    if(l+r==n+1){
        return pre[n-1]/(pre[n -1 -(l-1)]*pre[l-1]);
    }
   
    if(dp[n][l][r] == -1){
        long long res = 0;
        if(l>1)res+=solve(n-1,l-1, r);
        if(r>1)res+=solve(n-1, l, r-1);
        if(n>2)res+=(n-2)*solve(n-1,l,r);
        dp[n][l][r]=res;
    }
    return dp[n][l][r];
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
    cin>>T;
    pre[0]=1;
    for(long long i = 1; i < 21;++i){
        pre[i]=i*pre[i-1];
    }
    while(T > 0){
        cin>>n>>l>>r;
        if(l+r>n+1){
            cout<<"0\n";
        }else{
            cout<<solve(n, l, r)<<'\n';
        }
        --T;
    }
	return 0;
}
