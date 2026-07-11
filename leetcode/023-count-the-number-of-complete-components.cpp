/**
algo: fullfill
đếm số nhóm mà tất cả các phần tử kết nối trực tiếp tới nhau
**/
class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        int res = 0;
        vector<vector<int>> adj(n);
        for(auto e : edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<bool> visited(n, false);
        for(int i = 0; i < n;++i){
            bool complete = true;
            if(!visited[i]){
                int expectEd = adj[i].size();
                queue<int> q;
                q.push(i);
                int cnt = 1;
                visited[i]=true;
                while(!q.empty()){
                    auto c = q.front();q.pop();
                    // cout<<"at:"<<c<<" size:"<<adj[c].size()<<endl;
                    if(adj[c].size() != expectEd){
                        complete = false;
                    }
                    for(auto ne : adj[c]){
                        if(!visited[ne]){
                            visited[ne]=true;
                            ++cnt;
                            q.push(ne);
                        }
                    }

                }
                if(complete && adj[i].size()==cnt-1){
                    // cout<<"i:"<<i<<endl;
                    res++;
                }
            }
            
        }
        
        
        return res;
    }
};
