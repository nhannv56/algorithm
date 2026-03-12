/******************************************************************************

https://www.acmicpc.net/problem/27373
algo: dijiktra

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
struct Edge{
    long long u,v,w;
};
long long T, N, M, Q;
long long total;
const long long INF = 2e8+1; // Đủ lớn cho hầu hết bài toán
void floydWarshall(long long n, vector<vector<long long>>& dist /*, vector<vector<long long>>& next_node*/) {
    // // next_node dùng để truy vết đường đi
    // for (long long i = 1; i <= n; i++) {
    //     for (long long j = 1; j <= n; j++) {
    //         if (i == j) dist[i][j] = 0;
    //         if (dist[i][j] < INF && i != j) next_node[i][j] = j;
    //         else next_node[i][j] = -1;
    //     }
    // }

    // 3 vòng lặp O(V^3) - Lưu ý: k phải là vòng lặp ngoài cùng
    for (long long k = 1; k <= n; k++) {
        for (long long i = 1; i <= n; i++) {
            for (long long j = 1; j <= n; j++) {
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

long long score(stack<long long>& totals){
    return totals.top();
}
//dijiktra tìm khoảng cách trước-> tổng
//thêm/xóa 1 cạnh -> cạnh đó ảnh hưởng tới bao nhieu path 
void add(long long u, long long v, long long w,stack<Edge>& edges, stack<vector<vector<long long>>>& st,stack<long long>& totals){
    
    auto dist = st.top();
    if(w < dist[u][v]){
        // dist[u][v]=w;
        // long long reduce = dist[u][v]-w;
        // cout<<"dis:"<<u<<" "<<v<<" d:"<<dist[u][v]<<endl;
        for (long long i = 1; i <= N; i++) {
            for (long long j = i+1; j <= N; j++) {
                if (i == j) continue;
                
                // Kiểm tra xem cạnh (u, v) có nằm trên lộ trình i -> j không
                if (dist[i][u] + w + dist[v][j] < dist[i][j] ) {
                    if(dist[i][j]!=INF){
                        long long reduce = dist[i][j] -(dist[i][u] + w + dist[v][j]);
                        total-=reduce;
                    }else{
                        total+=(dist[i][u] + w + dist[v][j]);
                    }
                    dist[i][j] = dist[i][u] + w + dist[v][j];
                    dist[j][i] = dist[i][u] + w + dist[v][j];
                    // cout<<"reduce:"<<i<<" "<<u<<" "<<v<<" "<<j<<" |"<<dist[i][u]<<" "<<reduce<<" "<<dist[v][j]<<endl;
                }else if (dist[i][v] + w + dist[u][j] < dist[i][j] ) {
                    if(dist[i][j]!=INF){
                        long long reduce = dist[i][j] -(dist[i][v] + w + dist[u][j]);
                        total-=reduce;
                    }else{
                        total+=(dist[i][v] + w + dist[u][j]);
                    }
                    dist[i][j] = dist[i][v] + w + dist[u][j];
                    dist[j][i] = dist[i][v] + w + dist[u][j];
                    // cout<<"reduce:"<<i<<" "<<u<<" "<<v<<" "<<j<<" |"<<dist[i][u]<<" "<<reduce<<" "<<dist[v][j]<<endl;
                }
            }
        }
    }
    edges.push({u,v,w});
    st.push(dist);
    totals.push(total);
    // Nếu là đồ thị vô hướng và bạn coi cặp (i, j) giống (j, i), hãy chia 2 kết quả.
}

void erase(stack<Edge>& edges, stack<vector<vector<long long>>>& st, stack<long long>& totals){
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
    long long u,v,w,r;
    while(T > 0){
        cin>>N>>M>>Q;
        vector<vector<long long>> dis(N+1, vector<long long>(N+1, INF));
        // long long dis[100][100];
        stack<vector<vector<long long>>> sdis;
        for(long long i = 1; i <= N; ++i){
            dis[i][i]=0;
        }
        for(long long i = 0 ; i<M;++i){
            cin>>u>>v>>w;
            dis[u][v] = min(dis[u][v],w);
            dis[v][u] = min(dis[u][v],w);
        }
        total = 0;
        floydWarshall(N,dis);
        sdis.push(dis);
        for(long long i = 1; i < dis.size(); ++i){
            for(long long j = i+1; j < dis.size();++j){
                if(dis[i][j]!=INF){
                    total+= dis[i][j];
                }
            }
        }
        stack<Edge> add_edges;
        stack<long long> sum;
        sum.push(total);
        auto orgDis = dis;
        for(long long i = 0; i < Q;++i){
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
