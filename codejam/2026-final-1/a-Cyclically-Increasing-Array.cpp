2
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, M, T, K;

long long solve(vector<long long> nums)
{

    long long res = LLONG_MAX;
    auto numorg = nums;
    for (long long k = 0; k <= K; ++k)
    {
        long long tres=0;
        nums = numorg;
        for (long long i = 0; i < nums.size(); ++i)
        {           
            if(i==0){
                nums[i] +=k;
                tres+=k;
            }else{
                auto mod = (nums[i-1]+1)%K;
                auto st = max(nums[i], nums[i-1]+1);
                for(auto j = st; j <= st+K;++j){
                    if(j%K==mod){
                        tres+=j-nums[i];
                        nums[i]=j;
                        break;
                    }
                }
            }
        }
        res = min(res, tres);
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

    cin >> T;
    while (T > 0)
    {
        cin >> N >> K;
        vector<long long> num(N, 0);
        for (long long i = 0; i < N; ++i)
        {
            cin >> num[i];
            // cout<<"BC"<<items[i]<<endl;
        }
        cout << solve(num) << endl;
        T--;
    }
    return 0;
}
