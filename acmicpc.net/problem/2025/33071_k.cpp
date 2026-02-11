/***
 * 
 * Data Structures
Sorting
Binary Search
Set / Map
Set / Map By Trees
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Dùng struct để code rõ ràng hơn pair
struct Node {
    long long b, a;
    int id; // Lưu index ban đầu nếu cần debug
};

// Sắp xếp tăng dần theo b
bool compareNodes(const Node& x, const Node& y) {
    if (x.b != y.b) return x.b < y.b;
    return x.a < y.a;
}

int main() {
    // Tối ưu nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long K;
    if (!(cin >> N >> K)) return 0;

    vector<Node> data(N);
    for (int i = 0; i < N; ++i) {
        cin >> data[i].a >> data[i].b;
        data[i].id = i;
    }

    // Bước 1: Sắp xếp
    sort(data.begin(), data.end(), compareNodes);

    // Bước 2: Tạo mảng P
    // P[i]: chỉ số của phần tử gần nhất bên trái có a KHÁC data[i].a
    // Nếu không có thì là -1
    vector<int> P(N, -1);
    for (int i = 1; i < N; ++i) {
        if (data[i].a != data[i-1].a) {
            P[i] = i - 1;
        } else {
            P[i] = P[i-1]; // Copy giá trị của thằng trước đó vì a giống nhau
        }
    }

    long long max_sum = -2e18; // Khởi tạo giá trị rất nhỏ
    bool found = false;        // Cờ đánh dấu xem có tìm được cặp nào không

    // Bước 3: Duyệt và tìm kiếm
    for (int i = 0; i < N; ++i) {
        long long target = K - data[i].b;

        // Tìm vị trí đầu tiên mà b > target
        // Nghĩa là các phần tử đứng trước vị trí này đều có b <= target
        auto it = upper_bound(data.begin(), data.end(), target, [](long long val, const Node& node){
            return val < node.b;
        });
        
        int idx = (int)(it - data.begin()) - 1;

        // Bắt đầu kiểm tra từ idx ngược về trái
        int curr = idx;
        
        // Vòng lặp này thực tế chỉ chạy vài lần nhờ mảng P
        while (curr >= 0) {
            // Nếu trùng với chính nó thì lùi lại 1 bước
            if (curr == i) {
                curr--;
                continue;
            }

            // Nếu a khác nhau -> Thỏa mãn điều kiện
            if (data[curr].a != data[i].a) {
                long long current_sum = data[i].b + data[curr].b;
                if (!found || current_sum > max_sum) {
                    max_sum = current_sum;
                    found = true;
                }
                // Vì mảng đã sắp xếp theo b, nên tìm được thằng lớn nhất thỏa mãn rồi
                // thì không cần tìm tiếp các thằng nhỏ hơn bên trái nữa.
                break; 
            } else {
                // Nếu a giống nhau -> Nhảy cóc qua tất cả các thằng có cùng a
                curr = P[curr];
            }
        }
    }

    if (found) {
        cout << max_sum;
    } else {
        cout << "NO";
    }

    return 0;
}