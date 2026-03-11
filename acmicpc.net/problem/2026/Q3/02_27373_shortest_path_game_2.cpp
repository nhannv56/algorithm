/******************************************************************************

https://www.acmicpc.net/problem/27373
algo: dijiktra

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
struct Edge{
    int u,v,w;
};
int T, N, M, Q;
int total=0;
const int INF = 2e8; // Đủ lớn cho hầu hết bài toán
int floydWarshall(int n, vector<vector<int>>& dist /*, vector<vector<int>>& next_node*/) {
    // // next_node dùng để truy vết đường đi
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         if (i == j) dist[i][j] = 0;
    //         if (dist[i][j] < INF && i != j) next_node[i][j] = j;
    //         else next_node[i][j] = -1;
    //     }
    // }

    // 3 vòng lặp O(V^3) - Lưu ý: k phải là vòng lặp ngoài cùng
    if(total!= 0){
        return total;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        // next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }
    }
    // int total = 0;
    for(int i = 0; i <= N; ++i){
        for(int j = i+1; j <=N;++j){
            if(dist[i][j]!=INF){
                total +=dist[i][j];
            }
        }
    }
    return total;
}

int score(deque<Edge>& edges, vector<vector<int>> dist){
    for(auto [cu,cv,cw] : edges){
        dist[cu][cv] = min(dist[cu][cv],cw);
        dist[cv][cu] = min(dist[cu][cv],cw);
    }
    return floydWarshall(N, dist);
    // return total;
}
//dijiktra tìm khoảng cách trước-> tổng
//thêm/xóa 1 cạnh -> cạnh đó ảnh hưởng tới bao nhieu path 
void add(int u, int v, int w,deque<Edge>& edges){
    total=0;
    edges.push_back({u,v,w});
    // cout<<"add:"<<u<<" "<<v<< " "<<w<<endl;
    // Nếu là đồ thị vô hướng và bạn coi cặp (i, j) giống (j, i), hãy chia 2 kết quả.
}

void erase(deque<Edge>& edges){
    total=0;
    if(edges.size()>0){
        edges.pop_back();
    }
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
    cin>>T;
    int u,v,w,r;
    while(T > 0){
        cin>>N>>M>>Q;
        vector<vector<int>> dis(N+1, vector<int>(N+1, INF));
        // for(int i = 1; i <= N; ++i){
        //     dis[i][i]=0;
        // }
        for(int i = 0 ; i < M;++i){
            cin>>u>>v>>w;
            dis[u][v] = min(dis[u][v],w);
            dis[v][u] = min(dis[v][u],w);
        }
       
        deque<Edge> add_edges;
        // auto orgDis = dis;
        total=0;
        for(int i = 0; i < Q;++i){
            cin>>r;
            if(r==1){
                cout<<score(add_edges, dis)<<' ';
            }else if(r==2){
                cin>>u>>v>>w;
                add(u, v, w, add_edges);
            }else{
                erase(add_edges);
            }
        }
        cout<<'\n';
        --T;
    }
	return 0;
}
