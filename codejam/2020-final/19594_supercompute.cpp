/******************************************************************************

https://codejam.lge.com/problem/19592
algo: priority queue
Với mỗi deadline thì tính xem số over tối thiểu Node( overday, cur deadline, used time, used super)
 N = 3, H = [2, 4, 6], D = [3, 5, 8].
 N: số job
 H thời gian hoàn thành job
 D: Dead line của mỗi job
 tính xem thời gian overdue tối đa
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Custom class / struct (Min-heap theo cost)
struct Node
{
    int cost, d, t, used;

    // Cách 1: Nạp chồng toán tử < bên trong struct
    bool operator<(const Node &other) const
    {
        return cost > other.cost; // Đảo ngược so sánh để thành Min-heap thay vì Max-heap mặc định
    }
};
priority_queue<Node> pq_node1; // Sử dụng toán tử < bên trong cấu trúc Node

// Cách 2: Sử dụng functor (hữu ích cho class Node nếu không muốn đổi toán tử < mặc định)
struct CompareNode
{
    bool operator()(const Node &a, const Node &b)
    {
        return a.cost > b.cost; // Min-heap
    }
};
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
    while (T > 0)
    {
        cin >> N;
        vector<int> H(N), D(1001);
        vector<int> maxH(1001), sum(1001,0);
        int last = 0;
        for (int i = 0; i < N; ++i)
        {
            cin >> H[i];
        }
        int d = 0;
        for (int i = 0; i < N; ++i)
        {
            cin>>d;
            last = max(d,last);
            sum[d] += H[i];
            maxH[d] = max(maxH[d], H[i]);
        }
        // for(int i = 0; i < 10;++i){
        //     cout<<sum[i]<<' ';
        // }cout<<endl;
        int res = 0;
        priority_queue<Node, vector<Node>, CompareNode> pq;

        for (int i = 1; i <= 1000; ++i)
        {
            if (sum[i] > 0)
            {
                if (pq.empty())
                {
                    pq.push({max(0, sum[i] - i), i, sum[i], 0});
                    pq.push({max(sum[i] - maxH[i] +1 - i, 0), i, sum[i] - maxH[i] + 1, 1});
                }
                break;
            }
        }
        while(!pq.empty()){
            auto cur = pq.top(); pq.pop();
            // cout<<"c:"<<cur.cost<<" t:"<<cur.t<<" d:"<<cur.d<<" u:"<<cur.used<<endl;
            if(cur.d == last){
                res = cur.cost;
                break;
            }
            for(int i = cur.d + 1; i <= last;++i){
                if(sum[i] > 0) {
                    int cost = sum[i] + cur.t - i;
                    int t = sum[i]+cur.t;
                    // cout<<"i:"<<i<<" sum:"<<sum[i]<<endl;
                    pq.push({max(cur.cost, cost), i, t,cur.used});
                    // cout<<"push1 d:"<<i<<" c:"<<max(0, cost)<<" t:"<<t<<" u:"<<cur.used<<endl;
                    if(cur.used==0){
                        cost = cur.t+sum[i] - maxH[i] +1- i;
                        t=cur.t+sum[i] - maxH[i] + 1;
                        pq.push({max(cost, cur.cost), i, t, 1});
                        // cout<<"push2 d:"<<i<<" "<<max(cost, 0)<<" t:"<<t<<" u:"<<cur.used<<endl;
                    }
                    break;
                }
            }
        }
        // cout << "res:";
        cout << res << endl;
        --T;
    }
    return 0;
}
