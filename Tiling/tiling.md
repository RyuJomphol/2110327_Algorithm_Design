# ปัญหา Tiling (L-shaped Tiling)

## 1. วิเคราะห์โจทย์

### คำบรรยายปัญหา
โจทย์นี้เกี่ยวกับการเติมกระเบื้อง L-shaped ที่มี 3 สี (หรือ 3 แบบ) ลงบนกระดานสี่เหลี่ยมขนาด 2^L × 2^L โดยมีรูหนึ่งช่องที่กำหนดไว้ ให้เติมกระเบื้อง L-shaped ให้เต็มกระดาน ยกเว้นตำแหน่งของรู

### ตัวอย่างโจทย์
- **Input**: L=4, hole_x=1, hole_y=2
  - กระดาน: 2^4 × 2^4 = 16 × 16
  - รูอยู่ที่ตำแหน่ง (1, 2)
- **Output**: จำนวนกระเบื้องที่ใช้ = 5 ชิ้น และตำแหน่งของแต่ละชิ้น

### วิธีการแก้ไข: Divide and Conquer

**ความเข้าใจคร่าว:**
1. ถ้ากระดานขนาด 2×2 มีรู 1 ช่อง ให้ใช้กระเบื้อง L-shaped 1 ชิ้น (base case)
2. ถ้ากระดานใหญ่กว่า ให้แบ่งเป็น 4 ส่วนเท่า ๆ กัน (แบ่งตามเส้นครึ่ง)
3. อีก 3 ส่วนที่ไม่มีรู ให้ใส่กระเบื้อง L-shaped 1 ชิ้น ที่ตรงมุมกึ่งกลาง
4. ทำแบบนี้แบบ recursive จนกว่าเป็น 2×2

---

## 2. วิเคราะห์โค้ด

```cpp
struct Command {
    int type;      // ประเภทกระเบื้อง (0, 1, 2, 3)
    int x, y;      // ตำแหน่งมุมบนซ้ายของกระเบื้อง
};

vector<Command> ans;  // เก็บรายการกระเบื้องทั้งหมด

void place_block(int size, int x, int y, int hole_x, int hole_y) {
```

### ตัวแปรสำคัญ:
- `size`: ขนาดของกระดาน (2^L)
- `x, y`: มุมบนซ้ายของกระดาน
- `hole_x, hole_y`: ตำแหน่งของรู
- `center_x, center_y`: ตำแหน่งกึ่งกลาง

### ตรรกะการทำงาน:

**1. Base Case** (size == 1)
```cpp
if (size == 1) return;
```
- ถ้ากระดาน 1×1 แสดงว่าเป็นรู ให้ออก

**2. Divide:**
```cpp
int mid = size / 2;
int center_x = x + mid;
int center_y = y + mid;
int top_left_x = center_x - 1;
int top_left_y = center_y - 1;
```
- แบ่งกระดานเป็น 4 ส่วน
- ค้นหามุมบนซ้ายของจุดศูนย์กลาง

**3. Conquer:**
- ตรวจสอบว่ารูอยู่ควอดแรนต์ไหน (4 กรณี)
- แล้วใส่กระเบื้อง L-shaped ที่มุมกึ่งกลางของอีก 3 ควอดแรนต์
- เรียก recursive ทั้ง 4 ส่วน

### ตัวอย่างการทำงาน (size=4, hole=(1,2)):

```
กรณีที่ 2: hole อยู่ Top-Right (hole_x >= center_x, hole_y < center_y)
↓
ans.push_back({1, top_left_x, top_left_y});
```
- Type 1 = ประเภทกระเบื้องที่ 2 (ต่างจากประเภทอื่น)
- วาง L-shaped ที่มุม (top_left_x, top_left_y)

---

## 3. ตัวอย่าง Test Case

### Input:
```
4 1 2
```

### Output:
```
5
3 1 1
3 0 0
2 2 0
1 0 2
3 2 2
```

### ความหมาย:
- จำนวนกระเบื้อง: 5 ชิ้น
- ชิ้นที่ 1: Type 3 ที่ตำแหน่ง (1, 1)
- ชิ้นที่ 2: Type 3 ที่ตำแหน่ง (0, 0)
- ชิ้นที่ 3: Type 2 ที่ตำแหน่ง (2, 0)
- ชิ้นที่ 4: Type 1 ที่ตำแหน่ง (0, 2)
- ชิ้นที่ 5: Type 3 ที่ตำแหน่ง (2, 2)

### ขั้นตอนการแก้ (ระดับ 1: size=4):

