/******************************************************************************

https://www.acmicpc.net/problem/12055
algo:trie
algo:tree

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;
int N,T;
struct Trie{
    bool cur;
    int prefix;
    vector<Trie*> next;
    Trie(bool bit,int pre = -1){
        cur = bit;
        prefix = pre;
        next = vector<Trie*>(2, nullptr);
    }
};
vector<int> stovi(string& sub){
    vector<int> res;
    string cur = "";
    for(int i = 0; i < sub.length(); ++i){
        if(sub[i] == '.'||sub[i] == '/'){
            res.push_back(stoi(cur));
            cur = "";
        }else{
            cur+=sub[i];
        }
    }
    res.push_back(stoi(cur));
    return res;
}
vector<string> travel(const Trie* trie, string cur){
    vector<string> res;
    if(trie != nullptr){
        //cout<<"travel:prefix"<<trie->prefix<<" "<<cur<<endl;
        cur.push_back(trie->cur?'1':'0');
        if(trie->prefix != -1){
            res.push_back(cur);
            return res;
        }
        if(trie->next[0] == nullptr && trie->next[1] == nullptr){
            res.push_back(cur);
            return res;
        }
        
        if(trie->next[0] != nullptr && trie->next[1] != nullptr 
        && trie->next[0]->prefix !=-1 &&trie->next[1]->prefix !=-1){
            // cout<<"cur:"<<cur<<endl;
            res.push_back(cur);
            return res;
        }
        auto l = travel(trie->next[0], cur);
        auto r = travel(trie->next[1], cur);
        if(l.size() == 1 && r.size() == 1 )
        {
            if(l[0].substr(0, l[0].length()-1) == r[0].substr(0,r[0].length()-1)){
                res.push_back(l[0].substr(0, l[0].length()-1));
            }else{
                res.insert(res.end(), l.begin(), l.end());
                res.insert(res.end(), r.begin(), r.end());
            }
        }else
        {
            res.insert(res.end(), l.begin(), l.end());
            res.insert(res.end(), r.begin(), r.end());
        }

    }
    return res;
}
vector<string> solve(vector<string>& subs){
    Trie* root = new Trie(true);
    vector<string> res;
    for(auto sub : subs){
        auto subInt = stovi(sub);
        // cout<<"prefix:"<<subInt[subInt.size()-1]<<endl;
        int ipInt = 0;
        
        int prefix = subInt[subInt.size()-1];
        Trie* cur = root;
        int count = 0;
        string binNum = "";
        for(int i = 0; i < 4; ++i){
            binNum = std::bitset<8>(subInt[i]).to_string();
            if(count >= prefix){
                break;
            }
            // cout<<"num:"<<binNum<<endl;
            for(int j = 0; j < binNum.size(); j++){
                if(count < prefix){
                    int bit1 = (binNum[j] == '1' ? 1:0);
                    // cout<<"at:"<<count<<" "<<bit1<<endl;
                    if(cur->next[bit1] == nullptr){
                        cur->next[bit1] = new Trie(binNum[j]=='1',-1);
                        
                    }
                    if(count == prefix-1) {
                        //cout<<"bit:"<<bit<<" "<<prefix<<endl;
                        cur->next[bit1]-> prefix = prefix;
                    }
                    cur = cur->next[bit1];
                }else{
                    break;
                }
                ++count;
            }
        }
        
    }
    auto s1 = travel(root->next[0], string(""));
    auto s2 = travel(root->next[1], string(""));
    //todo
    res.insert(res.end(),s1.begin(),s1.end());
    res.insert(res.end(),s2.begin(),s2.end());
    return res;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    cin>>T;
    string curMask="";
    string preMask="";
    for(int t = 1; t <= T ;++t){
        cin>>N;
        vector<string> subs(N);
        for(int i = 0; i < N; ++i){
            cin>>subs[i];
        }
        auto res = solve(subs);
        cout<<"Case #"<<t<<":\n";
        
        for(auto m : res){
            //cout<<m<<'\n';
            int cur=0;
            int count = 0;
            for(int i = 0; i < m.length(); i+=8){
                int len = min(8, (int)m.length()-i);
                string num = m.substr(i,len);
                while(num.size() < 8){
                    num.push_back('0');
                }
                cur = std::stoi(num, nullptr, 2);
                cout<<cur;
                if(count < 3){
                    cout<<'.';
                }
                 ++count;
            }
            while(count < 4){
                cout<<"0";
                if(count < 3){
                    cout<<'.';
                }
                ++count;
            }
            cout<<'/'<<m.length()<<'\n';
        }
    }
	return 0;
}