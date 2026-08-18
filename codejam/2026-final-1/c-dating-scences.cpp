
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, M, T;
struct Couple
{
    long long l, r, w;
};
vector<long long> C;
vector<Couple> Intervals;
bool mapPtoInterval(long long cost)
{
    vector<pair<long long, long long>> points(N);
    for(long long i = 0; i < N; i++)
    {
        auto [l, r, w] = Intervals[i];
        
        auto m = cost/(Intervals[i].w);
        auto c1 = (l+r-m+1)/2;// +1 làm tròn lên đảm bảo >=
        auto c2 = (l+r+m)/2;
        points[i] = {c1, c2};

        if((r-l) > m)
        {
            return false;
        }
    }
    // sắp xếp lại theo left
    sort(points.begin(), points.end(),[](const pair<long long, long long> &a, const pair<long long, long long> &b)
    {
        return a.first < b.first;
    });
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    long long idx = 0;
    for(auto c : C)
    {
        while(idx < N && points[idx].first <= c)
        {
            //đẩy right của interval vào pq
            pq.push(points[idx].second);
            idx++;
        }
        // loại bỏ những interval mà right < c không phủ
        while(!pq.empty() && pq.top() < c)
        {
            pq.pop();
        }
        if(pq.empty())
        {
            // không có interval nào phủ c
            return false;
        }
        // chọn interval có right nhỏ nhất để phủ c
        pq.pop();
    }
    return true;
}
long long binary_search(){
    long long l = 0, r = 1e15;
    long long res = r;
    while(l <= r)
    {
        long long mid = (l + r) / 2;
        if(mapPtoInterval(mid))
        {
            r = mid - 1;
            res = mid;
            // cout<<"mid: "<<mid<<endl;
        }
        else
        {
            l = mid + 1;
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
    cin >> N;
    C.resize(N);
    Intervals.resize(N);
    for(long long i = 0; i < N; i++)
    {
        cin >> Intervals[i].l >> Intervals[i].r >> Intervals[i].w;
        if(Intervals[i].l > Intervals[i].r)
        {
            swap(Intervals[i].l, Intervals[i].r);
        }
    }
    for(long long i = 0; i < N; i++)
    {
        cin >> C[i];
    }
    //pre computation
    //sort theo left
    //sort  điểm theo thứ tự
    cout<<binary_search()<<endl;
    return 0;
}
