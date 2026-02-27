/******************************************************************************
https://www.acmicpc.net/problem/25779
algo: Nguyên lý Bao hàm - Loại trừ (Inclusion-Exclusion Principle - PIE) kết hợp với Bitmask.
algo: binary search
sub-problem: cho N số nguyên tố,
tổng số các bội số của N số đó <=K đưa ra phương pháp nhanh nhất N<=14 , K<=1e17
Nếu tổng các số nguyên tố lẻ +, chẵn trừ
ví dụ 2,3, 5, 235 +
23,25,35 - 
=> tổng số 30 -> thêm 4 lần, xóa 3 lần
số 6 thêm 2 lần xóa 1 lần
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
set<long long> P;
long long countMultiples(long long N, vector<long long> primes){
    long long res = 0;
    int S = primes.size();
    for(int i = 1; i < (1<<S); ++i){
        long long lcm = 1;
        int bits = 0;
        bool overflow = false;
        for(int j = 0; j < S; ++j){
            if((i>>j)&1){
                bits++;
                //kiểm tra nếu tràn
                if(N / primes[j] < lcm){
                    overflow = true;
                    break;
                }
                lcm*= primes[j];
            }
        }
        if(!overflow){
            if(bits%2 == 1){
                res+=N/lcm;
            }else{
                res-=N/lcm;
            }
        }
    }
    return res;
}
bool satify(const long long& N,long long candidate, vector<long long> & primes){
    
    long long countPrime = countMultiples(candidate, primes);
    
    return (candidate-countPrime >= N);
}
long long solve(long long N,vector<long long> & primes){
    long long res = N, right = 1e18, left = 1;

    long long mid = (left+right)/2;
    while(left <= right){
        mid = (left+right)/2;
        if(satify(N,mid, primes)){
            // cout<<"satify:"<<mid<<endl;
            right = mid-1;
            res = mid;
        }else{
            // cout<<"not satify:"<<mid<<endl;
            left = mid+1;
        }
    }
    return res;
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

    long long N, K;
    cin>>N>>K;
    vector<long long> primes(K);
    for(int i=0;i<K;i++){
        cin>>primes[i];
    }
    auto res =solve(N, primes);
    cout<<res;
	return 0;
}
