/******************************************************************************

https://www.acmicpc.net/problem/5904
Divide And Conquer
Recursion

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

long long T,N,K;
long long num[27][3];
//map<long long, long long> skills;//skill, count
void solve(int k, long long n) {
    char res='m';
    while(n - num[k][2] < 0){ // not in range
        --k;
        if(n-num[k][2] == 0){//end of string
            cout<<"o\n";
            return;
        }else if(n-num[k][2] > 0){                  //
            if(n-num[k][2]-num[k+1][1] > 0){
                n-=(num[k][2]+num[k+1][1]);
            }else{
                //mid case
                if(n-num[k][2]==1){
                    cout<<"m\n";
                    return;
                }else{
                    cout<<"o\n";
                    return;
                }
            }
        }
    }
    if(n==1){
        cout<<"m\n";
    }else{
        cout<<"o\n";
    }
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//build S
    num[0][0] = 3; // left and right
    num[0][1] = 0; // mid
    num[0][2] = 3; //sum
    for(long long k = 1; k < 27; ++k){
        num[k][0] = num[k-1][2];
        num[k][1] = 3+k;
        num[k][2] = num[k][0]*2+num[k][1];
        //cout<<"k:"<<k<<" "<<num[k][2]<<"\n";
    }
    
	cin>>N;
	solve(26, N);
	
	return 0;
}