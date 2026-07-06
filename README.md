- Lưu ý:
+ khi implement -> chú ý tính independant vừa kiểm tra vừa update vùng dữ liệu có thể dẫn đến sai state
        https://github.com/nhannv56/algorithm/edit/master/acmicpc.net/problem/2026/Q4/05_8972_roboti.cpp

---

## Danh sách Giải Thuật (Algorithms)

### algo: BFS (Breadth-First Search)
**Dấu hiệu nhận biết:**
- Tìm đường đi ngắn nhất trên đồ thị không có trọng số
- Duyệt theo từng bậc (layer-by-layer)
- Bài toán flood fill, tìm liên thông, khoảng cách nhỏ nhất trên lưới

**Cách hoạt động:**
- Dùng queue (FIFO), đưa đỉnh bắt đầu vào queue
- Lấy đỉnh từ đầu queue, duyệt tất cả đỉnh kề chưa thăm, đưa vào queue
- Lặp cho đến khi queue rỗng, đảm bảo mỗi đỉnh được thăm theo thứ tự khoảng cách tăng dần

**Files:** 1068_tree.cpp, 01_alicecub.cpp, 012-find-the-safest-path-in-a-grid.cpp, 013-find-a-safe-walk-through-a-grid.cpp, 13141_ignition.cpp, acmicpc_12793.cpp, acmicpc_15160.cpp, 10399_event_distribution.cpp, 1167_tree_longest_path.cpp, 32161_decrease_land.cpp, 28309_collecting_snacks.cpp, 25902_rising_tides.cpp, 25789_rcv_simplification.cpp

---

### algo: DFS (Depth-First Search)
**Dấu hiệu nhận biết:**
- Duyệt toàn bộ cây/đồ thị
- Tìm tất cả đường đi, kiểm tra liên thông
- Bài toán trên cây: tính subtree, duyệt con

**Cách hoạt động:**
- Dùng đệ quy hoặc stack (LIFO)
- Từ đỉnh hiện tại, đi sâu vào một đỉnh kề chưa thăm cho đến khi không còn đi được
- Quay lui và thử nhánh tiếp theo

**Files:** 1068_tree.cpp, 19240_toys.cpp, 18785_clock_tree.cpp, 14044_Phonomenal_Reviews.cpp

---

### algo: Dijkstra
**Dấu hiệu nhận biết:**
- Đồ thị có trọng số dương, tìm đường đi ngắn nhất từ một nguồn
- Cạnh có chi phí khác nhau
- Không có cạnh âm

**Cách hoạt động:**
- Dùng min-heap (priority queue), khởi tạo dist[start]=0, dist[other]=INF
- Mỗi lần lấy đỉnh có dist nhỏ nhất, relaxation: dist[v] = min(dist[v], dist[u] + w(u,v))
- Tiếp tục cho đến khi heap rỗng, O((V+E) log V)

**Files:** 04_ada_trip.cpp, 1162_Revamping_Trails.cpp, 1800.cpp, 015-network-recovery-pathways.cpp, 17270_celebrity.cpp, 27281.cpp, 13308_gas_station.cpp, 5719_almost_shortest_path.cpp

---

### algo: Floyd-Warshall
**Dấu hiệu nhận biết:**
- Tìm đường đi ngắn nhất giữa **tất cả** cặp đỉnh
- N nhỏ (N ≤ 500)
- Có thể có cạnh âm (nhưng không có chu trình âm)

**Cách hoạt động:**
- dp[i][j][k] = đường đi ngắn nhất từ i đến j đi qua tập đỉnh trung gian {1..k}
- Công thức: `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])` với mọi k
- O(V³)

**Files:** 13141_ignition.cpp, 27373_shortest_path_game.cpp, floys.cpp

---

### algo: Binary Search
**Dấu hiệu nhận biết:**
- Mảng hoặc hàm có tính đơn điệu (monotone)
- Bài toán "tìm giá trị nhỏ nhất/lớn nhất thỏa điều kiện"
- Khoảng giá trị rất lớn nhưng kiểm tra điều kiện O(N) hoặc O(N log N)

