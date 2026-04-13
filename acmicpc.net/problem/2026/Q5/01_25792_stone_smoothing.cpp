/***

https://www.acmicpc.net/problem/25792
algo: binary search
algo: math
góc ngoài mới = góc ngoài cũ chia số góc -1 => số lần cắt
Tìm góc ngoài theo toán học nhỏ nhất có thể thỏa mãn điều kiện
tìm số lần cắt tối thiểu để đạt được cho các gọc hiện có
**/
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);

struct Point {
    double x, y;
};

// Hàm kiểm tra xem với góc ngoài tối đa là maxExtAngle, số lần cắt có <= S không
bool check(double maxExtAngle, long long S, const vector<double>& extAngles) {
    long long totalCuts = 0;
    for (double alpha : extAngles) {
        if (alpha > maxExtAngle) {
            // Tính số nhát cắt cần thiết để chia góc alpha thành các phần <= maxExtAngle
            // Số phần = ceil(alpha / maxExtAngle), nên số nhát cắt = Số phần - 1
            long long cuts = ceil(alpha / maxExtAngle - 1e-9) - 1;
            S -= max(0LL, cuts);
        }
    }
    return S >= 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
#endif
    int C;
    long long S;
    if (!(cin >> C >> S)) return 0;

    vector<Point> pts(C);
    for (int i = 0; i < C; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    vector<double> extAngles(C);
    for (int i = 0; i < C; ++i) {
        Point prev = pts[(i - 1 + C) % C];
        Point curr = pts[i];
        Point next = pts[(i + 1) % C];

        // Vector BA và BC
        double v1x = prev.x - curr.x;
        double v1y = prev.y - curr.y;
        double v2x = next.x - curr.x;
        double v2y = next.y - curr.y;

        // Tính góc trong (interior angle) bằng dot product
        double dotProduct = v1x * v2x + v1y * v2y;
        double mag1 = sqrt(v1x * v1x + v1y * v1y);
        double mag2 = sqrt(v2x * v2x + v2y * v2y);
        
        double cosVal = dotProduct / (mag1 * mag2);
        // Tránh lỗi độ chính xác floating point làm cosVal vượt quá [-1, 1]
        cosVal = max(-1.0, min(1.0, cosVal));
        
        double interiorAngle = acos(cosVal); // radian
        extAngles[i] = PI - interiorAngle;   // Góc ngoài = PI - góc trong
    }

    // Tìm kiếm nhị phân cho góc ngoài mục tiêu (từ 0 đến PI)
    double left = 0.0;
    double right = PI;
    
    // 200 vòng lặp là quá đủ cho độ chính xác của số thực
    for (int iter = 0; iter < 200; ++iter) {
        double mid = (left + right) / 2.0;
        if (check(mid, S, extAngles)) {
            right = mid; // Có thể đạt được, thử ép góc ngoài nhỏ hơn nữa
        } else {
            left = mid;  // Không đủ số lần cắt, phải chấp nhận góc ngoài lớn hơn
        }
    }

    // Kết quả là góc trong nhỏ nhất tương ứng (chuyển đổi sang hệ Độ)
    double bestMinInteriorAngle = PI + right;
    cout << fixed << setprecision(6) << (bestMinInteriorAngle * 180.0 / PI) << "\n";

    return 0;
}
