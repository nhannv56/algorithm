/******************************************************************************

https://www.acmicpc.net/problem/1068
algo:Graph Theory
algo:Graph Traversal
algo:Tree
algo:dfs

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int N;
struct Node{
    int val;
    deque<Node*> childs;
    Node(int value){
        val = value;
    }
};

vector<Node*> vt(50, nullptr);
Node* root = nullptr;
int toRM;

void bfs(){
    int result = 0;
    deque<Node*> dq;
    dq.push_back(root);
    
    //bfs travel
    while(!dq.empty()){
        auto cur = dq.front();dq.pop_front();
        if(cur != nullptr && cur->val != toRM){
            if(cur->childs.size() == 0){
                result+=1;
            }else if(cur->childs.size()==1){
                if(cur->childs.front()->val == toRM){
                    // if(cur !=root) //is root like a leaf
                    {
                        result+=1;
                    }
                }else{
                    dq.push_back(vt[cur->childs.front()->val]);
                }
            }else{
                for(auto c : cur->childs){
                    if(c != nullptr && c->val != toRM){
                        dq.push_back(vt[c->val]);
                    }
                }
            }
        }
        
    }
    cout<<result;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>N;
    int p=0;
    for(int i = 0; i < N; i++){
        cin>>p;
        //init cur
        if(vt[i] == nullptr){
            Node* cur = new Node(i);
            vt[i] = cur;
        }
        if(p == -1){
            root = vt[i];
        }else{
            if(vt[p] == nullptr){
                Node* parent = new Node(p);
                vt[p] = parent;
            }
            //link to parent
            vt[p]->childs.push_back(vt[i]);
        }
    }
    cin>>toRM;
    bfs();
	return 0;
}