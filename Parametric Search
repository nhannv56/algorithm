**Parametric Search** là một **kỹ thuật thuật toán** (không phải 1 thuật toán cụ thể) dùng để **tìm giá trị tối ưu (min/max)** của một tham số **bằng cách kết hợp Binary Search với một hàm kiểm tra (check)**.

Nói ngắn gọn:

> 👉 **Parametric Search = Binary Search trên đáp án**

***

## 1. Khi nào dùng Parametric Search?

Dùng khi bài toán có dạng:

*   Ta cần tìm **giá trị tốt nhất** (nhỏ nhất / lớn nhất) của một số $$x$$
*   Với mỗi $$x$$, ta **có thể kiểm tra**:
    *   `x có thỏa điều kiện không?` (YES / NO)
*   Và điều kiện đó có tính **đơn điệu (monotonic)**

Ví dụ đơn điệu:

    x nhỏ  => KHÔNG thỏa
    x vừa  => KHÔNG thỏa
    x lớn  => THỎA
    x lớn hơn nữa => THỎA

hoặc ngược lại.

***

## 2. Ý tưởng cốt lõi

Ta không tìm trực tiếp nghiệm tối ưu, mà:

1.  **Đoán một giá trị x**
2.  **Kiểm tra x có hợp lệ không**
3.  Nếu hợp lệ → thử tốt hơn
4.  Nếu không → loại bỏ

→ **Dùng Binary Search trên miền đáp án**

***

## 3. Ví dụ cực kinh điển

### Bài toán

> Có N máy, mỗi máy i sản xuất `a[i]` sản phẩm / ngày.  
> Bạn cần sản xuất **≥ K sản phẩm**.  
> Hỏi **ít nhất bao nhiêu ngày**?

***

### Phân tích

*   Đáp án là **số ngày D**
*   Với mỗi D:
        tổng = sum(a[i] * D)
*   Nếu `tổng ≥ K` → D hợp lệ
*   Nếu `tổng < K` → D không hợp lệ

👉 Điều kiện **đơn điệu**:

*   D nhỏ → không đủ
*   D lớn → đủ

***

### Pseudocode

```cpp
bool check(long long D) {
    long long total = 0;
    for (i = 1..N)
        total += a[i] * D;
    return total >= K;
}
```

```cpp
long long l = 0, r = 1e18, ans;
while (l <= r) {
    mid = (l + r) / 2;
    if (check(mid)) {
        ans = mid;
        r = mid - 1;   // tìm ngày nhỏ hơn
    } else {
        l = mid + 1;
    }
}
```

***

## 4. Vì sao gọi là “Parametric Search”?

*   Ta **tham số hóa bài toán theo x**
*   Với mỗi giá trị x, bài toán trở thành:
    > “x có thỏa không?”
*   Sau đó tìm **giá trị tham số tối ưu**

📌 Nguồn gốc từ Megiddo (1983), nhưng trong competitive programming hiểu đơn giản là:

> **Binary search answer**

***

## 5. Những dấu hiệu nhận biết Parametric Search

Khi đọc đề, nếu bạn thấy:

✅ “ít nhất / nhiều nhất”  
✅ “tối ưu”  
✅ “minimize / maximize”  
✅ có thể viết hàm `check(x)`  
✅ điều kiện **true/false đơn điệu**

→ 90% là Parametric Search

***

## 6. Các dạng bài thường gặp

### ✔︎ 1. Chia đoạn / phân phối

*   Chia k người, mỗi người nhận ≤ x
*   Chia mảng thành ≤ k đoạn với tổng ≤ x

### ✔︎ 2. Khoảng cách / thời gian

*   Khoảng cách nhỏ nhất
*   Thời gian ít nhất

### ✔︎ 3. Năng lực / công suất

*   Máy móc
*   Worker làm việc

***

## 7. So sánh nhanh

| Kỹ thuật             | Ý tưởng                |
| -------------------- | ---------------------- |
| Binary Search thường | Search trên mảng       |
| Parametric Search    | Search trên **đáp án** |
| DP                   | Trạng thái             |
| Greedy               | Quyết định cục bộ      |

***

## 8. Lỗi thường gặp ❌

1.  **Check không đơn điệu**
2.  Giới hạn `l, r` sai
3.  Overflow khi tính toán
4.  Nhầm min ↔ max

***

## 9. Một câu “kim chỉ nam”

> Nếu bạn **không biết đáp án là gì**,  
> nhưng **biết cách kiểm tra một đáp án có đúng không**,  
> → **Parametric Search**

***

Nếu bạn muốn:

*   ví dụ **BOJ cụ thể**
*   giải **1 bài code thật**
*   hoặc so sánh với **Ternary Search**

👉 cứ nói, mình dạy tiếp từng mức 👌
