# Maximum Contiguous Sum with Width Constraint

## 1. วิเคราะห์โจทย์
โจทย์: ให้ลำดับจำนวนเต็มยาว `n` และค่าจำกัดความยาว `w` หา subarray ต่อเนื่องที่มีผลรวมมากที่สุด โดยความยาวของ subarray ต้องไม่เกิน `w` (i.e., length ≤ w)

วิธีที่ใช้: Prefix sums + Monotonic deque (sliding-window minimum on prefix sums)
- คำนวณ prefix sum `p[i] = sum_{t=1..i} a[t]` (และกำหนด `p[0]=0`).
- สำหรับตำแหน่งขวา `j` ของ subarray ผลรวม subarray (i+1..j) = `p[j] - p[i]` โดยต้องการ `j - i ≤ w` (หรือ `i ≥ j - w`).
- ถ้าต้องการ `p[j] - p[i]` มากสุด เราต้องลบ `p[i]` ให้เป็นค่าน้อยที่สุดภายในช่วงดัชนีที่อนุญาต (`i ∈ [j-w, j-1]`).
- เก็บตัวชี้ `i` ที่เป็นไปได้ใน deque ที่รักษา `p[i]` ในลำดับเพิ่มขึ้น (monotonic increasing). ด้านหน้าของ deque เป็นค่าที่เล็กที่สุดภายในหน้าต่าง = ตัวเลือกที่ดีที่สุดสำหรับ j ปัจจุบัน.

ข้อดี: ทำได้ในเวลา O(n) และใช้พื้นที่เสริมเล็กน้อย (deque + prefix array)

---

## 2. วิเคราะห์โค้ด

โค้ดหลักทำตามแนวทางข้างต้น:
1. อ่าน `n, w` แล้วอ่านค่าทีละตัว สร้าง `p[0..n]` เป็น prefix sums (p[0]=0)
2. เตรียม `deque<int> dq` เก็บดัชนี `i` ของ prefix sums (เริ่มด้วย 0)
3. สำหรับ `j` = 1..n ทำ:
   - ลบ front ของ deque ถ้ามันอยู่นอกหน้าต่าง: `dq.front() < j - w` → `dq.pop_front()`
   - ถ้า deque ไม่ว่าง ให้อัปเดต `max_sum = max(max_sum, p[j] - p[dq.front()])`
   - แล้วลบจากท้ายของ deque indices ที่มี `p[dq.back()] >= p[j]` เพื่อรักษา monotonic increasing ของพยัญชนะค่า prefix
   - เพิ่ม `j` เข้า deque
4. สุดท้ายพิมพ์ `max_sum`

เหตุผลความถูกต้อง:
- deque.front() ให้ `i` ที่มี `p[i]` ต่ำสุดในช่วงที่ถูกต้อง → ทำให้ `p[j] - p[i]` สูงสุดสำหรับ j นั้น
- การลบค่าจากท้ายเมื่อ `p[dq.back()] >= p[j]` ป้องกันไม่ให้มีค่า prefix ที่ใหญ่กว่ามีโอกาสเลือกในอนาคต (เพราะ j ปัจจุบัน มีค่า p[j] ที่ดีกว่าและ index ใหม่อยู่หลัง จึงครอบงำ)

---

## 3. ตัวอย่าง Test Case (ตามที่ให้)
Input:
```
10 4
1 4 2 -3 5 -7 3 9 2 -7
```
Output:
```
14
```

อธิบายการคำนวณ (prefix sums และการอัปเดต deque):

ค่าต้นฉบับ a[1..10]:
1, 4, 2, -3, 5, -7, 3, 9, 2, -7

Prefix sums p[i] (i=0..10):
p[0]=0
p[1]=1
p[2]=5
p[3]=7
p[4]=4
p[5]=9
p[6]=2
p[7]=5
p[8]=14
p[9]=16
p[10]=9

ตาราง trace ของลูป (j จาก 1 ถึง 10):

