- Lưu ý:
+ khi implement -> chú ý tính independant vừa kiểm tra vừa update vùng dữ liệu có thể dẫn đến sai state
        https://github.com/nhannv56/algorithm/edit/master/acmicpc.net/problem/2026/Q4/05_8972_roboti.cpp
1. SegmentTree
- Sum trên đoạn
- Min trên đoạn
- Max trên đoạn
- Quản lý các đoạn thẳng, diện tích phủ bởi các hình chữ

2. Disjoin-Set
- Tìm các nhóm
3. Two Pointer
- Khi trên 1 đoạn cần l -> r có điều kiện ràng buộc gì đó mà tạo ra 1 biên
- Thường kết hợp vs binary search
- Thường là mảng đã sắp xếp hoặc có tính chất đơn điệu.
4. Sweep line
- Thường là tập hợp các khoảng (intervals) hoặc tọa độ điểm
- Thường đi vs SegmentTree/set/heap
5. Binary search
- Bài toán tìm số thỏa mãn điều kiện vs biên rộng -> và kiểm tra satify thường là log(N) 

6. bfs/dfs
7. dijiktra

Tree
Trong giới Competitive Programming, nếu xem **Đường kính cây (Tree Diameter)** là một "pattern" cơ bản, thì thế giới thuật toán trên cây còn rất nhiều "biến thể" quan trọng khác. 
Với kinh nghiệm làm C++ lâu năm, bạn sẽ thấy các dạng này thường xoay quanh việc tối ưu hóa cách ta duyệt hoặc truy vấn trên cấu trúc phân cấp.

Dưới đây là các dạng bài toán trên cây phổ biến được phân loại theo kỹ thuật xử lý:

---

### 1. Rerooting DP (DP thay đổi gốc)
Đây là kỹ thuật nâng cao của DP trên cây. Thay vì chỉ tính kết quả cho một gốc cố định, ta cần tính kết quả cho **tất cả** các nút $N$ nếu mỗi nút đó lần lượt được chọn làm gốc.
* **Đặc điểm:** Thường chạy 2 lần DFS ($O(N)$). Lần 1 tính từ dưới lên (Bottom-up), lần 2 đẩy giá trị từ trên xuống (Top-down).
* **Ứng dụng:** Tìm nút mà tổng khoảng cách từ nó đến các nút khác là nhỏ nhất (Centroid), hoặc bài toán tính toán giá trị dựa trên sự tương tác toàn cục của cây.

### 2. LCA & Binary Lifting (Truy vấn đường đi)
Dạng này tập trung vào mối quan hệ giữa hai nút bất kỳ trên cây.
* **Kỹ thuật:** Sử dụng bảng thưa (Sparse Table) trên cây để tìm **Lowest Common Ancestor** trong $O(\log N)$.
* **Ứng dụng:** Tính khoảng cách giữa 2 nút ($dist(u, v) = depth[u] + depth[v] - 2 \times depth[LCA(u, v)]$), truy vấn các giá trị (min/max/sum) trên đường đi từ $u$ đến $v$.

### 3. Tree Flattening & Euler Tour (Phẳng hóa cây)
Biến cây thành một mảng tuyến tính để tận dụng các cấu trúc dữ liệu mạnh mẽ như **Segment Tree** hoặc **Fenwick Tree**.
* **Kỹ thuật:** Dùng DFS để ghi lại thời điểm vào (`tin`) và thời điểm ra (`tout`) của mỗi nút.
* **Ứng dụng:** Biến các truy vấn trên **cây con (subtree)** thành truy vấn trên **đoạn (range)** của mảng. Rất hiệu quả khi bài toán yêu cầu cập nhật giá trị nút và truy vấn tổng cây con liên tục.


### 4. Heavy-Light Decomposition (HLD)
Một kỹ thuật "hạng nặng" để xử lý các truy vấn trên đường đi (path queries) khi có cả cập nhật (update).
* **Chiến thuật:** Chia các cạnh của cây thành các "chuỗi" (chains) nặng và nhẹ. Mỗi chuỗi nặng sẽ được quản lý bởi một Segment Tree.
* **Độ phức tạp:** Truy vấn/Cập nhật trên đường đi mất $O(\log^2 N)$.
* **Ứng dụng:** Các bài toán "Update giá trị trên đường đi từ $u \to v$" và "Tính tổng trên đường đi $x \to y$".

### 5. Centroid Decomposition (Phân rã trọng tâm)
Kỹ thuật "chia để trị" trên cây, cực kỳ mạnh mẽ cho các bài toán liên quan đến khoảng cách hoặc đường đi thỏa mãn điều kiện $K$.
* **Chiến thuật:** Tìm trọng tâm (nút mà khi xóa đi, các thành phần liên thông còn lại có kích thước không quá $N/2$), xử lý các đường đi đi qua trọng tâm đó, sau đó đệ quy xuống các cây con.
* **Độ phức tạp:** $O(N \log N)$.


### 6. DSU on Tree (Sack)
Kỹ thuật này cho phép trả lời các truy vấn về "số lượng phần tử phân biệt" hoặc các tính chất thống kê trong từng cây con mà không cần tốn quá nhiều bộ nhớ như Mo's Algorithm trên cây.
* **Đặc điểm:** Tận dụng tư tưởng "giữ lại nhánh con nặng nhất" để giảm độ phức tạp xuống $O(N \log N)$.
* **Ưu điểm:** Cài đặt sạch sẽ hơn HLD trong nhiều trường hợp chỉ cần truy vấn cây con.

### 7. Steiner Tree (Cây con tối tiểu)
Chính là dạng bài **Phonominal Reviews** bạn vừa làm.
* **Bài toán:** Tìm cây con nhỏ nhất chứa một tập hợp các nút đích (terminal nodes).
* **Trường hợp đặc biệt:** Nếu số lượng nút đích nhỏ, có thể dùng DP trạng thái (Bitmask DP). Nếu cần quét hết như bài BOJ của bạn, ta dùng kỹ thuật Pruning (tỉa cây).

---

Trong các dạng trên, **Rerooting DP** và **Euler Tour + Segment Tree** là hai kỹ thuật thường xuất hiện nhất trong các kỳ thi. Bạn có muốn thử sức với một ví dụ cụ thể về **Rerooting DP** để thấy sự khác biệt so với cách làm DFS thông thường không?
