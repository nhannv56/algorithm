/******************************************************************************
https://www.acmicpc.net/problem/24579
algo: binary search
algo: pigeonhole principle

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
//p thời gian mở cửa mỗi ngày
//k số ngày mở cửa
//d số thời gian cần cho 1 người
vector<long long> days(2e5,-1),full(2e5,-1);//ngày bắt đầu, số lần full đã qua

long long solve(vector<long long>& d, long long p, long long k){
    const long long n = d.size();
    vector<long long> prefix(2*d.size(),0);
    //double prefix sum
    //0 1 2 3 4 0 1 2 3 4
    //chỉ số 2n+i = i
    for(int i = 0; i < prefix.size();++i){
        prefix[i] = (i > 0 ?prefix[i-1]:0) + d[(i%n)];
        // cout<<"prefix["<<i<<"]: "<<prefix[i]<<endl;
    }
    long long i = 0, c = 0, m =  0;//i là chỉ số bắt đầu, m la số ngày đã mở cửa, c lần full rehearsal
    long long t = p;// t là thời gian cần check
    bool cycle = false;
    if(t >= prefix[n-1] && t% prefix[n-1]==0){
        return ((long long)(t/prefix[n-1]))*k;
    }
    while( true ){
        //đảm bảo t lớn -> chảy cóc t > hơn 1 vòng
        if(t >= prefix[n-1]){
            c+= (long long)(t/prefix[n-1]);
            t%= prefix[n-1];
        }
        //mốc thời gian tiếp theo cần kiểm tả
        auto target = t+(i>0?(*(prefix.begin()+i-1)):0);

        //binary seach để tìm next student từ i có thể cover
        auto last = upper_bound(prefix.begin()+i, prefix.end(), target);
        if(last != prefix.end()){
            i = distance(prefix.begin(), last);
            //không thể cover hết đến last -> next reset về time = p
            t = p;
            ++m;
            if(i >= n){
                i -= n;
                c++;
            }
            //kiểm tra tìm được vòng
            if(days[i] != -1){
                if(!cycle){//nhảy cóc
                    long long numCycle = (k-m)/(m-days[i]);
                    long long cycleD = numCycle*(m-days[i]);
                    m += cycleD;
                    c+= numCycle*(c-full[i]);
                    cycle = true;
                }

            }else{//cập nhật ngày đầu tiên bắt đầu từ học sinh i nếu lặp lại ->vòng 
                days[i]=m;
                full[i]=c;
            }
            if(m == k){
                // cout<<"c: "<<c<<" m: "<<m<<endl;
                return c;
            }
        }else{
            //bug
        }        
    }        
    return c;
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
    long long n,p,k;
    cin>>n>>p>>k;
    vector<long long> d(n);
    for(int i = 0; i < n; ++i){
        cin>>d[i];
    }
    cout<<solve(d, p, k);
	return 0;
}
