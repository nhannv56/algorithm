/******************************************************************************

https://www.acmicpc.net/problem/24326
algo:Mathematics
algo:Sorting
algo:Number Theory
algo:Primality Test
algo:Precomputation
algo:Sieve Of Eratosthenes

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>

using namespace std;
long long N,M;
vector<long long> getDivisors(long long n) {
    vector<long long> divs;
    long long Range = sqrt(n);
    for (long long i = 1; i <= Range; ++i) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i * i != n) { // Tránh thêm 2 lần nếu là số chính phương
                divs.push_back(n / i);
            }
        }
    }
    return divs;
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>N;
	vector<long long> sweets(N+1,0);
	
	long long res = 0;
	vector<pair<long long,long long>> collected(N+1,{0,0});
	
	collected[0]={-1e14,0};
	for(long long i = 1; i <= N; ++i){
	    cin>>sweets[i];
	}
	long long maxSweet = -1e14;
	
	vector<vector<long long>> carrots(N+1,vector<long long>(2,-1e14));//max bị thay đổi theo carrot, và không 
    //vector<long long> postfix(N+2,-1e14);
    
    for(long long i = 1; i <= N; ++i){
        collected[i].second=i;
	    for(int j = i; j <= N; j += i){
	        collected[i].first += sweets[j];
	    }
	}
	auto sortB = collected;
	sort(sortB.begin(), sortB.end(), [](auto &a, auto b){return a.first > b.first;});

    // 1. Tính carrots[i][0] (Max của các ước): Dùng Sàng (Sieve) - O(N log N)
    for (int d = 1; d <= N; ++d) {
        long long val = collected[d].first;
        for (int i = d; i <= N; i += d) {
            carrots[i][0] = max(carrots[i][0], val);
        }
    }

    // 2. Tính carrots[i][1] (Max của các số không phải ước)
    for(int i = 1; i <= N; ++i){
        for(const auto& item : sortB){
            if(item.second == 0) continue; // Safety check
            if(i % item.second != 0){
                carrots[i][1] = item.first;
                break;
            }
        }
    }
    
    // Chuẩn bị dữ liệu Precompute
    vector<int> used(N + 1, 0); 
    // answer[i].first = Max Affected (nhóm ước), .second = Max Unaffected (nhóm không ước)
    vector<pair<long long, long long>> answer(N + 1, {-4e18, -4e18});

    // Tính trước cho TOÀN BỘ các số từ 1 đến N (thay vì tính mỗi lần query)
    // O(N * sqrt(N))
    for (int i = 1; i <= N; ++i) {
        long long currentMaxAffected = -4e18;

        // 1. Tìm ước và đánh dấu - O(sqrt(i))
        for (int j = 1; j * j <= i; ++j) {
            if (i % j == 0) {
                // j là ước
                currentMaxAffected = max(currentMaxAffected, collected[j].first);
                used[j] = i; // Đánh dấu j là ước của i

                // i/j cũng là ước
                if (j * j != i) {
                    int other = i / j;
                    currentMaxAffected = max(currentMaxAffected, collected[other].first);
                    used[other] = i; // Đánh dấu
                }
            }
        }
        answer[i].first = currentMaxAffected;

        // 2. Tìm số lớn nhất KHÔNG phải là ước - O(1) trung bình
        // Duyệt danh sách đã sort. Vì các ước đã được đánh dấu 'used' ở bước trên
        // nên ta chỉ cần check mảng used, không cần dùng phép % chậm chạp.
        for (const auto& item : sortB) {
            if (item.second == 0) continue; 
            
            // Nếu item.second chưa bị đánh dấu là ước của i hiện tại
            if (used[item.second] != i) {
                answer[i].second = item.first;
                break; // Tìm thấy ngay số lớn nhất không liên quan
            }
        }
    }
    
	cin >> M;
	long long p, s;
	
    // Truy vấn O(1)
	for(int i = 0; i < M; ++i){ 
	    cin >> p >> s;
        // Max của (Nhóm bị ảnh hưởng + s) vs (Nhóm không bị ảnh hưởng)
	    long long currentRes = max(answer[p].first + s, answer[p].second);
	    res += currentRes;
	}
	
	cout<<res;
	return 0;
}