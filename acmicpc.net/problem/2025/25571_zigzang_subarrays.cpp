/******************************************************************************

https://www.acmicpc.net/problem/25571

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
long long T,N,M;
enum Case{
    NONE,UP, DOWN
};
long long resolve(vector<long long> & A){
    long long result = 0;
    long long i = 0, j = 1;
    Case type = NONE;
    while(j < A.size()){
        if(A[j-1] == A[j]){ //NONE
            i = j;
            type = NONE;
        }else if(A[j-1] < A[j]){ //UP
            if(type == UP){
                i = j-1;
                ++result;
            }else{
                result+= j-i;
            }
            type = UP;
        }else{ //DOWN
            if(type == DOWN){
                i = j-1;
                ++result;
            }else{
                result+= j-i;
            }
            type = DOWN;
        }
        ++j;
    }
    return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>T;
    
    for(long long t = 0; t < T; t++){
        cin>>N;
        vector<long long> data(N);
        for(long long i = 0; i < N; ++i){
            cin>>data[i];
        }
        cout<<resolve(data)<<'\n';
    }
	return 0;
}