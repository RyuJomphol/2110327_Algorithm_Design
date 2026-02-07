# Maximum Contiguous Sum

**1. วิเคราะห์โจทย์**
- ปัญหา: หาค่าสูงสุดของผลบวกของ subarray ต่อเนื่อง (Maximum Subarray Problem)
- วิธีที่ใช้: Kadane's Algorithm (Dynamic Programming แบบ Greedy)
  - สแกนอาร์เรย์จากซ้ายไปขวา
  - เก็บค่าสะสม (`current_sum`) ที่เป็นผลบวกสูงสุดของ subarray ที่ลงท้ายที่ตำแหน่งปัจจุบัน
  - ปรับ `current_sum = max(a[i], current_sum + a[i])` และอัปเดต `max_sum = max(max_sum, current_sum)`

**2. วิเคราะห์โค้ด**
- อ่านค่า `N` จำนวนสมาชิก
- วนลูปอ่านทีละตัว `a`
- กรณี `i == 0`: กำหนด `current_sum = a` และ `max_sum = a` (base initialization)
- สำหรับตัวถัดไป: คำนวณ
  - `current_sum = max(a, current_sum + a)` — เลือกระหว่างเริ่ม subarray ใหม่ที่ตำแหน่งนี้หรือต่อจาก subarray ก่อนหน้า
  - `max_sum = max(max_sum, current_sum)` — เก็บค่าสูงสุดที่พบ
- พิมพ์ `max_sum`

ข้อสังเกตจากโค้ด:
- ถูกต้องและกระชับ ใช้ O(1) extra space
- รองรับกรณีที่สมาชิกทั้งหมดเป็นลบได้ (เพราะเริ่ม `current_sum` จากค่าตัวแรก)

**3. ตัวอย่าง Test Case (ที่คุณให้)**
Input (N=15):
```
15
1 2 -1 5 3 -8 -2 4 3 -4 -5 7 -1 -2 4
```
Output:
```
10
```

**อธิบาย Step โดยตาราง ASCII (tracking `current_sum` และ `max_sum`)**

Array indices:      1  2  3  4  5   6   7  8  9  10  11 12  13  14 15
Values:             1  2 -1  5  3  -8  -2  4  3  -4  -5  7  -1  -2  4

Step-by-step:

- เริ่มที่ i=1: current_sum=1, max_sum=1
- i=2: current_sum=max(2,1+2)=3, max_sum=3
- i=3: current_sum=max(-1,3-1)=2, max_sum=3
- i=4: current_sum=max(5,2+5)=7, max_sum=7
- i=5: current_sum=max(3,7+3)=10, max_sum=10
- i=6: current_sum=max(-8,10-8)=2, max_sum=10
- i=7: current_sum=max(-2,2-2)=0, max_sum=10
- i=8: current_sum=max(4,0+4)=4, max_sum=10
- i=9: current_sum=max(3,4+3)=7, max_sum=10
- i=10: current_sum=max(-4,7-4)=3, max_sum=10
- i=11: current_sum=max(-5,3-5)=-2, max_sum=10
- i=12: current_sum=max(7,-2+7)=7, max_sum=10
- i=13: current_sum=max(-1,7-1)=6, max_sum=10
- i=14: current_sum=max(-2,6-2)=4, max_sum=10
- i=15: current_sum=max(4,4+4)=8, max_sum=10

สรุป: `max_sum` ที่ได้ = 10 (ตัวอย่าง subarray ที่ให้ผลรวม 10 คือ indices 1..5: 1+2-1+5+3 = 10)

ASCII visualization (consecutive scanning):

[Start] current_sum = 0 (conceptual)

Scan values and choose keep-or-reset:

 i:   1   2   3   4   5    6    7   8   9   10  11  12 13 14 15
 a:   1   2  -1   5   3   -8   -2   4   3   -4  -5   7 -1 -2  4
 cur: 1   3   2   7  10    2    0   4   7    3  -2   7  6  4   8
 max: 1   3   3   7  10   10   10  10  10   10  10  10 10 10  10

แสดงว่าเมื่อถึงตำแหน่งที่ 5 ได้ค่าสูงสุด 10 และไม่มี subarray ใดที่รวมได้มากกว่า 10

**4. Complexity (Big O / Big Theta)**
- Time: O(N) per test (แต่ละสมาชิกประมวลผลครั้งเดียว) — Theta(N)
- Space: O(1) extra space (นับเฉพาะตัวแปรเล็กๆ `current_sum`, `max_sum`) — Theta(1)

---