j | p[j] | dq (indices, front→back) | p[dq.front()] | candidate p[j]-p[dq.front()] | max_sum after
--|------|--------------------------|---------------|---------------------------------|----------------
1 | 1    | [0] → push 1 → [0,1]     | 0             | 1 - 0 = 1                       | 1
2 | 5    | [0,1] → candidate 5-0=5  | 0             | 5                               | 5
   then pop back while p[back]≥p[2]: p[1]=1 <5 so none; push 2 → [0,1,2]
3 | 7    | front 0 → 7-0=7          | 0             | 7                               | 7
   push 3 → [0,1,2,3]
4 | 4    | dq.front()=0, j-w=0 → in window
   candidate 4-0=4 (max stays 7)
   pop back while p[back]≥4: p[3]=7≥4 pop, p[2]=5≥4 pop, p[1]=1<4 stop → dq [0,1]
   push 4 → [0,1,4]
5 | 9    | j-w=1, dq.front()=0 <1 → pop front → dq=[1,4]
   candidate 9-p[1]=9-1=8 → max becomes 8? (was 7) → now 8
   pop back while p[back]≥9: p[4]=4<9 → push 5 → [1,4,5]
6 | 2    | j-w=2, dq.front()=1 <2 → pop front → dq=[4,5]
   candidate 2 - p[4]=2-4=-2 → max stays 8
   pop back while p[back]≥2: p[5]=9≥2 pop, p[4]=4≥2 pop → dq empty → push 6 → [6]
7 | 5    | j-w=3, dq.front()=6 ≥3 OK
   candidate 5-p[6]=5-2=3 → max stays 8
   pop back while p[6]=2 ≥5? no → push 7 → [6,7]
8 | 14   | j-w=4, dq.front()=6 ≥4 OK
   candidate 14-p[6]=14-2=12 → max becomes 12
   pop back while p[back]≥14: p[7]=5<14 → push 8 → [6,7,8]
9 | 16   | j-w=5, dq.front()=6 ≥5 OK
   candidate 16-p[6]=14 → max becomes 14
   pop back while p[back]≥16: none → push 9 → [6,7,8,9]
10| 9    | j-w=6, dq.front()=6 <6? dq.front()==6 < (j-w)==6 is false (6 < 6 false) so in window
   candidate 9-p[6]=7 → max remains 14
   pop back while p[back]≥9: p[9]=16≥9 pop, p[8]=14≥9 pop, p[7]=5<9 stop → dq [6,7]
   push 10 → [6,7,10]

สุดท้าย max_sum = 14 → ตรงกับ output

สรุป subarray ที่ให้ผลลัพธ์ 14: เมื่อ j=9 และ i=6 → subarray (i+1..j) = (7..9) = [3,9,2] ผลรวม = 3+9+2 = 14 (ความยาว = 3 ≤ w=4)

ASCII visualization (สไลด์หน้าต่างความยาว ≤ 4):

ตำแหน่ง indices:  1  2  3  4  5   6  7  8  9   10
values a:           [1, 4, 2, -3, 5, -7, 3, 9, 2, -7]
possible windows (length ≤ 4) — highlight best window [7..9]:

...  (6)  (7)  (8)  (9)
     -7   3    9    2   → sum = 7+? compute = 14 (best)

หรือแสดงว่าเมื่อพิจารณาหน้าต่างที่เวกเตอร์ prefix ต่ำสุดในหน้าต่างคือที่ index 6 (p[6]=2) และพิจารณาจุด j=9 (p[9]=16) ได้ผลลัพธ์ p[9]-p[6]=14

---

## 4. Complexity (Big O / Big Theta)

- Time: แต่ละ index `j` ถูกประมวล O(1) amortized ทั้งการ pop front/pop back push → ผลลัพธ์เป็น Θ(n)
- Space:
  - Prefix array `p` ใช้ Θ(n)
  - Deque ใช้สูงสุด O(w) indices แต่ในโค้ดเก็บพวก indices ที่เป็นไปได้ทั้งหมดระหว่างกระบวนการ → O(n) worst-case

สรุป:
- Time = Θ(n)
- Space = Θ(n) (dominant by prefix array); extra working space Θ(min(n,w)) for deque

---
