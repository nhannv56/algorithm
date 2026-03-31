/***

https://www.acmicpc.net/problem/30300
algo: bitmask
algo: adhoc
x luôn có dạng bin là 1,11,111,1111 để đảm bảo luôn sinh ra các số 000,001,010,011,100,...
Vi du neu x la 10 -> ko the sinh ra số 11
-> kiếm tra vs x

00001101 -101
00001011 -011
00101000 -000
00001010 -010
00100001 -001
00010011 -011
**/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
int N;
using namespace std;
void solve(const vector<int> & a){
    int res = 0,x=0;
    int mex = 0;
    // thử tất cả các x có dạng 1,11,111,... để đảm bảo sinh ra tất cả các số 000,001,010,011,100,...
    // tìm max mex có thể sinh ra được
    while(x < (1<<30)){
        vector<bool> counted(N, false);
        x <<= 1;
        x |= 1;
        for(int i = 0; i < N; i++){
            int cur = x & a[i];
            if(cur < N ){
                counted[cur] = true;
            }
        }
        int curMex = 0;
        for(int i = 0; i < N; i++){
            if(counted[i]){
                curMex = i+1;
            }else{
                break;
            }
        }
        if(curMex > mex){
            mex = curMex;
            res = x;
            // cout<<"mex:"<<mex<<'\n';
        }
    }
    cout << res << '\n';
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
    int T;
    cin >> T;
    while(T--){
        cin >> N;
        vector<int> a(N);
        for(int i=0; i<N; i++){
            cin >> a[i];
        }
        solve(a);
    }
	return 0;
}
