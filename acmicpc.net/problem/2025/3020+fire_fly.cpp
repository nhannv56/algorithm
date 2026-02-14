/******************************************************************************

https://www.acmicpc.net/problem/27372
algo: slide window

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int N, H;
void sliding(vector<int> & starts, vector<int> & ends){
    int sI = 0;
    int eI = 0;
    int count = 0;
    int result = N;
    int same = 0;
    for(int l = 1; l <= H; ++l){
        while(sI < N &&starts[sI] < l){
            ++count;
            ++sI;
        }
        while(eI < N && ends[eI]< l){
            --count;
            ++eI;
        }
        if(count < result){
            result = count;
            same = 1;
        }else if(count == result){
            ++same;
        }
    }
    cout<<result<<' '<<same<<'\n';
    
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>N>>H;
    int len = 0;
    int s,  e;
    vector<int> starts(N), ends(N);
    
    for(int i = 0; i < N;i++){
        cin>>len;
        if(i % 2 == 0){
            s = 0;
            e = len;
        }else{
            s = H-len;
            e = H;
        }
        starts[i] = s;
        ends[i] = e;
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    sliding(starts, ends);
	return 0;
}