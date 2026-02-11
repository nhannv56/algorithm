/******************************************************************************

https://www.acmicpc.net/problem/12055
algo:dp
algo:prefix sum
algo:prime
algo:game

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int T;
vector<int> primes;
vector<int> winner(100000, -1);
void buildPrimes(int N){
    vector<int> check(N+1, true);
    for(int i = 2; i <= N; i++){
        if(check[i] == true){
           // cout<<i<<' ';
            primes.push_back(i);
            for(int j = 1; j*i <= N; ++j){
                check[j*i]= false;
            }    
        }
    }
    //cout<<endl;
}
bool isWin(int N){
    if(N == 0 || N == 1){
        return false;
    }
    if(winner[N] == -1){
        for(int i = 0; i < primes.size() && primes[i] <= N; i++){
            if(!isWin(N-primes[i])){// next turn cannot win so current turn win
                winner[N] = 1;         
                break;
            }
        }
        if(winner[N]==-1){
            winner[N] = 0;               
        }
    }
    return winner[N] == 1 ? true : false;
}
pair<int,int> solve(int A, int k){
    //cout<<"is win:"<<isWin(10)<<endl;
    int xRange = A+1-k;
    int bobWin = 0, minXBW = INT_MAX;
    int totalGame = 0;
    //slide window: size k with n from x to x+k-1 to minimize for O(n)
    int curBobWin = 0;
    for(int n = 2 ; n <= 2+k-1; n++){
        if(!isWin(n)){//verify alice can win or not
            ++curBobWin;
            //cout<<"bob win:"<<n<<endl;
        }    
    }
    bobWin = curBobWin;
    minXBW = 2;
    for(int x = 3; x <= xRange; ++x){// x range
        if(!isWin(x-1)){
            --curBobWin;
        }
        if(!isWin(x+k-1)){
            ++curBobWin;
        }
        //update result
        if(curBobWin > bobWin){
            bobWin = curBobWin;
            minXBW = x;
        }else if(curBobWin == bobWin) {
            minXBW = min(minXBW, x);
        }
    }
    
    return {bobWin, minXBW};
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>T;
    int A, k;
    buildPrimes(100000);
    for(int t = 1; t <=T ;++t){
        cin>> A>>k;
        auto [winCount, minX] = solve(A, k);
        
        cout<<winCount<<" "<<minX<<endl;
    }
	return 0;
}