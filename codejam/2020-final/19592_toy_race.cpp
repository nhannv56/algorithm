/******************************************************************************

https://codejam.lge.com/problem/19592
algo: binary search
tìm min time phần còn lại sẽ thắng
tìm min z mà bạn có thể thắng
điều kiện biên
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, T;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> T;
    int N;
    double X,Y;
    while(T > 0){
        cin>>N>>X>>Y;
        double v;
        double maxSpeed = 0;
        for(int i = 0; i < N;++i){
            cin>>v;
            if(i < N-1){
                maxSpeed= max(maxSpeed,v);
            }
        }
        double timeToWin = (double)X/maxSpeed;
        // if(X%maxSpeed !=0){
        //     timeToWin++;
        // }
        // cout<<"Time:"<<timeToWin<<endl;
        // cout<<"v:"<<v<<endl;
        int l = 0, r = Y;
        int mid;
        int res = 0;
        if(Y+v*(timeToWin-1) <= X && v*timeToWin <=X){//không thể thắng case dùng z và ko dùng
            cout<<-1<<endl;
        }else{
            if(v*timeToWin > X){// case ko dùng z và thắng
                cout<<0<<endl;
            }else{
                // cout<<"X:"<<X<<endl;
                while(l<=r){    
                    mid = (l+r)/2;
                    // cout<<"m:"<<mid<<" dis:"<<mid+v*(timeToWin-1)<<endl;
                    if((double)mid + v*(timeToWin-1) > X){
                        res = mid;
                        r = mid-1;
                    }else{
                        l = mid+1;
                    }
                }
                cout<<res<<endl;
            }
        }
        --T;
    }
    return 0;
}
