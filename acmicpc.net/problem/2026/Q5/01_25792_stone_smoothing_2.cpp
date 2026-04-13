/***
https://www.acmicpc.net/problem/25792
needCut = ceil((PI - degrees[i]) / (PI - minDegree));
Sử dụng góc trong
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long C;
const double PI =  acos(-1.0);
struct Point {
    double x, y;
};
bool satify(double targetMinInt, long long S, vector<double>& intAngles)
{
    for (double currentInt : intAngles) {
        if (currentInt < targetMinInt) {
            double divisor = PI - targetMinInt;
            // Nếu targetMinInt rất gần PI, số nhát cắt sẽ tiến tới vô cực
            if (divisor < 1e-12) return false;
            
            // Tính số nhát cắt cần thiết để phân bổ góc ngoài
            // Góc ngoài mục tiêu = PI - targetMinInt
            // Góc ngoài hiện tại = PI - currentInt
            long long cuts = ceil((PI - currentInt) / divisor - 1e-9) - 1;
            S -= max(0LL, cuts);
            
            if (S < 0) return false; // Không đủ số lần cắt
        }
    }
    return true;
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
long long S;
    cin >> C >> S;
    double x, y;
    vector<Point> pts(C);
    for (int i = 0; i < C; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    vector<double> intAngles(C);
    for (int i = 0; i < C; ++i) {
        Point prev = pts[(i - 1 + C) % C];
        Point curr = pts[i];
        Point next = pts[(i + 1) % C];

        // Vector BA và BC
        double v1x = prev.x - curr.x;
        double v1y = prev.y - curr.y;
        double v2x = next.x - curr.x;
        double v2y = next.y - curr.y;

        double dotProduct = v1x * v2x + v1y * v2y;
        double mag1 = sqrt(v1x * v1x + v1y * v1y);
        double mag2 = sqrt(v2x * v2x + v2y * v2y);
        
        double cosVal = dotProduct / (mag1 * mag2);
        cosVal = max(-1.0, min(1.0, cosVal));
        
        // Lưu lại chính góc trong (interior angle)
        intAngles[i] = acos(cosVal);
    }
    double l = 0.0, r = PI, mid;
    double res = 0;
    for (int i = 0; i < 200; ++i)
    {
        double mid = (l + r) / 2.0;
        if (satify(mid, S, intAngles))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    cout <<fixed << setprecision(6) << 360-(l * 180.0 / PI) << "\n";
    return 0;
}
