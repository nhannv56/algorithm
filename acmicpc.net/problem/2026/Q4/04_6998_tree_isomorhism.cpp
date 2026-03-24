/******************************************************************************

https://www.acmicpc.net/problem/6998

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
struct Node{
    Node* parent=nullptr;
    vector<Node*> children;
    char val;
};
bool solve(const string & s1, const string & s2){
    Node * r1 = new Node();
    Node * r2 = new Node();
    //build tree
    auto cur = r1;
    for(int i=0;i<s1.length();i+=2){
        if(s1[i] != '#'){
            Node * newNode = new Node();
            newNode->val = s1[i];
            newNode->parent = cur;
            cur->children.push_back(newNode);
            cur = newNode;
        }else{
            cur = cur->parent;
        }
    }
    cur = r2;
    for(int i=0;i<s2.length();i+=2){
        if(s2[i] != '#'){
            Node * newNode = new Node();
            newNode->val = s2[i];
            newNode->parent = cur;
            cur->children.push_back(newNode);
            cur = newNode;
        }else{
            cur = cur->parent;
        }
    }
    // bfs 2 tree to compare
    priority_queue<pair<int,Node*>> q1, q2;
    q1.push({r1->children.size(), r1});
    q2.push({r2->children.size(), r2});
    while(true){
        priority_queue<pair<int,Node*>> q1tmp1, q2tmp2;
        if(q1.size() != q2.size()){
            return false;
        }
        if(q1.empty() && q2.empty()){
            break;
        }
        while(q1.size() > 0){
            auto [d1, node1] = q1.top();
            q1.pop();
            cout<<node1->val<<" "<<d1<<"\n";
            auto [d2, node2] = q2.top();
            q2.pop();
            if(d1!=d2){
                return false;
            }
            for(auto child: node1->children){
                q1tmp1.push({child->children.size(), child});
            }
            for(auto child: node2->children){
                q2tmp2.push({child->children.size(), child});
            }
        }
        if(q1tmp1.size() != q2tmp2.size()){
            return false;
        }else{
            q1=q1tmp1;
            q2=q2tmp2;
        }
    }
    return true;
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
    int T;
    cin >> T;
    while(T--){
        string s1,s2;
        cin >> s1 >> s2;
        auto res = solve(s1,s2);
        if(res==false){
            cout<<"The two trees are not isomorphic.\n";
        }else{
            cout<<"The two trees are isomorphic.\n";
        }
    }
	return 0;
}
