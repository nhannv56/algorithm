/******************************************************************************

https://www.acmicpc.net/problem/23077
algo: slide window
algo: sweeping
algo: data structure lưu k phần tử lớn nhất trong range
hỗ trợ thêm và xóa 1 phần tử bất kỳ O log(n)
bài toán O(nlog(n))

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include <iterator> // For std::next

using namespace std;

long long T, D, N,K;
class MaxKinN{
public:
    class Elements{
        public:
            int count = 0;            
            map<long long, int> elms;            
            long long total = 0;
            void insert(long long val){
                auto it = elms.find(val);
                if(it == elms.end()){
                    elms[val]=1;
                }else{
                    ++elms[val];
                }
                ++count;
                total+=val;
            }
            void erase( long long val){
                auto it = elms.find(val);
                if(it != elms.end()){
                   if(it->second <=1){
                       elms.erase(it);
                   }else{
                        --it->second;
                   }
                }
                --count;
                total-=val;
            }
    };
    
    Elements maxK, buffer;
    int K=0;
    MaxKinN(int _K){
        K = _K;
    }
    void insert(long long val){
        if(maxK.count < K){ //thêm vào maxK vì chưa đầy
            maxK.insert(val);
        }else{
            auto fmk = maxK.elms.begin();//tính toán để thêm vào maxK từ giá trị hoặc từ buffer
            if(fmk->first < val){
                auto fVal = fmk->first;
                maxK.erase(fVal);
                maxK.insert(val);
                buffer.insert(fVal);
            }else{
                buffer.insert(val);
            }
        }
    }
    void erase(long long val){
        auto b = buffer.elms.find(val);
        if(b == buffer.elms.end()){//ko co trong buffer nằm trong maxK phần tử
            maxK.erase(val);
            if(buffer.elms.size() > 0){
                maxK.insert(buffer.elms.rbegin()->first);//phần tử lớn nhất trong buffer
                buffer.erase(buffer.elms.rbegin()->first);
            }
        }else{
            buffer.erase(val);
        }
    }

};
long long slide_window(vector<pair<long long, long long>>& starts,vector<pair<long long, long long>>& ends, long long D, long long K){
    sort(starts.begin(), starts.end());// time and label
    sort(ends.begin(), ends.end());
    long long res = 0;
    MaxKinN mkn(K);
    int sI = 0;
    int eI = 0;
    for(int d = 1; d <= D;++d){
        while(sI < starts.size() && starts[sI].first <= d){
            mkn.insert(starts[sI].second);
            ++sI;
        }
        while(eI < ends.size() && ends[eI].first < d){
            mkn.erase(ends[eI].second);
            ++eI;
        }
        res = max(mkn.maxK.total, res);
    }
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

    cin>>T;
    long long h, s, e;
	for(int t = 1; t <=T; ++t){
        cin>>D>>N>>K;
        vector<pair<long long, long long>> starts(N),ends(N);
        for(int i = 0; i < N; ++i){
            cin>>h>>s>>e;
            starts[i] = {s, h};
            ends[i] = {e, h};
        }

        cout<<"Case #"<<t<<": " <<slide_window(starts, ends, D, K)<<'\n';
    }
	return 0;
}