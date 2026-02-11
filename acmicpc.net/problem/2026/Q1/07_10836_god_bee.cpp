/******************************************************************************

https://www.acmicpc.net/problem/27361
algo:prefix sum
Index   0	1	2	3	4	5	6
U1      0	0	0	0	0	0	0  tại điểm + thêm
U2      0	0	1	0	0	1	0

Filled   1	0	1	0	0	1	1

Prefix	1	1	2	2	2	3   4
Bắt đầu từ điểm nào thì sẽ +1

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int N,M;


int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>M>>N;
	vector<vector<int>> arr(M, vector<int>(M, 1));
	vector<int> base(M*2-1, 0);
	int c0,c1,c2;
	//build prefix sum từ c1 +1 từ c2+2
	for(int i = 0; i < N; ++i){
	   cin>>c0>>c1>>c2;
	   ++base[c0];//từ index c0 thì các phần tử sẽ +1
	   ++base[c0+c1]; //từ index c0+c1 các phần tử sẽ +2 ( theo prefix sẽ bao gồm c1)
	}
	int bI = 0;
	int cur = 0;
	//sử dụng tính arr trái và phía trên
    for(int i = M-1; i >=0; --i){
        cur+= base[bI];//prefix sum tại bI
        arr[i][0]=cur+1;//tính dưới lên
        ++bI;
    }
    for(int i=1; i < M; ++i){
        cur+= base[bI];//prefix sum tại bI
        arr[0][i]= cur+1;//tính trái -> phải
        ++bI;
    }
    //tính các item còn lại
    for(int i = 1; i < M;++i){
        for(int j = 1; j < M; ++j){
            arr[i][j] = max({arr[i-1][j], arr[i-1][j-1], arr[i-1][j]});
        }
    }
    //in
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < M;++j){
            cout<<arr[i][j]<<' ';
        }
        cout<<'\n';
    }
	return 0;
}