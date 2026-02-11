/******************************************************************************

https://www.acmicpc.net/problem/31856
algo:prefix sum
algo:mono
algo:dp
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int N;
vector<long long> a,b;
vector<long long> prefixA;
long long solve(){
    /**Nhân đôi mảng prefix hiện tại để tính khoảng cách cả ngược chiều kim đồng hồ và xuôi chiều kim đồng hồ
     * 0 - N, 0 -> N
     * Xuôi chiều khi j < N
     * Ngược chiều khi  j >=N (0 -> N-1) circle size - front + prefix j %N
     * 
     * dùng monotonick stack decrease để maintain b[i] + prefixA[j] - prefixA[i] vs prefix b[j] đảm bảo phẩn tử
     * đầu tiên lớn nhất tính đến j
     * \i1       \i2          \i3                 \j
     * -----------------------------------------------
     * so sánh khoảng i3 + distance i3 -> j đảm bảo từ j sẽ lựa chọn được đoạn dài nhất đến j
     * **/
    long long result = 0;
    vector<long long> twoPA = prefixA;
    twoPA.insert(twoPA.end(), prefixA.begin(), prefixA.end());
    //max from 0 to other by left/right
    deque<long long> f;
    f.push_back(0);
    for(int j = 1; j < twoPA.size(); j++)
    {
        int jC = j % N;
        long long lenaij = 0;
        
        //xóa case quá vòng tròn và tìm max in tại i(stack) và out tại j
        while(f.size() > 0){
            if(j < N){
                lenaij = twoPA[jC] - twoPA[f.front()];  
            }else{
                lenaij = twoPA[jC] + twoPA[N] - twoPA[f.front()];
            }
            if(lenaij < prefixA[N]){//satify in 2 point < circle size
                result = max(result, lenaij + b[f.front()]+b[jC]);
               break;
            }else{
                f.pop_front();
            }
        }
        //maintain monotonick stack giảm dần push
        while(f.size()> 0){
            if(j < N){
                lenaij = twoPA[jC] - twoPA[f.back()];  
            }else{
                lenaij = twoPA[jC] + twoPA[N] - twoPA[f.back()];
            }
            if(lenaij + b[f.back()] <= b[jC]){
                f.pop_back();
            }else{
                break;
            }
        }
        f.push_back(jC);
    }
    
    return result;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>> N;
    a = vector<long long>(N);
    b = vector<long long>(N);
    prefixA = vector<long long>(N+1, 0);
    for(int i = 0; i < N; ++i){
        cin>>a[i];
        if(i > 0){
            prefixA[i]= prefixA[i-1]+a[i-1];
            //cout<<"c:"<<i<<" "<<prefixA[i]<<endl;
        }
    }
    prefixA[N] = prefixA[N-1]+a[N-1]; //from N-1 to 0
    //cout<<"c:"<<N<<" "<<prefixA[N]<<endl;
    for(int i = 0; i < N; ++i){
        cin>>b[i];
    }
    cout<<solve();
	return 0;
}