**Cách hoạt động:**
- Duy trì khoảng [lo, hi], mỗi bước thu hẹp một nửa
- Kiểm tra mid, nếu thỏa: tìm nửa trái/phải tùy mục tiêu
- O(log N) mỗi lần tìm kiếm

**Files:** 02_books_copy.cpp, 08_most_serving_meal.cpp, 1800.cpp, 2539.cpp, 32956_box.cpp, 015-network-recovery-pathways.cpp, 016-minimum-removals-to-balance-array.cpp, 25779_which_number.cpp, 27362_couting_special_int_pairs.cpp, 25792_stone_smoothing.cpp, 2962_svada.cpp, 25112_signle_stack_railway.cpp, 24579_concert_rehearsal.cpp

---

### algo: Parametric Search (Binary Search on Answer)
**Dấu hiệu nhận biết:**
- Bài toán "tìm giá trị tham số nhỏ nhất/lớn nhất sao cho tồn tại một phương án"
- Hàm feasibility có tính đơn điệu theo tham số
- Thường kết hợp với greedy hoặc DP để kiểm tra điều kiện

**Cách hoạt động:**
- Binary search trên giá trị tham số (ví dụ: thời gian, chi phí, khoảng cách)
- Với mỗi giá trị mid, kiểm tra xem bài toán có giải được không (feasible check)
- Thu hẹp khoảng tìm kiếm cho đến khi tìm ra biên

**Files:** 02_books_copy.cpp, 08_most_serving_meal.cpp, 1800.cpp, 28312_secure_robots.cpp

---

### algo: Dynamic Programming (DP)
**Dấu hiệu nhận biết:**
- Bài toán có tính chất optimal substructure và overlapping subproblems
- Câu hỏi "số cách", "giá trị lớn nhất/nhỏ nhất", "có thể đạt được không"
- Trạng thái có thể được mô tả bằng vài tham số

**Cách hoạt động:**
- Định nghĩa trạng thái dp[i] hoặc dp[i][j]...
- Tìm công thức chuyển trạng thái (recurrence relation)
- Tính từ trạng thái cơ sở (base case) lên, hoặc dùng memoization top-down
- Đảm bảo mỗi trạng thái tính đúng một lần

**Files:** 01_alicecub.cpp, 07_acmarker.cpp, 11062_card_game.cpp, 2098_traveling_sale_mans.cpp, 12013_game_2048.cpp, 003-maximum-absolute-sum-of-any-subarray.cpp, 004-maximum-product-subarray.cpp, 009-number-of-zigzag-arrays-1.cpp, 010-number-of-zigzag-arrays-2.cpp, 3114.cpp, 27361_stick_cutting.cpp, 3037_zbrka.cpp, 25806.cpp, acmicpc_26107.cpp, 25845_Hidden_Message.cpp, 25218_cutting_the_cake.cpp, 8895_Pole_arrangement.cpp, 24756_protect_the_pollen.cpp, 28096_meal_deliver.cpp, 34490_number_reduction.cpp, 17279_odd_subsequences.cpp

---

### algo: Bitmask DP / TSP (Traveling Salesman Problem)
**Dấu hiệu nhận biết:**
- Số phần tử N nhỏ (thường ≤ 20)
- Trạng thái là tập con của tập hợp phần tử
- Bài toán cần thăm tất cả các điểm, tìm chi phí tối ưu

**Cách hoạt động:**
- Biểu diễn tập con bằng bitmask (số nguyên, bit thứ i = 1 nếu phần tử i đã chọn)
- dp[mask][i] = chi phí tối ưu khi đã thăm tập điểm mask, đang ở điểm i
- Chuyển trạng thái: `dp[mask | (1<<j)][j] = min(..., dp[mask][i] + cost[i][j])`
- O(2^N * N²)

**Files:** 2098_traveling_sale_mans.cpp, 28096_meal_deliver.cpp, 30300_and_mex.cpp

