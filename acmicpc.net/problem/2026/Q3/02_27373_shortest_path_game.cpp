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
int total;
const int INF = 2e8; // Đủ lớn cho hầu hết bài toán
void floydWarshall(int n, vector<vector<int>>& dist /*, vector<vector<int>>& next_node*/) {
    // // next_node dùng để truy vết đường đi
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         if (i == j) dist[i][j] = 0;
    //         if (dist[i][j] < INF && i != j) next_node[i][j] = j;
    //         else next_node[i][j] = -1;
    //     }
    // }

    // 3 vòng lặp O(V^3) - Lưu ý: k phải là vòng lặp ngoài cùng
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
}
int countPairsPassingThroughEdge(int u, int v, int w, int n, const vector<vector<int>>& dist) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            
            // Kiểm tra xem cạnh (u, v) có nằm trên lộ trình i -> j không
            if (dist[i][u] + w + dist[v][j] == dist[i][j] || 
                dist[i][v] + w + dist[u][j] == dist[i][j]) {
                count++;
            }
        }
    }
    // Nếu là đồ thị vô hướng và bạn coi cặp (i, j) giống (j, i), hãy chia 2 kết quả.
    return count;
}
int score(stack<int>& totals){
    return totals.top();
}
//dijiktra tìm khoảng cách trước-> tổng
//thêm/xóa 1 cạnh -> cạnh đó ảnh hưởng tới bao nhieu path 
void add(int u, int v, int w,stack<Edge>& edges, stack<vector<vector<int>>>& st,stack<int>& totals){
    
    auto dist = st.top();
    if(w < dist[u][v]){
        if(dist[u][v] != INF){
            // dist[u][v]=w;
            // int reduce = dist[u][v]-w;
            // cout<<"dis:"<<u<<" "<<v<<" d:"<<dist[u][v]<<endl;
            for (int i = 1; i <= N; i++) {
                for (int j = i+1; j <= N; j++) {
                    if (i == j) continue;
                    
                    // Kiểm tra xem cạnh (u, v) có nằm trên lộ trình i -> j không
                    if (dist[i][j] !=INF && dist[i][u] + w + dist[v][j] < dist[i][j] ) {
                        int reduce = dist[i][j] -(dist[i][u] + w + dist[v][j]);
                        total-=reduce;
                        dist[i][j] = dist[i][u] + w + dist[v][j];
                        dist[j][i] = dist[i][u] + w + dist[v][j];
                        // cout<<"reduce:"<<i<<" "<<u<<" "<<v<<" "<<j<<" |"<<dist[i][u]<<" "<<reduce<<" "<<dist[v][j]<<endl;
                    }
                }
            }
        }else{
            // cout<<"case";
            // dist[u][v]=w;
            for (int i = 1; i <= N; i++) {
                for (int j = i+1; j <= N; j++) {
                    if (i == j) continue;
                    
                    // Kiểm tra xem cạnh (u, v) có nằm trên lộ trình i -> j không
                    if(dist[i][u] != INF && dist[v][j]!= INF && dist[i][j]==INF){
                        dist[i][j] = dist[i][u] + w + dist[v][j];
                        dist[j][i] = dist[i][u] + w + dist[v][j];
                        total += dist[i][j];
                        // cout<<"add:"<<i<<" "<<u<<" "<<v<<" "<<j<<" |"<<dist[i][u]<<" "<<w<<" "<<dist[v][j]<<endl;
                    }
                }
            }
        }
    }
    edges.push({u,v,w});
    st.push(dist);
    totals.push(total);
    // Nếu là đồ thị vô hướng và bạn coi cặp (i, j) giống (j, i), hãy chia 2 kết quả.
}

void erase(stack<Edge>& edges, stack<vector<vector<int>>>& st, stack<int>& totals){
    if(edges.size()==0){
        return;
    }
    edges.pop();
    st.pop();
    totals.pop();
    
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
        stack<vector<vector<int>>> sdis;
        for(int i = 1; i <= N; ++i){
            dis[i][i]=0;
        }
        for(int i = 0 ; i<M;++i){
            cin>>u>>v>>w;
            dis[u][v] = min(dis[u][v],w);
            dis[v][u] = min(dis[u][v],w);
        }
        total = 0;
        floydWarshall(N,dis);
        sdis.push(dis);
        for(int i = 1; i < dis.size(); ++i){
            for(int j = i+1; j < dis.size();++j){
                if(dis[i][j]!=INF){
                    total+= dis[i][j];
                }
            }
        }
        stack<Edge> add_edges;
        stack<int> sum;
        sum.push(total);
        auto orgDis = dis;
        for(int i = 0; i < Q;++i){
            cin>>r;
            if(r==1){
                cout<<score(sum)<<' ';
            }else if(r==2){
                cin>>u>>v>>w;
                add(u, v, w, add_edges, sdis,sum);
            }else{
                erase(add_edges, sdis, sum);
            }
        }
        cout<<'\n';
        --T;
    }
	return 0;
}
