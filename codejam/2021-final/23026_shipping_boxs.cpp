/******************************************************************************

https://codejam.lge.com/problem/23021
algo: binary search
algo: Pigeonhole Principle 
*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long T,n,B,R;
/**
 * V số item trong 1 container v[i] độ dài mỗi item
 * B kích thước box xếp các v[i] theo thứ tự
 * R số containe
 * return: số box phải dùng để đóng đầy
 */
long long solve(vector<long long>& v, long long B, long long R){
    const long long n = v.size();
    
    vector<long long> prefix(2*v.size(), 0);
    for(int i = 0; i < (int)prefix.size(); ++i){
        prefix[i] = (i > 0 ? prefix[i-1] : 0) + v[(i % n)];
    }
    
    long long numBox = 1,numCont=0;
    long long space = B; // không gian còn lại của phiên hiện tại

    // Bước 2: Trường hợp đặc biệt - B đủ lớn để đi hết >= 1 vòng mỗi ngày
    // => mỗi ngày hoàn thành đúng (B / tổng_1_vòng) lần full rehearsal
    if(space >= prefix[n-1] && space % prefix[n-1] == 0){
        long long contInABox = ((long long)(space / prefix[n-1]));
        numBox=R/contInABox;
        R-= numBox*contInABox;
        if(R !=0){
            numBox++;
        }
        return numBox;
    }
    //số box đã dùng 
    //số container đã đóng gói
    vector<long long> usedB(n,-1), cont(n,-1);
    // long long contCount=0;
    long long idx = 0; //item which remain start point
    
    bool cycle = false; // đã nhảy chu kỳ hay chưa (chỉ nhảy 1 lần)
    while(true){
        //space lớn
        if(space >= prefix[n-1]){
            numCont+=(space/prefix[n-1]);
            space %= prefix[n-1];
        }
        if(numCont >= R){
            return numBox;
        }
        auto target = space + (idx > 0 ? (*(prefix.begin() + idx - 1)) : 0);
        auto last = upper_bound(prefix.begin() + idx, prefix.end(), target);
        if(last != prefix.end()){
            idx = distance(prefix.begin(), last); // cập nhật vị trí bắt đầu ngày mai
            
            // Bước 6: Nếu i vượt qua n, tức là đã đi qua 1 vòng đầy đủ
            if(idx >= n){
                idx -= n;
                numCont++; // tang so container covered
            }
            if(numCont >= R){
                return numBox;
            }
            space = B;   // reset khong gian gian cho phiên mới
            ++numBox;     // tăng số box
            // cout<<"container:"<<numCont<<" ubox:"<<numBox<<endl;
            // Bước 7: Phát hiện và nhảy chu kỳ (cycle detection)
            // Nếu days[i] != -1: ta đã thấy trạng thái bắt đầu tại học sinh i trước đây
            // => cấu trúc lặp lại => nhảy nhiều chu kỳ cùng lúc để tiết kiệm thời gian
            if(cont[idx] != -1){
                if(!cycle){ // chỉ nhảy 1 lần để tránh vượt quá k
                    long long cycleLen = numCont - cont[idx];        // độ dài 1 chu kỳ (số ngày)
                    long long numCycle = (R - numCont-1) / cycleLen; // số chu kỳ có thể nhảy

                    // cout<<"box:"<<numBox-usedB[idx]<<" con:"<<cycleLen<<" numcycle:"<<numCycle<< endl;
                    numBox += numCycle * (numBox - usedB[idx]);                 // nhảy m tiến
                    numCont += numCycle * cycleLen;            // cộng thêm full rehearsal tương ứng
                    cycle = true;
                }
            } else {
                // Lần đầu thấy trạng thái bắt đầu tại học sinh i -> lưu lại để phát hiện chu kỳ
                cont[idx] = numCont;
                usedB[idx] = numBox;
            }

            // Bước 8: Kiểm tra đã đủ k ngày chưa
            if(numCont >= R){
                return numBox;
            }
        }
    }
    return numBox;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> T;
    
    while(T > 0){
        // cout<<"T---------------:"<<T<<endl;
        cin>>n>>B>>R;
        vector<long long> v(n);
        for(int i = 0; i < n; ++i){
            cin>>v[i];
        }
    
        cout<<solve(v, B, R)<<endl;
        --T;
    }
    return 0;
}
