/******************************************************************************

https://www.acmicpc.net/problem/6998
Bài toán yêu cầu bạn kiểm tra xem hai cây (được biểu diễn dưới dạng chuỗi) 
có đồng cấu (isomorphic) với nhau hay không.

Định nghĩa đồng cấu trong bài này: Hai cây có cấu trúc giống hệt nhau
 nếu ta có thể thay đổi thứ tự các con của một nút để biến cây này thành cây kia. 
 (Lưu ý: Giá trị của các nút không quan trọng, chỉ quan trọng cấu trúc phân nhánh).

Định dạng đầu vào: Chuỗi biểu diễn cây theo thứ tự tiền thứ tự (pre-order).
Mỗi khi gặp ký hiệu #, nghĩa là ta quay ngược lại nút cha (backtrack).

Ví dụ: a b # c # # có nghĩa là a là gốc, b và c là con của a.

Duyệt cây theo từng cấp (tương tự BFS).

Ở mỗi cấp, bạn lấy toàn bộ các nút hiện tại của cả hai cây và bỏ vào hai priority_queue.

Tiêu chí so sánh: Các nút trong hàng đợi được sắp xếp dựa trên số lượng con trực tiếp (children.size()).

Nếu ở bất kỳ cấp nào, "danh sách số lượng con" của Cây 1 khác với Cây 2
 (ví dụ: Cây 1 có một nút 3 con, Cây 2 chỉ có nút 2 con), code sẽ trả về false ngay lập tức.

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
    // cout<<"solve:\n"<<s1<<'\n'<<s2<<'\n';
    Node * r1 = new Node();
    Node * r2 = new Node();
    r1->val=s1[0];
    r2->val=s2[0];
    //build tree
    auto cur = r1;
    for(int i=2;i<s1.length();i+=2){
        // cout<<"s1c:"<<s1[i]<<'\n';
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
    for(int i = 2;i<s2.length();i+=2){
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
    priority_queue<pair<int,Node*>> q1, q2;//lưu số con của node phải tương ứng, pq để order theo thứ tự kiểm tra sớm đk
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
            auto [d2, node2] = q2.top();
            q2.pop();
            // cout<<"tree1:"<<node1->val<<" "<<d1<<"\n";
            // cout<<"tree2:"<<node2->val<<" "<<d2<<"\n";
            if(d1!=d2){
                return false;
            }
            for(auto child: node1->children){
                // cout<<"insert c1:"<<child->val<<'\n';
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
    string s1,s2;
    std::getline(std::cin, s1);
    while(T--){
        std::getline(std::cin, s1);
        std::getline(std::cin, s2);
        auto res = solve(s1,s2);
        if(res==false){
            cout<<"The two trees are not isomorphic.\n";
        }else{
            cout<<"The two trees are isomorphic.\n";
        }
    }
	return 0;
}
