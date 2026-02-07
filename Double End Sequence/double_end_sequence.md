# Double End Sequence

## 1. วิเคราะห์โจทย์
โจทย์: ให้ลำดับของจำนวนเต็ม หา subarray ต่อเนื่องที่ "มีค่าเริ่มต้นและสิ้นสุดเท่ากัน" (first element == last element) และให้ผลรวมของ subarray มากที่สุด

วิธีที่ใช้: Prefix sums + เก็บค่าสถานะสำหรับแต่ละค่า
- คำนวณ prefix sum `p[j] = sum_{t=1..j} a[t]` (และ `p[0]=0`).
- สำหรับค่า `val` แต่ละค่า เก็บค่าน้อยที่สุดของ `p[i-1]` ที่เห็นก่อนตำแหน่งปัจจุบันเมื่อ `a[i] == val` (เรียกว่า `min_p_minus_1[val]`).
- เมื่อพบค่า `val` ที่ตำแหน่ง `j` ให้พิจารณาเป็นจุดสิ้นสุดของ subarray ที่มีค่าเริ่มต้นเท่ากับ `val` ดังนั้นผลรวม subarray (i..j) = `p[j] - p[i-1]` และการเก็บ `p[i-1]` ที่น้อยที่สุดให้ผลรวมสูงสุดสำหรับคู่ที่มี `val` เดียวกัน
- อัปเดต `max` ตามค่า `p[j] - min_p_minus_1[val]` และอัปเดต `min_p_minus_1[val]` ด้วย `p[j-1]` (prefix ก่อนตำแหน่งนี้) ถ้าจำเป็น

ข้อดี: เวลา O(n) (แต่ละตำแหน่งทำ O(1)), พื้นที่ O(Range_of_values) (ในโค้ดใช้ array ขนาดคงที่ 2005 เพื่อรองรับค่าในช่วง -1000..1000)

---

## 2. วิเคราะห์โค้ด

สำคัญ (สรุปโค้ด):
```cpp
vector<int> min_p_minus_1(2005, INF);
int current_prefix_sum = 0;
int max_double_end_sum = -INF;
for each a in input:
    idx = a + 1000;
    potential_p_minus_1 = current_prefix_sum; // prefix up to previous element
    if (potential_p_minus_1 < min_p_minus_1[idx]) min_p_minus_1[idx] = potential_p_minus_1;
    current_prefix_sum += a; // now prefix including current element
    current_sum = current_prefix_sum - min_p_minus_1[idx];
    max_double_end_sum = max(max_double_end_sum, current_sum);
```

คำอธิบายทีละบรรทัดสำคัญ:
- `min_p_minus_1` เก็บค่าน้อยสุดของ `p[i-1]` สำหรับแต่ละค่า `val` (index = val + 1000)
- ก่อนเพิ่ม `a` เข้า `current_prefix_sum` เราเก็บ `potential_p_minus_1 = current_prefix_sum` ซึ่งคือ `p[i-1]` สำหรับตำแหน่งปัจจุบัน `i`
- ถ้าค่านี้น้อยกว่าที่เก็บไว้ เราอัปเดต `min_p_minus_1[idx]`
- หลังเพิ่ม `a` (ได้ `p[j]`) เราคำนวณ `p[j] - min_p_minus_1[idx]` ซึ่งเป็นผลรวมสูงสุดของ subarray ที่จบที่ `j` และมีค่าเริ่มต้นเท่ากับ `a[j]`
- เก็บค่า `max_double_end_sum` เป็นคำตอบสุดท้าย

ข้อสังเกต:
- โค้ดอนุญาตให้ subarray ความยาว 1 (i=j) — ในกรณีนี้ `p[j] - p[j-1] = a[j]` จะถูกพิจารณา
- ช่วงค่าที่รองรับคือ [-1000,1000] (offset 1000) — ถาข้อมูลมีค่านอกช่วงนี้ ต้องขยาย array หรือใช้ map

---

## 3. ตัวอย่าง Test Case
Input:
```
7
1 2 -3 1 4 -3 4
```
Output:
```
5
```

อธิบายทีละขั้น (คำนวณ prefix sums และการอัปเดตสำหรับแต่ละตำแหน่ง):

ค่าลำดับ a[1..7]:  1, 2, -3, 1, 4, -3, 4
Prefix sums p[0..7]:
 p0 = 0
 p1 = 1
 p2 = 3
 p3 = 0
 p4 = 1
 p5 = 5
 p6 = 2
 p7 = 6

ตาราง trace (ตำแหน่ง i, a[i], p[i-1], update min, p[i], candidate sum = p[i] - min_p):

i=1: a=1, idx=1001
 - p[i-1]=p0=0 → min_p[1001] = min(INF,0) = 0
 - p1=1 → candidate = 1 - 0 = 1 → max = 1

i=2: a=2, idx=1002
 - p1=1 → min_p[1002]=1
 - p2=3 → candidate = 3 - 1 = 2 → max = 2

i=3: a=-3, idx=997
 - p2=3 → min_p[997]=3
 - p3=0 → candidate = 0 - 3 = -3 → max stays 2

i=4: a=1, idx=1001
 - p3=0 → min_p[1001]=min(0,0)=0
 - p4=1 → candidate = 1 - 0 = 1 → max stays 2

i=5: a=4, idx=1004
 - p4=1 → min_p[1004]=1
 - p5=5 → candidate = 5 - 1 = 4 → max becomes 4

i=6: a=-3, idx=997
 - p5=5 → min_p[997]=min(3,5)=3
 - p6=2 → candidate = 2 - 3 = -1 → max stays 4

i=7: a=4, idx=1004
 - p6=2 → min_p[1004]=min(1,2)=1
 - p7=6 → candidate = 6 - 1 = 5 → max becomes 5

ผลลัพธ์สุดท้าย = 5 — เกิดจาก subarray indices 5..7 = [4, -3, 4] หรืออาจถือเป็น 5..7 (เริ่มที่ตำแหน่งที่มีค่า 4 และสิ้นสุดที่ตำแหน่งที่มีค่า 4)

ASCII visualization (แนวคิด):

Indices:     1   2   3   4   5    6   7
Values a:   [1,  2, -3,  1,  4,  -3, 4]
Prefix p:    0   1   3   0   1   5   2   6

แสดงการจับคู่ "same endpoints":
- For value 4: first occurrence i=5 (p4=1), second occurrence j=7 (p7=6)
  → sum(5..7) = p7 - p4 = 6 - 1 = 5 ← best

---

## 4. Complexity (Big O / Big Theta)
- Time: แต่ละตำแหน่งทำงาน O(1) → Time = Θ(n)
- Space: ใช้ array `min_p_minus_1` ขนาดคงที่ (2005) → Space = Θ(1) ถานับเป็นค่าสมมุติ; ในทั่วไป O(R) เมื่อ R = range of values

ถ้าพิจารณาช่องว่างของค่าเป็นตัวแปร:
- Time = Θ(n)
- Space = Θ(R)

---