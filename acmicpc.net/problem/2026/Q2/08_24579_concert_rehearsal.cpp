/******************************************************************************
https://www.acmicpc.net/problem/24579
Bài toán: n học sinh xếp hàng vòng tròn, mỗi ngày phòng mở p đơn vị thời gian.
Học sinh i cần d[i] thời gian. Mỗi ngày tập từ học sinh tiếp theo sau ngày hôm trước.
Hỏi sau k ngày có bao nhiêu lần full rehearsal (đi qua hết vòng)?

algo: binary search (tìm học sinh cuối được phục vụ mỗi ngày)
algo: cycle detection (pigeonhole: sau tối đa n ngày sẽ lặp lại vị trí bắt đầu)
*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;
// p: thời gian mở cửa mỗi ngày
// k: số ngày mở cửa (cần tính)
// d: thời gian cần cho từng học sinh

// days[i]: ngày đầu tiên (m) mà phiên bắt đầu tại học sinh i (dùng để phát hiện chu kỳ)
// full[i]: số lần full rehearsal tương ứng khi days[i] được ghi nhận
vector<long long> days(2e5,-1), full(2e5,-1);

long long solve(vector<long long>& d, long long p, long long k){
    const long long n = d.size();

    // Bước 1: Xây dựng prefix sum nhân đôi (mảng vòng tròn)
    // prefix[i] = tổng d[0..i%n] trên mảng kép, giúp xử lý wrap-around
    // Ví dụ n=5: chỉ số 0..4 là vòng 1, chỉ số 5..9 là vòng 2 (= vòng 1 lặp lại)
    vector<long long> prefix(2*d.size(), 0);
    for(int i = 0; i < (int)prefix.size(); ++i){
        prefix[i] = (i > 0 ? prefix[i-1] : 0) + d[(i % n)];
    }

    // i: chỉ số học sinh bắt đầu phiên hôm nay (trong prefix kép)
    // m: số ngày đã tổ chức (phiên)
    // c: số lần full rehearsal đã hoàn thành
    long long i = 0, c = 0, m = 0;
    long long t = p; // thời gian còn lại của phiên hiện tại
    bool cycle = false; // đã nhảy chu kỳ hay chưa (chỉ nhảy 1 lần)

    // Bước 2: Trường hợp đặc biệt - p đủ lớn để đi hết >= 1 vòng mỗi ngày
    // => mỗi ngày hoàn thành đúng (p / tổng_1_vòng) lần full rehearsal
    if(t >= prefix[n-1] && t % prefix[n-1] == 0){
        return ((long long)(t / prefix[n-1])) * k;
    }

    while(true){
        // Bước 3: Nếu t vẫn >= tổng 1 vòng, cuộn bớt full rehearsal
        // (tránh tìm kiếm trên mảng kép khi t span nhiều vòng)
        if(t >= prefix[n-1]){
            c += (long long)(t / prefix[n-1]);
            t %= prefix[n-1];
        }

        // Bước 4: Tính mốc thời gian tuyệt đối trên prefix kép
        // target = prefix[i-1] + t: điểm kết thúc tối đa của phiên hôm nay
        auto target = t + (i > 0 ? (*(prefix.begin() + i - 1)) : 0);

        // Bước 5: Binary search - tìm học sinh cuối cùng được phục vụ hôm nay
        // upper_bound trả về iterator đến phần tử đầu tiên > target
        // => học sinh [i .. last-1] được phục vụ, phiên mai bắt đầu tại last
        auto last = upper_bound(prefix.begin() + i, prefix.end(), target);

        if(last != prefix.end()){
            i = distance(prefix.begin(), last); // cập nhật vị trí bắt đầu ngày mai
            t = p;   // reset thời gian cho phiên mới
            ++m;     // tăng số ngày đã tổ chức

            // Bước 6: Nếu i vượt qua n, tức là đã đi qua 1 vòng đầy đủ
            if(i >= n){
                i -= n;
                c++; // tăng số lần full rehearsal
            }

            // Bước 7: Phát hiện và nhảy chu kỳ (cycle detection)
            // Nếu days[i] != -1: ta đã thấy trạng thái bắt đầu tại học sinh i trước đây
            // => cấu trúc lặp lại => nhảy nhiều chu kỳ cùng lúc để tiết kiệm thời gian
            if(days[i] != -1){
                if(!cycle){ // chỉ nhảy 1 lần để tránh vượt quá k
                    long long cycleLen = m - days[i];        // độ dài 1 chu kỳ (số ngày)
                    long long numCycle = (k - m) / cycleLen; // số chu kỳ có thể nhảy
                    m += numCycle * cycleLen;                 // nhảy m tiến
                    c += numCycle * (c - full[i]);            // cộng thêm full rehearsal tương ứng
                    cycle = true;
                }
            } else {
                // Lần đầu thấy trạng thái bắt đầu tại học sinh i -> lưu lại để phát hiện chu kỳ
                days[i] = m;
                full[i] = c;
            }

            // Bước 8: Kiểm tra đã đủ k ngày chưa
            if(m == k){
                return c;
            }
        }
        // (else: không xảy ra với input hợp lệ vì prefix kép luôn đủ dài)
    }
    return c;
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
    long long n,p,k;
    cin>>n>>p>>k;
    vector<long long> d(n);
    for(int i = 0; i < n; ++i){
        cin>>d[i];
    }
    cout<<solve(d, p, k);
	return 0;
}
