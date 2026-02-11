/******************************************************************************

https://www.acmicpc.net/problem/28312
https://codejam.lge.com/problem/28312
2 lần prefix sum cần build công thức

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int T,N,M;
long long result = 0;

long long distance(long long s, long long e, const vector<long long> & p, const vector<long long> & pp){
    long long res = (e-s)*p[e]-(pp[e-1]-pp[s-1]);
    //cout<<"dis:"<<s<<" "<<e<<" "<<res<<endl;
    return res;
}
bool validate(long long maxDis, const vector<long long> & p,const vector<long long> & pp){

    
    //cout<<"validate:"<<maxDis<<endl;
    int count = 1;
    int cur = 1;
    long long dis = 0;
    int pos = 1;
    for(int s = 1; s < p.size()-1; ){
        dis = 0;
        for(int e = s+1; e < p.size(); e++){
            long long pse = distance(s,e, p,pp);
            dis+=pse;
            if(dis > maxDis){
               // cout<<"invalid:"<<s<<" "<<e<<" "<<dis<<endl;
                s=e;
                dis=0;
                count++;
                if(count > M){
                    return false;
                }
                break;
            }else{
                if(e == p.size()-1){
                    return true;
                }
            }
        }
        
    }
    return true;
}
void binarySearch(long long l, long long r, vector<long long>& data ,vector<long long>& pp){
    long long mid = (l+r)/2;
    while(l <= r){
        mid = (l+r)/2;
        //cout<<"binarySearch:"<<mid<<endl;
        if(validate(mid, data,pp)){
            result = mid;
            r = mid-1;
        }else{
            l=mid+1;
        }
    }
}
long long solve(vector<long long> dis){
   vector<long long> prefix(dis.size(), 0);
   vector<long long> pp(prefix.size(),0);
//   cout<<"solve:"<<N<<" "<<M<<endl;
   if(N==M){
       return 0;
   }else{
       for(int i = 2; i < prefix.size(); ++i){
           prefix[i] = prefix[i-1]+dis[i-1]; //distance from 1 to N
        //   cout<<i<<" "<<prefix[i]<<endl;
       }
       
        for(int i = 1; i < prefix. size(); ++i){
            pp[i] = pp[i-1]+prefix[i];
        }
   }
   long long s = 0;
   long long e = static_cast<long long>(pow(10,20));
   result = e;
   binarySearch(s, e,prefix,pp);
   //cout<<"end\n";
   return result;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>T;
    while(T > 0){
        // cout<<"TC:"<<T<<endl;
        cin>>N>>M;
        vector<long long> d(N+1);
        for(int i = 1; i < N; i++){
            cin>>d[i];
        }
        cout<<solve(d)<<'\n';
        --T;
    }
	return 0;
}