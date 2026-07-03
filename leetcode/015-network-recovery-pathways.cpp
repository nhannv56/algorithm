/**
https://leetcode.com/problems/network-recovery-pathways/?envType=daily-question&envId=2026-07-03
algo: dijiktra
algo: binary search
travel 2 condition min of max
**/
class Solution {
public:
    bool dijiktra(vector<vector<pair<int, int>>>& adj, vector<bool>& online,
                  long long k, int minE) {
        long long n = online.size();

        bool havePath = false;

        vector<long long> dist(n, LLONG_MAX);
        priority_queue<
            pair<long long, long long>,
            vector<pair<long long, long long>>, 
            greater<pair<long long,long long>>
            > pq;
        pq.push({0,0});
        dist[0] = 0;
        while (!pq.empty()) {
            auto [cost, pos] = pq.top();
            pq.pop();
            if (pos == n - 1) {
                havePath = true;
                break;
            }      
            if(cost > dist[pos]){
                continue;
            }      
            for (auto [nc, np] : adj[pos]) {
                long long nRC = cost + nc;
                if (nRC <= k  && nc >=minE && nRC < dist[np]) {
                    pq.push({nRC,np});
                    dist[np] = nRC;
                }
            }
        }
        return havePath;
    }
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online,
                         long long k) {
        long long n = online.size();
        vector<vector<pair<int, int>>> adj(n);
        for (auto e : edges) {
            if (online[e[0]] && online[e[1]]) {
                adj[e[0]].push_back({e[2], e[1]});
            }
        }
        int res = -1;
        int l = 0, r = 1e9, mid;
        while (l <= r) {
            mid = (l + r) / 2;
            if (dijiktra(adj, online, k, mid)) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return res;
    }
};
