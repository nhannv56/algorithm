/***
 https://www.acmicpc.net/problem/24978
 */

#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

string s1, s2;
int N;
int MAX_Q_LEN = 'r' - 'a' + 1;
vector<vector<int>> charIndx1(MAX_Q_LEN), charIndx2(MAX_Q_LEN); //
vector<bool> dp(1 << 19, false);
vector<int> arr1, arr2;
void precal(vector<int> &vt1, vector<int> &vt2, int mask = 0, int index = 0)
{
   if (index > 17)
   {
      return;
   }
   precal(vt1, vt2, mask, index + 1);
   vector<int> target1(vt1.size() + charIndx1[index].size()), target2(vt1.size() + charIndx1[index].size());
   int i = 0, k = 0;
   mask |= (1 << index);
   if (charIndx1[index].size() == charIndx2[index].size())
   {
      while (i < vt1.size() && k < charIndx1[index].size())
      {
         if (vt1[i] < charIndx1[index][k] && vt2[i] < charIndx2[index][k])
         {
            target1[i + k] = vt1[i];
            target2[i + k] = vt2[i];
            ++i;
         }
         else if (vt1[i] > charIndx1[index][k] && vt2[i] > charIndx2[index][k])
         {
            target1[i + k] = charIndx1[index][k];
            target2[i + k] = charIndx2[index][k];
            ++k;
         }
         else
         {
            return;
         }
      }
      // push remain item don't need compare
      while (i < vt1.size())
      {
         target1[i + k] = vt1[i];
         target2[i + k] = vt2[i];
         ++i;
      }
      while (k < charIndx1[index].size())
      {
         target1[i + k] = charIndx1[index][k];
         target2[i + k] = charIndx2[index][k];
         ++k;
      }
      dp[mask] = true;
      precal(target1, target2, mask, index + 1);
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
   cin >> s1 >> s2 >> N;

   for (int i = 0; i < s1.length(); ++i)
   {
      charIndx1[s1[i] - 'a'].push_back(i);
   }
   for (int i = 0; i < s2.length(); ++i)
   {
      charIndx2[s2[i] - 'a'].push_back(i);
   }
   string q;
   precal(arr1, arr2);
   for (int i = 0; i < N; ++i)
   {
      cin >> q;
      int mask = 0;
      for (int j = 0; j < q.length(); ++j)
      {
         mask |= (1 << (q[j] - 'a'));
      }
      cout << (dp[mask] ? 'Y' : 'N');
   }

   return 0;
}
