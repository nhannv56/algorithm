/******************************************************************************

brute force, geometry ,Area Of A Polygon

*******************************************************************************/
#include <iostream>
#include<vector>
#include <iomanip>

using namespace std;
int lineSide(pair<float,float> & p1, pair<float, float> & p2, pair<float,float> c){
    auto [x1,y1] = p1;
    auto [x2,y2] = p2;
    auto [x, y] = c;
    if(x1 == x2){
        return (x- x1)/abs(x - x1);
    }else if(y1 == y2){   
        return (y -y1)/abs(y - y1);
    }else{
        int t = (y1 -y2)* x +(x2 -x1)*y -((y1 -y2)* x1 +(x2 -x1)*y1);
        return t/abs(t);
    }
}
int main()
{
    int n;
    int x,y;
    
    //input
    cin>>n;
    vector<pair<float,float>> vetexs = vector<pair<float,float>>(n);
    
    for(int i = 0; i < n; ++i){
        cin>>x>>y;
        vetexs[i].first = x;
        vetexs[i].second = y;
    }
    //order by near vertex
    
    vector<pair<float,float>> vertex_sorted;
    
    vector<bool> visited = vector<bool>(100, false);
    
    vertex_sorted.push_back(pair<float,float>(vetexs[0]));
    visited[0] = true;
    
    //100*100*100
    while(vertex_sorted.size() < vetexs.size()){
        auto firstPoint = vertex_sorted[vertex_sorted.size()-1];
        for(int i = 0; i < n;++i){
            if(!visited[i]){
                visited[i] = true;
                //second point
                auto secondPoint = vetexs[i];
                
                //check other point side
                int side = 0;
                bool isEdge = true;
                for(int j = 0; j < n; j++){
                    if(!visited[j]){
                        //cout<<"line:"<<firstPoint.first<<" "<<firstPoint.second<<","<<secondPoint.first<<" "<<secondPoint.second<<","<<vetexs[j].first<<" "<<vetexs[j].second<<endl;
                        auto jSide = lineSide(firstPoint,secondPoint,vetexs[j]);
                        if(side == 0){
                            side = jSide;
                        }else{
                            if(side != jSide){
                                isEdge = false;
                                break;
                            }
                        }
                    }
                }
                if(isEdge){
                    vertex_sorted.push_back(secondPoint);
                    break;
                }
                visited[i] = false;
            }
        }
    }
    
    //100*100
    //calculation total s of polygon
    //from each point calculation half of polygon and get smallest difference
    float S = 0;
    auto [x1,y1] = vertex_sorted[0];
    for(int i = 2; i  < vertex_sorted.size();i++){
        auto [x2,y2] = vertex_sorted[i-1];
        auto [x3,y3] = vertex_sorted[i];
        S += abs(x1*(y2-y3) + x2*(y3-y1)+x3*(y1-y2))/2;
    }
    // for(auto [x,y]: vertex_sorted){
    //     cout<<x<<" "<<y<<endl;
    // }
    
    // cout<<"S:"<<S<<endl;
    float result  = -1;
    for(int i = 0; i < vertex_sorted.size()-1; i++){
        auto [x1,y1] = vertex_sorted[i];
        float S1 = 0;
        float S2 = 0;
        for(int j = i + 2; j < vertex_sorted.size();++j){
            auto [x2,y2] = vertex_sorted[j-1];
            auto [x3,y3] = vertex_sorted[j];
            S1+= abs(x1*(y2-y3) + x2*(y3-y1)+x3*(y1-y2))/2;
            float S2 = S -S1;
            float diff = abs(S1-S2);
            //cout<<"S1:"<<S1<<",S2:"<<S2<<", diff:"<<diff<<endl;
            if(result == -1){
                result = diff;
            }else{
                result = min(result, diff);
            }
        }
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(1);
    cout<<result<<endl;
    return 0;
}
