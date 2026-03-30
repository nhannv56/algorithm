/***
 * TÓM TẮT ĐỀ BÀI VÀ PHƯƠNG PHÁP GIẢI: FLARIANA FLOWERS

---
1. Tóm tắt đề bài
- Cấu trúc: N bông hoa (N <= 300) nối thành một Cây (Tree).
- Dữ liệu mỗi hoa k: s_k (số lượng ong), p_k (sức mạnh).
- Giới hạn: Tổng số ong chọn đi <= S (S <= 300).
- Điều kiện: Với mỗi cạnh (u, v), không được chọn cả hai gia đình u và v cùng đi.
- Mục tiêu: Tìm tổng sức mạnh p_k lớn nhất.

---
2. Phương pháp giải: Tree DP + Knapsack
Đây là bài toán tìm Tập độc lập có trọng số (Independent Set) trên cây kết hợp giới hạn cái túi (Knapsack).

Trạng thái DP:
dp[u][j][state]: Sức mạnh lớn nhất ở cây con gốc u, dùng j con ong.
- state = 0: Không chọn u.
- state = 1: Có chọn u.

Công thức truy hồi (Khi gộp con v vào cha u):
1. Nếu không chọn u (state=0):
   dp[u][j+k][0] = max(dp[u][j][0] + max(dp[v][k][0], dp[v][k][1]))
2. Nếu có chọn u (state=1):
   dp[u][j+k][1] = max(dp[u][j][1] + dp[v][k][0])

Khởi tạo:
- dp[u][0][0] = 0
- Nếu s_u <= S: dp[u][s_u][1] = p_u
- Các giá trị khác = -vô cùng.

---
3. Độ phức tạp
- Thời gian: O(N * S^2) ~ 300^3 = 27,000,000 (Pass tốt trong 1-2s).
- Không gian: O(N * S).
 */