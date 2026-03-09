/***

https://www.acmicpc.net/problem/17788
Mỗi ô nấm (#) sau k bước sẽ lan theo quy tắc:

Mỗi bước, nó lan ra 8 hướng (N, S, E, W, và 4 đường chéo).
Nghĩa là sau k bước, từ một ô ban đầu tại tọa độ (x, y) ta bao phủ một hình vuông có cạnh = (2k+1), tâm là (x, y).

Quan sát quan trọng:
Chiều lan theo 8 hướng tương đương norm L∞, nghĩa là:

Tập các điểm cách ô ban đầu không quá k theo metric L∞:
|dx| ≤ k và |dy| ≤ k.

→ Ta không cần mô phỏng từng bước, mà chỉ cần lấy hợp của nhiều hình vuông (2k+1)×(2k+1).
Input cho ban đầu chỉ là một grid nhỏ (tối đa 20×20), nhưng k có thể lên đến 10⁶, nên hình vuông mở rộng có cạnh ~2×10⁶, quá lớn để duyệt lưới.
Tuy nhiên:

Số ô ban đầu có nấm <= 400
Mỗi ô nấm tạo thành một hình vuông rất lớn.
Cần tính diện tích hợp của tất cả hình vuông đó.

Đây là bài toán hình học:

Cho N hình vuông trục song song cực lớn.
Tính diện tích phần hợp của chúng.
3. Công thức biểu diễn hình vuông
Nếu tại thời điểm ban đầu, ô (i, j) là #, thì:

Tại thời điểm k, nấm phủ hình vuông:

[x0 = i - k,  x1 = i + k]
[y0 = j - k,  y1 = j + k]

→ Đây là một hình chữ nhật trục song song.
Toàn bộ bài toán là hợp của nhiều hình chữ nhật.
4. Ý tưởng giải hình học: Sweep line theo trục X
Vì số ô ban đầu ≤ 400, số hình vuông ≤ 400.
Bài toán kinh điển:
Tính diện tích hợp của nhiều hình chữ nhật.
Phương pháp chuẩn:

Với mỗi hình vuông, tạo hai "sự kiện":

x = x0: add đoạn [y0, y1]
x = x1 + 1: remove đoạn [y0, y1]
Sort tất cả sự kiện theo x tăng dần.
Dùng segment tree / interval merging để duy trì tổng độ dài các đoạn phủ theo trục y.
Khi quét từ x = cur đến x = next:
diện tích cộng thêm = (next - cur) * (độ dài phủ trên trục y).
→ Độ phức tạp: O(N log N) với N ~ 400 → rất thoải mái.
**/
