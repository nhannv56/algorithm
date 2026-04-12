/***

https://www.acmicpc.net/problem/25792
dùng map<double,int> tham số góc và số góc tương ứng
khởi tạo C góc ban đầu
duyệt từ góc nhỏ tìm góc kế tiếp,
chia sao cho góc nhỏ > góc liền kề -> xóa + chèn vào map
công thức 180 - (180-alpha)/(2*k)
-alpha là góc đang xét
-k là số lần cắt sẽ tạo ra k góc mới
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
int C, S;
const double PI = 3.14159265358979323846;
bool satify(double minDegree, int numCut, vector<double> degrees)
{
    int needCut = 0;
    bool res = true;
    for (int i = 0; i < degrees.size(); ++i)
    {
        if (degrees[i] < minDegree)
        {
            needCut = ceil(degrees[i]/(PI-minDegree)-1);
            numCut -= needCut;
            if (numCut < 0)
            {
                res = false;
                break;
            }
        }
    }
    cout<<"D:"<<minDegree*180/PI<<" "<<res<<endl;
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
    cin >> C >> S;
    double x, y;
    vector<pair<double, double>> pos(C + 2);
    for (int i = 0; i < C; ++i)
    {
        cin >> pos[i].first >> pos[i].second;
    }
    pos[C] = pos[0];
    pos[C + 1] = pos[1];
    // build góc
    //  solve
    vector<double> degrees;
    for (int i = 1; i < pos.size() - 1; ++i)
    {
        auto [xa, ya] = pos[i - 1];
        auto [xb, yb] = pos[i];
        auto [xc, yc] = pos[i + 1];
        auto b1 = xa - xb, b2 = ya - yb;
        auto c1 = xc - xb, c2 = yc - yb;
        auto arccosVal = (b1 * c1 + b2 * c2) / (sqrt(b1 * b1 + b2 * b2) * sqrt(c1 * c1 + c2 * c2));
        auto radian = acos(arccosVal);
        // auto d = radian * 180.0 / PI; // conver radian to o
        // cout<<"cos:"<<arccosVal<<" "<<d<<'\n';
        degrees.push_back(radian);
    }
    // sort(degrees.begin(), degrees.end());
    // for(auto d : degrees){
    //     cout<<d<<endl;
    // }
    double l = 0, r = PI, mid;
    // double minDegree = *degrees.begin();
    double res = 0;
    for (int i = 0; i < 100; ++i)
    {
        double mid = (l + r) / 2.0;
        if (satify(mid, S, degrees))
        {
            l = mid;
            res = l;
        }
        else
        {
            r = mid;
            res = r;
        }
    }
    cout << (2*PI - res)* 180.0 / PI << '\n';
    return 0;
}
