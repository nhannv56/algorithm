// prefix sum, sweeping
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k, x1, x2;
    cin >> n >> k;
    long long leaf[n][2];
    long long target[k];
    vector<pair<long long,long long>> starts(n);//first: time s, second: index
    vector<pair<long long,long long>> ends(n);//first: time end, second: index
    //vector<int> se;

    for(long long i = 0; i < n; i++) {
        cin >> x1 >> x2;
        leaf[i][0] = x1;
        leaf[i][1] = x2;
        starts[i].first = x1;
        starts[i].second = i;
        ends[i].first = x2;
        ends[i].second = i;
        //se.push_back(x1);
        //se.push_back(x2);
    }

    for(long long i = 0; i < k; i++) {
        cin >> target[i];
        --target[i]; // Convert to 0-based index
    }
    sort(starts.begin(), starts.end());//The intervals are given in increasing order of their left endpoints – if they are same, then in increasing order of the right endpoints
    sort(ends.begin(), ends.end());
    //sort(se.begin(), se.end());
    //se.erase(unique(se.begin(), se.end()), se.end());
    // for(int i = 0; i < se.size(); i++){
    //     cout<<starts[i]<<" ";
    // }cout<<endl;
    // int finterval = 1;
    long long totalJumps = 0;
    long long sI = 0;
    long long eI = 0;
    long long seI = 0;
    //unordered_set<long long> achieved;
    //achieved.insert(1);
    
    int achieved = 1;    
    long long xFrog = leaf[0][0];
    vector<long long> prefix(n, 0);
    //int xTarget = leaf[1][0];

    for(long long i = 1; i < n; i++) {
        const long long startI = leaf[i][0];
        //push start time less than startI

        while(eI < ends.size() && ends[eI].first < startI){
            --achieved;
            xFrog = ends[eI].first;
            eI++;
        }
        if(achieved==0){
            //cout<<"i:"<<i <<" "<< startI<<" "<<xFrog<<endl;
            prefix[i] = prefix[i-1]+ startI - xFrog;
        }else{
            prefix[i] = prefix[i-1];
        }
        
        ++achieved;
       // cout<<"i:"<<i<<" "<<prefix[i]<<" "<<endl;
        
    }
    totalJumps+= abs(prefix[0] - prefix[target[0]]);
    
    for(long long i = 1 ; i < k;i++){
        totalJumps+=abs(prefix[target[i]] - prefix[target[i-1]]);
       // cout<<"from:"<<target[i-1]<<" to:"<<target[i]<<" "<<totalJumps<<endl;
    }
    cout<<totalJumps<<endl;
    return 0;
}
