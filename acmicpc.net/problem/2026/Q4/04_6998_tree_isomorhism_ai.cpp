/***
 * algo: Tree Isomorphism
 * 3. Ví dụ minh họa sự "Isomorphic"Giả sử chúng ta có 2 cây trông có vẻ khác nhau về thứ tự:
 * Cây 1: Gốc A có con B (lá) và C (có 1 con lá D).
 * Mã của B: ()
 * Mã của D: ()
 * Mã của C: (()) (vì C bao bọc mã của D)
 * Mã của A: Sắp xếp ["()", "(())"] $\rightarrow$ 
 * Kết quả: (() (()) )
 * Cây 2: Gốc X có con Y (có 1 con lá Z) và W (lá).
 * Mã của W: ()
 * Mã của Z: ()
 * Mã của Y: (())
 * Mã của X: Sắp xếp ["(())", "()"] $\rightarrow$ 
 * Kết quả: (() (()) )
 * Kết luận: Cả hai cây đều có mã cuối cùng là (()(())).
 *  Vì mã giống nhau, chúng đồng cấu!4. 
 * Tại sao cách này tối ưu?Tính duy nhất: 
 * Phương pháp này (được gọi là Tree Hashing hoặc AHU Algorithm) 
 * đã được chứng minh là tạo ra một chuỗi duy nhất cho mỗi cấu trúc cây không có thứ tự.
 * Độ phức tạp:Duyệt qua mỗi nút 1 lần: $O(N)$.
 * Thao tác sắp xếp chuỗi tại mỗi nút: Tổng cộng mất khoảng $O(N \log N)$ hoặc $O(N^2)$ tùy thuộc vào độ dài chuỗi. 
 * Với $N=20$, nó chạy cực nhanh (vài mili giây).
 */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Hàm đệ quy để tạo mã định danh cho cây
// pos: vị trí hiện tại trong danh sách token
string getCanonicalForm(const vector<string>& tokens, int& pos) {
    // Nếu token hiện tại là '#', nghĩa là cây con rỗng tại hướng này (backtrack)
    if (pos >= tokens.size() || tokens[pos] == "#") {
        return "";
    }

    pos++; // Bỏ qua tên nút hiện tại (vì tên nút không quan trọng trong đồng cấu)
    
    vector<string> childCodes;
    // Duyệt qua tất cả các con của nút hiện tại
    while (pos < tokens.size() && tokens[pos] != "#") {
        childCodes.push_back(getCanonicalForm(tokens, pos));
    }
    
    if (pos < tokens.size() && tokens[pos] == "#") {
        pos++; // Bỏ qua dấu '#' để quay về nút cha
    }

    // Bước quan trọng nhất: Sắp xếp mã của các con
    sort(childCodes.begin(), childCodes.end());

    // Xây dựng mã cho nút hiện tại
    string result = "(";
    for (const string& code : childCodes) {
        result += code;
    }
    result += ")";
    
    return result;
}

// Hàm chuyển đổi dòng input thành vector các token (nút hoặc #)
vector<string> tokenize(string line) {
    stringstream ss(line);
    string token;
    vector<string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void solve() {
    string line1, line2;
    if (!getline(cin, line1) || !getline(cin, line2)) return;

    vector<string> tokens1 = tokenize(line1);
    vector<string> tokens2 = tokenize(line2);

    int pos1 = 0, pos2 = 0;
    string code1 = getCanonicalForm(tokens1, pos1);
    string code2 = getCanonicalForm(tokens2, pos2);

    if (code1 == code2) {
        cout << "The two trees are isomorphic." << endl;
    } else {
        cout << "The two trees are not isomorphic." << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Nếu bạn muốn xuất ra file luôn
    #endif
    int T;
    if (!(cin >> T)) return 0;
    string dummy;
    getline(cin, dummy); // Đọc bỏ dòng trống sau T

    while (T--) {
        solve();
    }

    return 0;
}