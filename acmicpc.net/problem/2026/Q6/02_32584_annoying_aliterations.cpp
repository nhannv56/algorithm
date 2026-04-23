/******************************************************************************

https://www.acmicpc.net/problem/12055
algo:trie
algo:tree

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
long long N;
long long cnt = 0;
struct Trie
{
    char _c;
    long long maxLen;
    vector<Trie *> next;
    Trie(char c)
    {
        _c = c;
        maxLen = 0;
        next = vector<Trie *>(26, nullptr);
    }
};
void add(Trie *node, const string &s, long long &len, long long index = 0)
{
    while (index < s.length())
    {
        auto w = s[index];
        auto iW = w - 'a';
        if (node->next[iW] == nullptr)
        {
            auto cur = new Trie(s[index]);
            node->next[iW] = cur;
            //case:
            //aa
            //aabb
            if(cnt>1){
                len = max(len, (long long)s.length()-index);
            }
        }        
        node->next[iW]->maxLen = max(node->next[iW]->maxLen, (long long)s.length() - index);
        // for(long long i = 0; i < 26; ++i){
        //     if(i != iW && node->next[i]!= nullptr){
        //         len = max(len, node->next[iW]->maxLen + node->next[i]->maxLen);
        //     }
        // }
        // case:
        // aaabbb
        // aaa
        if(index == s.length()-1 && node->next[iW]->maxLen > 1&& cnt>1){
            len = max(len, node->next[iW]->maxLen-1);
        }
        node = node->next[iW];
        ++index;
    }
}
void dpOntree(Trie *node, long long &len)
{
    for (long long i = 0; i < 26; ++i)
    {
        if (node->next[i] != nullptr)
        {
            dpOntree(node->next[i], len);
            for (long long j = i + 1; j < 26; ++j)
            {
                if (node->next[j] != nullptr)
                {
                    len = max(len, node->next[i]->maxLen + node->next[j]->maxLen);
                }
            }
        }
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
    cin >> N;
    string s;
    Trie *root = new Trie('A');
    long long res = 0;
    for (long long i = 0; i < N; ++i)
    {
        cin >> s;
        ++cnt;
        add(root, s, res);
    }
    dpOntree(root, res);
    cout << res;
    return 0;
}
