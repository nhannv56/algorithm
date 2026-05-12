/***
https://spoj.com/problems/ALICECUB/
algo: dp
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
vector<int> dp(1 << 17, 4);
int T;
int adj[17][4]{
    {0, 0, 0, 0},    // 0
    {2, 3, 5, 9},    // 1
    {1, 4, 6, 10},   // 2
    {1, 4, 7, 11},   // 3
    {2, 3, 8, 12},   // 4
    {1, 6, 7, 13},   // 5
    {2, 5, 8, 14},   // 6
    {3, 5, 8, 15},   // 7
    {4, 6, 7, 16},   // 8
    {1, 10, 11, 13}, // 9
    {2, 9, 12, 14},  // 10
    {3, 9, 12, 15},  // 11
    {4, 10, 11, 16}, // 12
    {5, 9, 14, 15},  // 13
    {6, 10, 13, 16}, // 14
    {7, 11, 13, 16}, // 15
    {8, 12, 14, 15}, // 16
};
void precompute(const int index)
{
    queue<pair<int, int>> q;

    int all_on = 0b11111111;
    q.push({all_on, 0});

    dp[all_on] = 0;

    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        int u_state = curr.first;
        int level = curr.second;

        dp[u_state] = min(dp[u_state], level);
        if (level >= 3) continue;
        // Iterate through all possible swaps
        for (int i = 1; i <= 16; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                int neighbor_vertex = adj[i][j];
                // Check if the two connected vertices have different states
                bool state_i = (u_state >> (i - 1)) & 1;
                bool state_neighbor = (u_state >> (neighbor_vertex - 1)) & 1;

                if (state_i != state_neighbor)
                {
                    // Create new state by swapping (flipping) the two bits
                    int v_state = (u_state ^ ((1 << (i - 1))) | (1 << (neighbor_vertex - 1)));
                    {
                        q.push({v_state, level + 1});
                    }
                }
            }
        }
    }
}

void solve(vector<int> &cubes, int t)
{
    int index = 0;
    for (int i = 0; i < cubes.size(); ++i)
    {
        if (cubes[i] == 1)
        {
            index |= (1 << (15 - i));
        }
    }
    if (dp[index] <= 3)
    {
        cout << "Case #" << t << ": " << dp[index] << "\n";
    }
    else
    {
        cout << "Case #" << t << ": more" << (t != T ? "\n" : "");
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
    
    cin >> T;
    vector<int> cubes(16, 0);
    dp[0b11111111] = 0;
    precompute(0b11111111);
    for (int t = 1; t <= T; ++t)
    {
        for (int i = 0; i < 16; ++i)
        {
            cin >> cubes[i];
        }
        solve(cubes, t);
    }
    return 0;
}
