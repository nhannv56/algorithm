/******************************************************************************

https://www.acmicpc.net/problem/32956
Mathematics
Binary Search
Parametric Search

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
long long N,M,K;
long long result = 0;
//greater or equal minS
long long countEqualGreater(long long minS,const vector<vector<long long>>& data){

    long long A, B, i;
    long long count = 0;
    
    for(auto it : data){
        A = it[0];
        B = it[1];
        if(B < minS){
            continue;
        }
        i = (B-minS)/A; //[0-i]
        //cout<<"i:"<<i<<endl;
        if(i >= 0){
            count+=(i+1);
        }
        if(count>=K){
            return count;
        }
    }
    return count;
}
long long solve(vector<vector<long long>>& data){
    long long l = 1, r = 1000000000;
    long long mid = (l+r)/2;
    long long count = 0;
    long long minVal = -1;
    while(l <= r){
        mid = (l+r)/2;
        //cout<<"mid:"<<mid<<endl;
        auto curRes = countEqualGreater(mid, data);
        if(curRes >= K ){
            // cout<<"right"<<endl;
            minVal = mid;
            count = curRes;
            l = mid+1;
        }else{
            // cout<<"left"<<endl;
            r = mid-1;
        }
    }
    long long result = 0;
    //long long countEqual = 0;
    long long countGreater = 0;
    for(auto it : data){
        long long A = it[0];
        long long B = it[1];
        long long i = (B - minVal) / A;
        if (B < minVal) continue;
        countGreater += i;
        result += (i * (2*B - (i-1)*A)) / 2;
        if(B - i*A == minVal){
            
        } else {
            countGreater += 1;
            result += B - i*A;
        }
    }
    result += (K - countGreater) * minVal;
    return result;
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>N>>K;
    long long p1, p2;
    long long t;
    long long cMore0 = 0;
    long long sMore0 = 0;
    long long A,B, c;
    vector<vector<long long>> data(N, vector<long long>(2));
    for(int i = 0; i < N;++i){
        cin>>data[i][0]>>data[i][1];
        A = data[i][0];
        B = data[i][1];
        c = B/A; //[0-i]
        cMore0+=(c+1);
        // cout<<A<<" "<<B<<" "<<c<<" +:"<<(c+1)*B - A*c*(c+1)/2<<endl;
        sMore0 +=((c+1)*(2*B - A*c))/2;
    }
    if(cMore0 <= K){
        cout<<sMore0;
    }else{
        cout<<solve(data);
    }
    
	return 0;
}