---

### algo: Greedy
**Dấu hiệu nhận biết:**
- Tại mỗi bước, lựa chọn cục bộ tối ưu dẫn đến kết quả toàn cục tối ưu
- Có thể chứng minh tính đúng đắn bằng exchange argument
- Thường kết hợp với sắp xếp

**Cách hoạt động:**
- Sắp xếp dữ liệu theo tiêu chí phù hợp
- Duyệt qua và chọn phương án tốt nhất tại mỗi bước mà không cần xét lại

**Files:** 02_books_copy.cpp, 25093.cpp, 014-maximum-element-after-decreasing-and-rearranging.cpp, 19241_pirates.cpp, 24470_autobus.cpp, 25789_rcv_simplification.cpp, 34648_Armageddon.cpp

---

### algo: Backtracking
**Dấu hiệu nhận biết:**
- Liệt kê tất cả tổ hợp/hoán vị thỏa mãn điều kiện
- N nhỏ, không gian trạng thái vừa
- Có thể cắt nhánh (pruning) sớm

**Cách hoạt động:**
- Duyệt đệ quy tất cả khả năng
- Khi không thỏa mãn điều kiện, quay lui (undo) và thử lựa chọn khác
- Cắt nhánh để giảm không gian tìm kiếm

**Files:** 03_digger_octaves.cpp, 09_SUBSUMP.cpp, 28094.cpp, 27372_mini_bigo.cpp, 31813.cpp

---

### algo: Binary Lifting / LCA (Lowest Common Ancestor)
**Dấu hiệu nhận biết:**
- Bài toán trên cây: tìm tổ tiên chung gần nhất
- Truy vấn khoảng cách giữa hai đỉnh trên cây
- Tìm tổ tiên thứ k của một đỉnh

**Cách hoạt động:**
- Tiền xử lý: ancestor[v][k] = tổ tiên thứ 2^k của v
- Xây dựng bằng: `ancestor[v][k] = ancestor[ancestor[v][k-1]][k-1]`
- LCA: nâng hai đỉnh lên cùng độ sâu, rồi đồng thời nhảy 2^k bậc
- O(N log N) preprocessing, O(log N) mỗi truy vấn

**Files:** 06_kingdom_of_equality.cpp

---

### algo: Union-Find (Disjoint Set Union / DSU)
**Dấu hiệu nhận biết:**
- Quản lý các tập hợp rời nhau
- Kiểm tra hai phần tử có cùng nhóm không
- Gộp hai nhóm lại với nhau
- Bài toán liên thông, MST (Kruskal)

**Cách hoạt động:**
- Mỗi phần tử có parent[], lúc đầu parent[i]=i
- `find(x)`: tìm đại diện nhóm của x (path compression)
- `union(x,y)`: gộp nhóm của x và y (union by rank/size)
- Gần O(1) mỗi thao tác (amortized)

**Files:** 006-minimum-cost-walk-in-weighted.cpp, 32161_decrease_land.cpp

---

### algo: Segment Tree
**Dấu hiệu nhận biết:**
- Truy vấn và cập nhật trên đoạn (range query, point update)
- Ví dụ: tổng đoạn, min/max đoạn, đếm trên đoạn
- Cần cả update và query hiệu quả

**Cách hoạt động:**
- Xây dựng cây nhị phân hoàn chỉnh lưu thông tin từng đoạn
- Node i lưu thông tin của đoạn [l,r], con trái [l,mid], con phải [mid+1,r]
- Query/Update: đi từ gốc xuống, chia đôi đoạn tại mỗi node
- O(log N) mỗi thao tác

**Files:** 26183_justice_served.cpp, 32322.cpp, 25112_signle_stack_railway.cpp

---

### algo: Fenwick Tree / Binary Indexed Tree (BIT)
**Dấu hiệu nhận biết:**
- Truy vấn tổng prefix (prefix sum) có cập nhật điểm
- Đơn giản hơn Segment Tree, bộ nhớ ít hơn
- Không hỗ trợ range update trực tiếp (trừ khi dùng difference array)

