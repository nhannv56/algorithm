/******************************************************************************

https://spoj.com/problems/BOOKS1/
algo: binary search on answer + greedy backwards
TỔNG HỢP VẤN ĐỀ VÀ CÁCH GIẢI:
1. Phương pháp: Binary Search on Answer (Tìm kiếm nhị phân trên kết quả).
   - Tìm số trang sách tối đa `res` mà một người phải chép.
   - Không gian tìm kiếm:
     + left = max(books): Ít nhất một người phải chép cuốn sách dày nhất. 
       LƯU Ý: Nếu set left = 0, hàm check() có thể pass sai, dẫn đến `res` tính ra 
       nhỏ hơn 1 cuốn sách, vòng lặp chia sách sẽ rơi vào Infinite Loop (gây SIGKILL/TLE).
     + right = sum(books): Trường hợp xấu nhất, một người chép tất cả.

2. Yêu cầu "Minimize work assigned to the first scriber":
   - Nghĩa là người xử lý đầu tiên phải nhận phần nhẹ nhất có thể -> Tương đương với 
     ưu tiên nhồi nhét tối đa sức chứa cho những người theo sau.
   - Giải pháp: Tham lam ngược (Greedy Backwards). Duyệt mảng sách từ m-1 về 0.
   - Tại mỗi bước, nếu nhét thêm 1 cuốn mà vượt quá giới hạn `res`, ta đặt 1 vách ngăn `/`.
   - Ràng buộc quan trọng: "Mỗi người ít nhất 1 quyển sách". Khi số quyển sách còn lại 
     vừa đúng bằng số lượng vách ngăn còn lại chưa đặt, bắt buộc phải cắt từng quyển một.

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
long long T, m, k;
long long l = 0, r=0;
bool check(long long len, long long k, vector<long long> &books)
{
    long long cnt = 1, sum = 0;
    for (long long i = 0; i < books.size(); ++i)
    {
        if (sum + books[i] > len)
        {
            ++cnt;
            sum = books[i];
        }
        else
        {
            sum += books[i];
        }
    }
    return cnt <= k;
}

void solve(vector<long long> &books, long long k)
{
    // 
    long long res = r;
    long long mid;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (check(mid, k, books))
        { // all books can copy each copying time <= mid
            res = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    // Assign books: minimize work for earliest scribers
    long long remain = m;
    long long sum = 0;
    int i = m-1;
    int count = 0;
    string output;
    // cout<<"res:"<<res<<endl;
    deque<long long> q;
    while(i >=0){
        while(sum+books[i] <= res ){
            // cout<<"i:"<<i<<" remain:"<<remain<<" count:"<<k - count<<endl;
            q.push_front(books[i]);
            sum+=books[i];
            --i;
            --remain;
            if(remain < k - count){
                // cout<<"violate"<<endl;
                break;
            }
        }
        if(i >= 0){
            q.push_front(-1); // separator
        }
        sum = 0;
        ++count;
    }
    while(!q.empty()){
        auto val = q.front();
        q.pop_front();
        if(val == -1){
            cout << "/ ";
        }else{
            cout << val << " ";
        }
    }
    cout << '\n';
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
        cin >> m >> k;
        vector<long long> books(m);
        l = 0;
        r = 0;

        for (long long i = 0; i < m; ++i)
        {
            cin >> books[i];
            r += books[i];
            l = max(l, books[i]);
        }
        solve(books, k);
        --T;
    }
    return 0;
}
