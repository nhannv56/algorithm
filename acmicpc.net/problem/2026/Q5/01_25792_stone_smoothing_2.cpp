/***
https://www.acmicpc.net/problem/25792
needCut = ceil((PI - degrees[i]) / (PI - minDegree));
Sử dụng góc trong
user write
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;
long long C, S;
const double PI =  acos(-1.0);
bool satify(double minDegree, long long numCut, vector<double>& degrees)
{
    long long needCut = 0;
    bool res = true;
    for (int i = 0; i < degrees.size(); ++i)
    {
        if (degrees[i] < minDegree)
        {
            needCut = ceil((PI-degrees[i])/(PI-minDegree)- 1e-9) - 1;
            needCut = max(0LL, needCut); // Đảm bảo số lần cắt không bị âm
            numCut -= needCut;
            if (numCut < 0)
            {
                res = false;
                break;
            }
        }
    }
    // cout<<"D:"<<minDegree*180/PI<<" "<<res<<endl;
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
        arccosVal = max(-1.0, min(1.0, arccosVal));
        auto radian = acos(arccosVal);
        // auto d = radian * 180.0 / PI; // conver radian to o
        // cout<<"cos:"<<arccosVal<<" "<<d<<'\n';
        degrees.push_back(radian);
    }
    // sort(degrees.begin(), degrees.end());
    // for(auto d : degrees){
    //     cout<<d<<endl;
    // }
    double l = *min_element(degrees.begin(), degrees.end()), r = PI, mid;
    // double minDegree = *degrees.begin();
    double res = 0;
    for (int i = 0; i < 200; ++i)
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
    cout << fixed << setprecision(6) << 360-res * 180.0 / PI << '\n';
    return 0;
}