**Cách hoạt động:**
- Mỗi vị trí i chịu trách nhiệm một đoạn có độ dài bằng least significant bit của i
- Update: `i += i & (-i)` để cập nhật tất cả nút cha
- Query: `i -= i & (-i)` để tổng hợp prefix sum
- O(log N) mỗi thao tác

**Files:** 1797.cpp

---

### algo: Trie Tree
**Dấu hiệu nhận biết:**
- Lưu trữ và tìm kiếm chuỗi theo tiền tố (prefix)
- Bài toán autocomplete, IP routing, XOR max
- Đếm số chuỗi bắt đầu bằng một prefix

**Cách hoạt động:**
- Cây với mỗi cạnh là một ký tự
- Insert: duyệt từng ký tự, tạo node mới nếu chưa có
- Search: kiểm tra từng ký tự theo đường đi từ gốc
- O(L) mỗi thao tác với L là độ dài chuỗi

**Files:** 12055_ip_address_sumariation.cpp, acmicpc_12055_trie_tree.cpp, 27185_the_tree.cpp, 32584_annoying_aliterations.cpp

---

### algo: Monotonic Stack / Queue
**Dấu hiệu nhận biết:**
- Tìm phần tử lớn/nhỏ hơn gần nhất bên trái/phải (Next Greater Element)
- Sliding window min/max trong O(N)
- Bài toán histogram, largest rectangle

**Cách hoạt động:**
- Duy trì stack/deque tăng hoặc giảm
- Khi thêm phần tử mới, pop tất cả phần tử không thỏa điều kiện đơn điệu
- Phần tử bị pop: phần tử hiện tại là "next greater/smaller" của nó
- O(N) tổng thể vì mỗi phần tử push/pop tối đa 1 lần

**Files:** 21982.cpp, 2433.cpp, 31856_leak.cpp

---

### algo: Two Pointer / Sliding Window
**Dấu hiệu nhận biết:**
- Tìm đoạn con thỏa điều kiện (subarray problem)
- Điều kiện có tính đơn điệu: khi mở rộng cửa sổ thỏa mãn thì thu hẹp không thỏa nữa
- Mảng đã sắp xếp, tìm cặp phần tử thỏa điều kiện

**Cách hoạt động:**
- Duy trì hai con trỏ l, r
- Di chuyển r để mở rộng cửa sổ, di chuyển l để thu hẹp khi không thỏa điều kiện
- O(N) vì mỗi con trỏ di chuyển tối đa N bước

**Files:** 2433.cpp, 011-number-of-substrings-containing-all-three-characters.cpp, 016-minimum-removals-to-balance-array.cpp, 3151.cpp, 23077_festival.cpp, 29892_gameboard.cpp

---

### algo: Sweep Line
**Dấu hiệu nhận biết:**
- Bài toán liên quan đến các khoảng (intervals), hình chữ nhật, điểm trên trục
- Sắp xếp theo một chiều và xử lý sự kiện theo thứ tự
- Thường kết hợp với Segment Tree, set, hoặc heap

**Cách hoạt động:**
- Tạo danh sách sự kiện (events) theo tọa độ x hoặc thời gian
- Sắp xếp events, dùng cấu trúc dữ liệu để duy trì trạng thái "đường quét"
- Xử lý từng sự kiện, cập nhật cấu trúc dữ liệu

**Files:** 17788_gluttonous_goop.cpp, 15770_QueryeuQ.cpp

---

### algo: Prefix Sum
**Dấu hiệu nhận biết:**
- Truy vấn tổng đoạn nhiều lần, không cập nhật
- Tổng 2D, đếm số phần tử thỏa điều kiện trong đoạn
- Cần tính nhanh sum(l,r) = prefix[r] - prefix[l-1]

**Cách hoạt động:**
- Xây dựng mảng prefix: `prefix[i] = prefix[i-1] + a[i]`
- Truy vấn sum(l,r) trong O(1)
- Với 2D: `prefix[i][j] = a[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]`

