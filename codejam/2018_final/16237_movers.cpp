/******************************************************************************

https://codejam.lge.com/submit/16237
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N;


int solve(vector<int> &a)
{
    int res = 0;
    //5
    res+=a[5];
    //4
    res+=a[4];
    if(a[4] >=a[1]){
        a[1]=0;
    }else{
        a[1]-=a[4];
    }
    //3
    res+=a[3];
    int slot = a[3];
    if(a[2] > 0){
        slot -= min(a[3],a[2]);
        a[2] -= a[3]; 
    }
    if(slot > 0){
        a[1]-=slot*2;
    }
    // 2
    if(a[2] > 0){
        res+=a[2]/2;
        if(a[2]%2==0){
            a[1]-=a[2]/2;
        }else{
            res+=1;
            a[1]-=(a[2]/2+3);
        }
    }
    if(a[1] > 0){
        res+=a[1]/5;
        if(a[1]%5!=0){
            ++res;
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
    freopen("output.txt", "w", stdout); 
#endif

    vector<int> items(6,0);
    for(int i = 1; i < 6;++i){
        cin>>items[i];
    }
    cout<<solve(items);
    return 0;
}
