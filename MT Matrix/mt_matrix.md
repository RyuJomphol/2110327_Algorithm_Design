# MT Matrix — เฉลยเชิงวิธีการ

## 1. วิเคราะห์โจทย์ — วิธีที่ใช้
โจทย์สร้างเมทริกซ์ขนาด 2^n × 2^n โดยนิยามจากเมทริกซ์ฐานขนาด 2×2 ที่ให้ค่า `U, V, W, P` ดังนี้:

Base (n=1):
[ U  V ]
[ W  P ]

กระดานสำหรับระดับต่อไปถูกสร้างแบบแบ่งเป็น 4 บล็อก (quadrants) ขนาด 2^{n-1} × 2^{n-1}:
- Top-left = M_{n-1}
- Top-right = transpose(M_{n-1})
- Bottom-left = -M_{n-1}
- Bottom-right = -transpose(M_{n-1})

ดังนั้นวิธีแก้คือการใช้วิธี Divide-and-Conquer (recursion) โดยติดตามควอแดรนต์ที่ตำแหน่ง `(r,c)` อยู่ แล้วแปลงพิกัดและสัญญาณตามกฎข้างต้น จนลงไปถึงฐาน (n=1)

---
## 2. วิเคราะห์โค้ด (`mt_matrix.cpp`)
ฟังก์ชันสำคัญ: `solve(long long n, long long r, long long c)`
- ถ้า `n == 1` — คืนค่าตามตำแหน่งในเมทริกซ์ฐาน:
  - (1,1) -> `U`
  - (1,2) -> `V`
  - (2,1) -> `W`
  - (2,2) -> `P`
- คำนวณ `half = 1LL << (n - 1)` ซึ่งเป็นขนาดของแต่ละควอแดรนต์
- ตรวจสอบควอแดรนต์ของ `(r,c)`:
  - ถ้า `r <= half && c <= half` → อยู่ Top-left → คืน `solve(n-1, r, c)`
  - ถ้า `r <= half && c > half` → อยู่ Top-right → คืน `solve(n-1, c-half, r)` (สลับแถวคอลัมน์ = transpose)
  - ถ้า `r > half && c <= half` → อยู่ Bottom-left → คืน `-solve(n-1, r-half, c)` (ย้ายพิกัดและใส่ลบ)
  - ถ้า `r > half && c > half` → อยู่ Bottom-right → คืน `-solve(n-1, c-half, r-half)` (transpose + ลบ)

หมายเหตุ: การสลับพิกัดในกรณีขวา (ใช้ `c-half, r` หรือ `c-half, r-half`) คือการนำ transpose ของเมทริกซ์ย่อย

---
## 3. ตัวอย่าง Test Case (ตามที่ให้)
Input (อธิบายรูปแบบ):
```
3 4        # n = 3 (ขนาดเมทริกซ์ = 2^3 = 8), m = 4 (จำนวนคำถาม)
1 2 3 4    # U=1, V=2, W=3, P=4  (เมทริกซ์ฐาน)
1 1        # คำถามที่ 1: (r=1,c=1)
2 4        # คำถามที่ 2: (r=2,c=4)
4 3        # คำถามที่ 3: (r=4,c=3)
4 4        # คำถามที่ 4: (r=4,c=4)
```

Expected Output (แต่ละบรรทัดหนึ่งคำตอบ):
```
1
4
-2
-4
```

อธิบายการคำนวณทีละคำถาม (แสดงเส้นทาง recursion และการแปลงพิกัด):

1) Query (1,1)
- n=3, half=4 → r<=4,c<=4 → Top-left → solve(2,1,1)
- n=2, half=2 → r<=2,c<=2 → Top-left → solve(1,1,1)
- n=1 → (1,1) => U = 1 → result = 1

2) Query (2,4)
- n=3, half=4 → r<=4,c<=4 → Top-left → solve(2,2,4)
- n=2, half=2 → r<=2, c>2 → Top-right → solve(1, c-half, r) = solve(1, 4-2=2, 2)
- n=1 → (2,2) => P = 4 → result = 4

3) Query (4,3)
- n=3, half=4 → Top-left → solve(2,4,3)
- n=2, half=2 → r>2,c>2 → Bottom-right → return -solve(1, c-half, r-half) = -solve(1, 3-2=1, 4-2=2)
- n=1 → (1,2) => V = 2 → result = -2

4) Query (4,4)
- n=3 → Top-left → solve(2,4,4)
- n=2 → Bottom-right → -solve(1, 4-2=2,4-2=2)
- n=1 → (2,2) => P = 4 → result = -4

ASCII Visualization (กฎการประกอบเมทริกซ์ จากน้อยไปมาก):

Base (n=1) 2x2:

  [ U   V ]
  [ W   P ]

n=2 (ขนาด 4x4) ประกอบเป็น 4 บล็อก (M = base):

  [  M        transpose(M)  ]
  [ -M       -transpose(M)  ]

แทนค่า M ด้วยตัวเลขแทนตำแหน่ง (เพื่อเห็นรูปแบบ):
ถ้า M = [[a b] [c d]] แล้ว 4x4 จะเป็น:

  [ a  b | a  c ]
  [ c  d | b  d ]
  ------+------
  [-a -b |-a -c]
  [-c -d |-b -d]

(บรรทัดขวาของบล็อกบนเป็น transpose ของ M; บล็อกล่างเป็นค่าลบ)

การขยายไปยัง n=3 ทำซ้ำกฎเดียวกันกับ M = เมทริกซ์ขนาด 4x4 ที่ได้

---
## 4. Complexity (Big O / Big Theta)

- เวลา (Time) ต่อคำถาม: ฟังก์ชัน `solve` ลด `n` ลงทีละ 1 ในแต่ละครั้งจนถึงฐาน — ดังนั้นเวลาต่อคำถามเป็น O(n)
  - ถ้าเรียกให้เทียบกับขนาดเมทริกซ์ `N = 2^n` จะได้ `n = log2 N` ดังนั้นเวลา = O(log N)
- พื้นที่ (Space): ความลึกของ recursion = O(n) (stack) → O(log N)
- ถ้ามี `m` คำถามทั้งหมด เวลา = O(m * n) = O(m * log N)

---

## สรุปสั้น ๆ
- แนวคิดหลัก: สร้างเมทริกซ์แบบ recursive — top-right = transpose, bottom blocks = negative
- การหาค่าเฉพาะตำแหน่ง `(r,c)` ทำได้โดยการติดตามควอแดรนต์และแปลงพิกัดจนถึงเมทริกซ์ฐาน
- เวลา: O(n) ต่อคำถาม (หรือ O(log N) เมื่อ N = 2^n)

ไฟล์นี้บันทึกใน: `MT Matrix/mt_matrix.md`
