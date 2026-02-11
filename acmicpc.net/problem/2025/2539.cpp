/******************************************************************************

https://www.acmicpc.net/problem/5904
sort
binary search
Parametric Search

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

long long R, C, P, N;
int arr[1000+1][2]={0,};
vector<int> cols;
//Row,Col,Pape number, incorrect cell
int minSquare = 0;

bool covered(int lSquare){
    int cnt = 0;
    if(cols.size() > 0){
        auto it = cols.begin();
        while(it != cols.end()){
            cnt++;
            it = lower_bound(it+1, cols.end(), *it+lSquare);
            if(cnt > P){
                return false;
            }
        }
    }
    
    return true;
}
void resolve() {
    int result = minSquare;
    //cout<<"minSquare:"<<minSquare<<endl;
    int left = minSquare;
    int right = min(R,C);
    int mid;
    while(left <= right){ //1000 -> minSquare O(log(n))
        mid = (left+right)/2;
        if(covered(mid)){
            result = mid;
            right = mid-1;
        }else{
            left = mid+1;
        }
    }
    cout<<result<<'\n';
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>R>>C>>P>>N;
	
	for(int i = 0; i < N;++i){
	    cin>>arr[i][0]>>arr[i][1];
	    minSquare = max(minSquare,arr[i][0]);
	    cols.push_back(arr[i][1]);
	}
	sort(cols.begin(),cols.end());// O(n*log(n))
    auto last = std::unique(cols.begin(), cols.end()); 
    cols.erase(last, cols.end());
	resolve();
	
	return 0;
}