**Files:** 005-minimum-cost-to-move-between-indices.cpp, 10800_ball_color.cpp, 12055_ip_address_sumariation.cpp, 3037_zbrka.cpp, 9077.cpp, 28312_secure_robots.cpp, 23000.cpp, acmicpc_34649.cpp, 25218_cutting_the_cake.cpp, 25112_signle_stack_railway.cpp

---

### algo: Matrix Exponentiation
**Dấu hiệu nhận biết:**
- Tính F(n) với n rất lớn (10^18) theo công thức tuyến tính
- Fibonacci, recurrence tuyến tính bậc k
- Đếm số đường đi độ dài n trong đồ thị

**Cách hoạt động:**
- Biểu diễn recurrence dưới dạng nhân ma trận: `V(n) = M * V(n-1)`
- `V(n) = M^n * V(0)` - tính M^n bằng fast exponentiation
- O(k³ log n) với k là kích thước ma trận

**Files:** 11440_sqr_fibo.cpp, 13430_sum_matrix.cpp, 23891_ask_drink_double.cpp, 010-number-of-zigzag-arrays-2.cpp

---

### algo: Sieve of Eratosthenes
**Dấu hiệu nhận biết:**
- Tìm tất cả số nguyên tố đến N
- Phân tích nhân tử nguyên tố
- Liên quan đến số nguyên tố, ước số

**Cách hoạt động:**
- Khởi tạo mảng is_prime[] = true
- Với mỗi p từ 2 đến sqrt(N): nếu is_prime[p], đánh dấu tất cả bội số p² trở lên là false
- O(N log log N)

**Files:** 19595_prime_number_game.cpp, 24326_maximal_sum.cpp, 1016_no_square_no_number.cpp

---

### algo: Game Theory / Sprague-Grundy / Nim
**Dấu hiệu nhận biết:**
- Hai người chơi lần lượt thực hiện nước đi
- Người không đi được là thua (normal play convention)
- Tổ hợp nhiều trò chơi độc lập

**Cách hoạt động:**
- Tính Grundy number (nimber) cho mỗi trạng thái: `G(s) = mex{G(s') | s' kế tiếp của s}`
- Với tổ hợp trò chơi: XOR tất cả Grundy number
- Nếu XOR ≠ 0: người đi trước thắng; XOR = 0: người đi trước thua

**Files:** 19595_prime_number_game.cpp

---

### algo: LCS (Longest Common Subsequence)
**Dấu hiệu nhận biết:**
- Tìm dãy con chung dài nhất của hai chuỗi
- Bài toán chỉnh sửa chuỗi, so khớp DNA
- Trực giác: dp[i][j] phụ thuộc vào dp[i-1][j-1], dp[i-1][j], dp[i][j-1]

