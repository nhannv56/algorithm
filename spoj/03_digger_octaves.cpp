/******************************************************************************

https://vn.spoj.com/problems/UCI2009D/
algo: backtracking + bitmask + hash set
TỔNG HỢP VẤN ĐỀ VÀ CÁCH GIẢI
1. Vấn đề: Đếm số cách chọn 8 ô sách (được đánh dấu 'X') sao cho chúng tạo thành một đường đi liên tục (connected path) trên bảng N x N.
2. Phương pháp: Sử dụng backtracking để duyệt tất cả các đường đi có thể, kết hợp với bitmask để lưu trữ trạng thái của các ô đã chọn.
3. Chi tiết giải pháp:
   - Sử dụng một hàm đệ quy `backtrack(i, j, path, visited, books, seen)` để duyệt các đường đi bắt đầu từ ô (i, j).
   - `path` là một bitmask đại diện cho các ô đã chọn trong đường đi hiện tại.
   - `visited` là một mảng boolean để đánh dấu các ô đã được thăm trong quá trình backtracking.
   - Khi số lượng ô đã chọn đạt 8 (kiểm tra bằng `__builtin_popcountll(path) == 8`), ta lưu `path` vào một hash set `seen` để đảm bảo tính duy nhất của các đường đi.
   - Di chuyển theo 4 hướng (lên, xuống, trái, phải) và tiếp tục backtracking nếu ô mới hợp lệ (trong phạm vi, chưa thăm và có 'X').

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
long long T, N;
long long mv[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
void backtrack(int i, int j, long long path, vector<bool> &visited, vector<string> &books, unordered_set<long long> &seen)
{
    long long res = 1;
    visited[i * N + j] = true;
    if (__builtin_popcountll(path) == 8)
    {
        seen.insert(path);
        return;
    }
    for (int d = 0; d < 4; ++d)
    {
        int ni = i + mv[d][0];
        int nj = j + mv[d][1];
        int idx = ni * N + nj;
        if (ni >= 0 && ni < N && nj >= 0 && nj < N && !visited[idx] && books[ni][nj] == 'X')
        {
            visited[idx] = true;
            path |= (1LL << idx);
            backtrack(ni, nj, path, visited, books, seen);
            path &= ~(1LL << idx);
            visited[idx] = false;
        }
    }
    return;
}

long long solve(vector<string> &books)
{
    unordered_set<long long> seen;
    vector<bool> visited(N * N, false);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int idx = i * N + j;
            long long path = 0;
            if (books[i][j] == 'X')
            {
                visited[idx] = true;
                path |= (1LL << idx);
                backtrack(i, j, path, visited, books, seen);
                path &= ~(1LL << idx);
                visited[idx] = false;
            }
        }
    }
    return seen.size();
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
    while (T > 0)
    {
        cin >> N;
        vector<string> books(N);
        for (long long i = 0; i < N; ++i)
        {
            cin >> books[i];
        }
        cout << solve(books) << '\n';
        --T;
    }
    return 0;
}