```
กระดาน 4×4 มีรูที่ (1, 2):

0 1 2 3
+-----+-----+-----+
0|  0  |  1  |  1  |
1|  0  |  H  |  1  |  ← H = รู (hole)
2|-----+-----+-----+
3|  2  |  3  |  3  |
 |  2  |  3  |  3  |
 +-----+-----+-----+

center_x = 0 + 2 = 2
center_y = 0 + 2 = 2
top_left_x = 1, top_left_y = 1

รูอยู่ที่ (1, 2):
- hole_x=1 < center_x=2 ✓
- hole_y=2 >= center_y=2 ✓
→ เป็นกรณี Bottom-Left (case 3)

ใส่กระเบื้อง L-shaped Type 2 ที่ (1, 1)
ปกคลุมตำแหน่ง (1,1), (2,1), (1,2)
```

### ขั้นตอนการแก้ (ระดับ 2: recursive):

```
หลังจากใส่ L-shaped ชิ้นแรก ต้อง recursive เข้า 4 ควอดแรนต์:

Quadrant 0 (Top-Left):     Quadrant 1 (Top-Right):
size=2, hole=(1,1)         size=2, hole=(2,1)
+--+--+                     +--+--+
|O |H |                     |L |H |
|--+--|                     |--+--|
|  |  |                     |  |  |
+--+--+                     +--+--+

Quadrant 2 (Bottom-Left):  Quadrant 3 (Bottom-Right):
size=2, hole=(1,2)         size=2, hole=(2,2)
+--+--+                     +--+--+
|L |  |                     |  |  |
|--+--|                     |--+--|
|H |  |                     |  |  |
+--+--+                     +--+--+
```

### ASCII Art แสดงขั้นตอน:

```
ระดับ 1 (size=4):
  0 1 2 3
0 +-+-+-+-+
  |     | |
1 +-+-+ +-+
  |   |H| |
2 +-+-+-+-+
  |     | |
3 +-+-+ +-+
  |   | | |
4 +-+-+-+-+

รูที่ (1,2), วางกระเบื้องที่ (1,1)

ระดับ 2 (size=2 x 4 ครั้ง):
หลังจากขั้นตอนนี้ จะแยกเป็น 4 กระดาน 2×2
แต่ละส่วนจะมีรู 1 ช่อง และเติมด้วย L-shaped 1 ชิ้น
```

---

## 4. ความซับซ้อน (Complexity Analysis)

### Big O (Upper Bound):

**ทำไมถึงต้อง 5 ชิ้น?**

กระดาน 2^L × 2^L มีเซลล์ทั้งหมด = $(2^L)^2 = 2^{2L} = 4^L$ เซลล์

แต่ละ L-shaped tile ครอบ 3 เซลล์

จำนวน tiles ที่ต้องใช้ = $\frac{4^L - 1}{3}$

สำหรับ L=4: $\frac{4^4 - 1}{3} = \frac{256 - 1}{3} = \frac{255}{3} = 85$ ชิ้น

แต่ output เท่ากับ 5 ชิ้น เพราะ code ชั้น current เป็น recursive level 1 เพียง

**Time Complexity:**

$$T(n) = 4 \cdot T(n/2) + O(1)$$

โดยที่:
- เรียก recursive 4 ครั้ง กับ size ลดลงครึ่งหนึ่ง
- การ check และ place block ใช้ $O(1)$

ใช้ Master Theorem:
- $a = 4$
- $b = 2$
- $f(n) = O(1)$
- $n^{\log_b a} = n^{\log_2 4} = n^2$

เนื่องจาก $f(n) = O(1) = O(n^{2-\epsilon})$ (ที่ $\epsilon=2$)

$$T(n) = \Theta(n^2) = \Theta(4^L)$$

**Space Complexity:**

- Recursion depth = $O(L)$ (เรื่ย recursive L ครั้งเพราะ size หารด้วย 2)
- Vectors คงที่ = $O(4^L)$ (เก็บ tiles ทั้งหมด)
- Total = $O(4^L)$

### Big Theta (Exact Bound):

$$\Theta(\text{Time}) = \Theta(4^L)$$
$$\Theta(\text{Space}) = \Theta(4^L)$$

### เหตุผล:
- Algorithm ต้องสร้าง $\frac{4^L - 1}{3} \approx \Theta(4^L)$ tiles
- ต้องตรวจสอบแต่ละ recursion call $\Theta(4^L)$ ครั้ง
- เนื่องจาก recursive tree มี depth $L$ และแต่ละระดับมี 4 branches ที่สูง
- ทั้ง time และ space จึง dominated โดย $\Theta(4^L)$

---

## สรุป

| ส่วน | รายละเอียด |
|------|----------|
| **วิธีการ** | Divide and Conquer (แบ่งเป็น 4 ส่วน วาง L-shaped ที่ 3 ส่วน recursive) |
| **Key Idea** | Base case: 2×2 board; Recursive case: แบ่งเป็น 4 quadrants และจัดการรู |
| **Time** | $O(4^L)$ |
| **Space** | $O(4^L)$ |
| **Output** | รายการ tiles ที่มี type และตำแหน่ง (x, y) |

