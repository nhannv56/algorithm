/***
 https://www.acmicpc.net/problem/24978
 algo: string
 algo: bitmask
 algo: merge sort
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
void precal(int arr1[], int arr2[],int aSize =0, int mask = 0, int index = 0)
{
   if (index > 17)
   {
      return;
   }
   precal(arr1, arr2, aSize, mask, index + 1);
   int target1[aSize + charIndx1[index].size()], target2[aSize + charIndx1[index].size()];
   int i = 0, k = 0;
   mask |= (1 << index);
   if (charIndx1[index].size() == charIndx2[index].size())
   {
      while (i < aSize && k < charIndx1[index].size())
      {
         if (arr1[i] < charIndx1[index][k] && arr2[i] < charIndx2[index][k])
         {
            target1[i + k] = arr1[i];
            target2[i + k] = arr2[i];
            ++i;
         }
         else if (arr1[i] > charIndx1[index][k] && arr2[i] > charIndx2[index][k])
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
      while (i < aSize)
      {
         target1[i + k] = arr1[i];
         target2[i + k] = arr2[i];
         ++i;
      }
      while (k < charIndx1[index].size())
      {
         target1[i + k] = charIndx1[index][k];
         target2[i + k] = charIndx2[index][k];
         ++k;
      }
      dp[mask] = true;
      precal(target1, target2, aSize + charIndx1[index].size(), mask, index + 1);
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
   int arr1[s1.length()], arr2[s2.length()];
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