**Cách hoạt động:**
- `dp[i][j]` = LCS của s1[0..i-1] và s2[0..j-1]
- Nếu s1[i]==s2[j]: `dp[i][j] = dp[i-1][j-1] + 1`
- Ngược lại: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`
- O(N*M)

**Files:** acmicpc_26107.cpp, 26342_Palindrome_Maker_1.cpp

---

### algo: Inclusion-Exclusion Principle (Bao hàm - Loại trừ)
**Dấu hiệu nhận biết:**
- Đếm số phần tử thỏa ít nhất/nhiều nhất k trong n điều kiện
- N điều kiện nhỏ (≤ 20), có thể dùng bitmask
- Bài toán đếm với nhiều ràng buộc chồng chéo

**Cách hoạt động:**
- |A∪B| = |A| + |B| - |A∩B|
- Với bitmask: duyệt tất cả 2^n tập con, cộng/trừ luân phiên theo số bit
- O(2^N * cost_per_subset)

**Files:** 25779_which_number.cpp

---

### algo: Minimum Spanning Tree (MST) - Prim / Kruskal
**Dấu hiệu nhận biết:**
- Tìm cây khung có tổng trọng số nhỏ nhất
- Kết nối tất cả đỉnh với chi phí nhỏ nhất
- Đồ thị vô hướng có trọng số

**Cách hoạt động:**
- **Kruskal**: sắp xếp cạnh theo trọng số, thêm cạnh nếu không tạo chu trình (Union-Find)
- **Prim**: tương tự Dijkstra, tham lam thêm đỉnh gần nhất vào cây MST
- O(E log E) Kruskal, O((V+E) log V) Prim

**Files:** 2887_SVEMIR.cpp

---

### algo: Tree DP / Knapsack on Tree
**Dấu hiệu nhận biết:**
- Bài toán tối ưu trên cây, chọn tập con đỉnh/cạnh thỏa ràng buộc
- DP tính từ lá lên gốc
- Kết hợp kết quả các cây con

**Cách hoạt động:**
- `dp[v][...]` = kết quả tối ưu cho subtree gốc v với trạng thái ...
- Duyệt DFS, sau khi xử lý xong tất cả con mới tính dp[v]
- Tree knapsack: merge dp các cây con bằng convolution O(N²) hoặc O(N log N)

**Files:** 24756_protect_the_pollen.cpp, 14044_Phonomenal_Reviews.cpp

---

### algo: Bipartite Graph / Graph Coloring
**Dấu hiệu nhận biết:**
- Kiểm tra xem đồ thị có thể tô màu bằng 2 màu không
- Bài toán matching, scheduling với 2 nhóm
- Đồ thị không có chu trình lẻ ⟺ đồ thị 2 phía

**Cách hoạt động:**
- BFS/DFS tô màu xen kẽ 0 và 1
- Nếu gặp cạnh nối 2 đỉnh cùng màu → không phải đồ thị 2 phía
- Bipartite matching dùng Hopcroft-Karp hoặc augmenting path

**Files:** 19240_toys.cpp

---

### algo: LIS (Longest Increasing Subsequence)
**Dấu hiệu nhận biết:**
- Tìm dãy con tăng dài nhất
- Bài toán patience sorting, đặt hộp chồng lên nhau
- Kết hợp với binary search để đạt O(N log N)

**Cách hoạt động:**
- Duy trì mảng `tails[]`: `tails[i]` = phần tử cuối nhỏ nhất của dãy con tăng độ dài i+1
- Với mỗi phần tử x: tìm vị trí lower_bound trong tails, thay thế hoặc mở rộng
- Độ dài tails[] cuối cùng là LIS
- O(N log N)

**Files:** 3745_stock_exchange.cpp

---

### algo: Modular Arithmetic / Fermat's Little Theorem
**Dấu hiệu nhận biết:**
- Kết quả rất lớn, yêu cầu lấy mod 10^9+7
- Tính nghịch đảo modulo (modular inverse)
- Tính C(n,k) mod p

**Cách hoạt động:**
- Fermat: a^(p-1) ≡ 1 (mod p) với p nguyên tố → a^(-1) ≡ a^(p-2) (mod p)
- Fast exponentiation: `pow(a, b, mod)` trong O(log b)
- Tính factorial và inverse factorial để tính C(n,k)

**Files:** 25334_long_cake.cpp, 34648_Armageddon.cpp

---

### algo: Combinatorics (Tổ hợp C(n,k))
**Dấu hiệu nhận biết:**
- Đếm số cách chọn, sắp xếp
- Pascal's triangle, stars and bars
- Đếm đường đi trên lưới, số cách phân chia

**Cách hoạt động:**
- Tiền xử lý factorial và inverse factorial
- `C(n,k) = fact[n] * inv_fact[k] * inv_fact[n-k] % MOD`
- Hoặc dùng Pascal's triangle: `C[n][k] = C[n-1][k-1] + C[n-1][k]`

**Files:** 25334_long_cake.cpp, 23019_the_swirl_game.cpp, 24326_maximal_sum.cpp

---

### algo: Priority Queue / Heap
**Dấu hiệu nhận biết:**
- Cần lấy phần tử lớn nhất/nhỏ nhất liên tục
- Kết hợp với Dijkstra, Prim, hoặc các thuật toán tham lam
- Xử lý sự kiện theo độ ưu tiên

**Cách hoạt động:**
- Min-heap: phần tử nhỏ nhất luôn ở đỉnh
- Push O(log N), pop O(log N), peek O(1)
- Trong C++: `priority_queue<int, vector<int>, greater<int>>` cho min-heap

**Files:** 012-find-the-safest-path-in-a-grid.cpp, 013-find-a-safe-walk-through-a-grid.cpp, 015-network-recovery-pathways.cpp, 27281.cpp, 13308_gas_station.cpp

---

### algo: Divide and Conquer
**Dấu hiệu nhận biết:**
- Bài toán có thể chia thành các phần độc lập nhau
- Kết quả toàn phần = hàm của kết quả từng phần
- Merge sort, closest pair of points, FFT

**Cách hoạt động:**
- Divide: chia bài toán thành 2 nửa
- Conquer: giải đệ quy mỗi nửa
- Combine: gộp kết quả lại
- O(N log N) nếu combine O(N)

**Files:** 5904_Moo.cpp

---

### algo: Geometry (Hình học tính toán)
**Dấu hiệu nhận biết:**
- Bài toán với điểm, đoạn thẳng, đa giác trên mặt phẳng
- Tính diện tích, chu vi, giao điểm
- Convex hull, point in polygon

**Cách hoạt động:**
- Diện tích đa giác: công thức shoelace `|Σ(x_i * y_{i+1} - x_{i+1} * y_i)| / 2`
- Cross product để kiểm tra hướng quay, giao cắt
- Convex hull: Graham scan hoặc Andrew's monotone chain O(N log N)

**Files:** acmicpc_30223.cpp, 25792_stone_smoothing.cpp, 25112_signle_stack_railway.cpp

---

### algo: Topological Sort
**Dấu hiệu nhận biết:**
- Đồ thị có hướng không có chu trình (DAG)
- Thứ tự thực hiện công việc có phụ thuộc
- Bài toán "task scheduling", phụ thuộc gói phần mềm

**Cách hoạt động:**
- **Kahn's algorithm**: dùng queue, bắt đầu từ đỉnh in-degree = 0
- **DFS-based**: DFS và push vào stack khi thoát node, đảo ngược stack
- O(V+E)

**Files:** 2637_assemble_toys.cpp

---

### algo: Sparse Table / RMQ (Range Minimum Query)
**Dấu hiệu nhận biết:**
- Truy vấn min/max trên đoạn tĩnh (không cập nhật)
- Cần O(1) mỗi truy vấn sau preprocessing
- Thường dùng kết hợp với LCA

**Cách hoạt động:**
- Tiền xử lý: `sparse[k][i]` = min của đoạn [i, i+2^k-1]
- `sparse[k][i] = min(sparse[k-1][i], sparse[k-1][i+2^{k-1}])`
- Query(l,r): `min(sparse[k][l], sparse[k][r-2^k+1])` với k = log₂(r-l+1)
- O(N log N) preprocessing, O(1) query

**Files:** 5904_Moo.cpp, 7_acmarker.cpp

---

### algo: Euler Tour / DFS Order on Tree
**Dấu hiệu nhận biết:**
- Biến truy vấn trên subtree thành truy vấn trên đoạn mảng
- Đánh số thứ tự in/out của mỗi node khi DFS
- Kết hợp với Segment Tree hoặc BIT để cập nhật subtree

**Cách hoạt động:**
- DFS, gán `in[v]` khi bước vào và `out[v]` khi bước ra
- Tất cả đỉnh trong subtree của v nằm trong đoạn `[in[v], out[v]]`
- Biến subtree query → range query trên mảng Euler tour

**Files:** 1068_tree.cpp, 2637_assemble_toys.cpp



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

8.Parametric Search
