/***
 
 */

#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

string s1,s2;
int N;

char solve(const string & q)
{
   char res = 'Y';
   vector<vector<int>> preCal1('r'-'a'+1),preCal2('r'-'a'+1);
   for(int i = 0; i < s1.length();++i){
      preCal1[s1[i]-'a'].push_back(i);
   }
   for(int i = 0; i < s2.length();++i){
      preCal2[s2[i]-'a'].push_back(i);
   }
   set<int> set1,set2;
   for(int i = 0; i < q.length();++i){
      // cout<<"char: "<<q[i]<<endl;
      char c = q[i];
      int cI = c-'a';
      if(preCal1[cI].size() != preCal2[cI].size()){
         return 'N';
      }else{
         for(int j = 0; j < preCal1[cI].size(); ++j){
            // cout<<"preCal1: "<<preCal1[cI][j]<<" preCal2: "<<preCal2[cI][j]<<endl;
            for(auto x: set1){
               // cout<<"set1: "<<x<<" ";
            }
            for(auto x: set2){
               // cout<<"set2: "<<x<<" ";
            }
            auto f1 = set1.lower_bound(preCal1[cI][j]);
            auto f2 = set2.lower_bound(preCal2[cI][j]);
            if(f1 == set1.end() && f2== set2.end()){

            }else{
               // cout<<"dis:"<<distance(set1.begin(),f1)<<" "<<distance(set2.begin(),f2)<<endl;
               if(distance(set1.begin(),f1) != distance(set2.begin(),f2)){
                  return 'N';
               }
            }
            set1.insert(preCal1[cI][j]);
            set2.insert(preCal2[cI][j]);
         }
      }
      
   }
   return res;
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
   cin >> s1 >> s2 >>N;
   string q;
   for (int i = 0; i < N; ++i)
   {
     cin>>q;
     cout<<solve(q);
   }
  
   return 0;
}
