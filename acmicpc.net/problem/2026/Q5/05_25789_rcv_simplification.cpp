/***

https://www.acmicpc.net/problem/25789
algo: greedy
algo: prefix sum
* Có $N$ lá phiếu cho các ứng viên.
* **Quy tắc loại:** Người có ít phiếu nhất bị loại. Nếu nhiều người cùng có số phiếu thấp nhất bằng nhau, **tất cả** đám đó bị loại cùng lúc.
* **Quy tắc thắng:** Một người thắng nếu có số phiếu $> 50\%$ tổng số phiếu hiện có.
* **Câu hỏi:** Tìm tất cả ứng viên **không bao giờ** có cơ hội thắng, dù kịch bản chuyển giao phiếu bầu có thuận lợi thế nào đi nữa.

### 2. Cách giải (Thuật toán "Leo Tháp")

Để một người có cơ hội thắng, họ phải vượt qua được tất cả các vòng loại trừ từ dưới lên. Ta dùng chiến thuật **Tham lam (Greedy)**: 
Giả sử ứng viên đó nhận được toàn bộ phiếu từ những người yếu hơn đã bị loại.

**Các bước thực hiện:**

* **Bước 1: Nhóm và Sắp xếp:** Gom các ứng viên có cùng số phiếu vào các nhóm. Sắp xếp các mức phiếu tăng dần: $v_1 < v_2 < v_3 < \dots < v_k$.
* **Bước 2: Tính Tổng dồn (Prefix Sum):** Gọi $S_i$ là tổng số phiếu của tất cả ứng viên thuộc các nhóm từ $1$ đến $i$. 
            Đây là "sức mạnh tối đa" mà một người ở nhóm $i$ có thể đạt được sau khi hấp thụ các nhóm yếu hơn.
* **Bước 3: Tìm "Điểm Gãy" (The Barrier):** Duyệt từ nhóm thấp nhất lên cao nhất. Một nhóm $i$ sẽ bị loại (và kéo theo toàn bộ các nhóm yếu hơn $1 \dots i-1$ bị loại) nếu:
    $$S_i < v_{i+1}$$
    *(Giải thích: Dù nhóm $i$ có gom sạch phiếu của các nhóm dưới, họ vẫn chỉ bằng hoặc ít phiếu hơn nhóm tiếp theo. Theo luật "Hòa là loại hết", cả đám này sẽ bị quét sạch ở vòng đó).*

* **Bước 4: Kết luận:** * Tìm chỉ số $i$ lớn nhất thỏa mãn điều kiện $S_i < v_{i+1}$. 
    * Tất cả ứng viên có số phiếu < v_{i+1}$ đều nằm trong danh sách **Không thể thắng**.
    * *Lưu ý:* Nếu có người chiếm $> 50\%$ ngay từ đầu, chỉ người đó có thể thắng, tất cả còn lại đều thua.
**/
#include <iostream>
#include <bits/stdc++.h>
#include <iterator> // For std::next
using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
#endif
    int N;
    cin >> N;
    vector<string> names(N);
    for(int i = 0; i < N;++i){
        cin>>names[i];
    }
    sort(names.begin(), names.end());
    int count = 1;
    vector<pair<int,string>> votes;// count vote and name
    for(int i = 1; i < N; ++i){
        if(names[i]== names[i-1]){
            ++count;            
        }else{
            votes.push_back({count, names[i-1]});
            //cout<<names[i-1]<<" "<<count<<endl;
            count = 1;
        }
    }
    votes.push_back({count, names[names.size()-1]});
    sort(votes.begin(), votes.end());
    // for(auto it : votes){
    //     cout<<"vote:"<<it.first<<" "<<it.second<<endl;
    // }
    vector<int> voteVal;
    for(auto v : votes){
        if(voteVal.size() ==0){
            voteVal.push_back(v.first);
        }else if(v.first != *voteVal.rbegin()){
            voteVal.push_back(v.first);
        }
    }
    vector<string> canNotWin;
    if(votes.size()==1){
        cout<<0;
    }else{
        int resI = 0;
        if(votes[0].first == votes[votes.size()-1].first){
            resI = votes.size()-1;
        }else{
            int sigIndex = 1;
            int possibleVote = 0;
            int countSame = 0;
            int curVote = votes[0].first;
            for(int i = 0; i < votes.size();++i){
                
                if(curVote == votes[i].first){
                    countSame++;
                }else{                    
                    possibleVote+=countSame*curVote;
                    curVote= voteVal[sigIndex];
                    countSame=1;
                    sigIndex++;
                }
                if(votes[i].first+possibleVote <= voteVal[sigIndex]){
                    resI = i;
                }
            }
        }
        for(int i = 0; i <= resI;++i){
            canNotWin.push_back(votes[i].second);
        }
        sort(canNotWin.begin(), canNotWin.end());
        cout<<canNotWin.size()<<'\n';
        for(int i = 0; i < canNotWin.size();++i){
            cout<<canNotWin[i];
            if(i!= canNotWin.size()-1){
                cout<<'\n';
            }
        }
    }
    
    return 0;
}
