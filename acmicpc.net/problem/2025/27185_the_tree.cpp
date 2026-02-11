/******************************************************************************

https://www.acmicpc.net/problem/12055
algo:Trie tree travel
algo:tree xây case nhị phân
merge nếu 2 nhánh con same prefix

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;

int q,c, type, x;
struct Trie{
    int color;
    Trie* l;
    Trie* r;
    Trie(int _color=-1){
        color = _color;
        l=nullptr;
        r=nullptr;
    }
};

Trie * root = new Trie(-1);

int solve(string& path){
   int x=-1;
//    auto parent = root;
   Trie* cur = root;
   for(int i = 0; i < path.length(); ++i){
       if(cur != nullptr){
           if(path[i] == 'R'){
               cur = cur->r;
           }else{
               cur = cur->l;
           }
       }
       if(cur!=nullptr){
           if(cur->color != -1){
               x = cur->color;
           }else{
               if(x != -1){
                   if(path[i] == 'R'){
                       x = (x-1+c)%c;
                   }else{
                       x = (x+1)%c;
                   }
               }
           }
       }else{
           if(x==-1){
               break;
           }
           if(path[i] == 'R'){
               x = (x-1+c)%c;
           }else{
               x = (x+1)%c;
           }
       }
    //    parent = cur;
   }
   return x;
}
void buildTrie(string& path, int color){
    auto cur = root;
    for(int i = 0; i < path.length(); ++i){
        if(path[i] == 'L'){
            if(cur->l == nullptr){
                cur->l = new Trie();
            }
            cur = cur->l;
        }else{
            if(cur->r == nullptr){
                cur->r = new Trie();
            }
            cur = cur->r;
        }
    }
    cur->color = color;
    //update for last path if already colored before
    cur->l = nullptr;
    cur->r = nullptr;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    string path;
    cin>>q>>c;
    for(int i = 0; i < q; ++i){
        cin>>type;
        if(type == 1){
            cin>>x;
            cin>>path;
            buildTrie(path, x);
        }else{
            cin>>path;
            // cout<<"path:"<<path<<endl;
            cout<<solve(path)<<'\n';
        }
    }
	return 0;
}