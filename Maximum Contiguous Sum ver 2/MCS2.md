# Maximum Contiguous Sum ver 2

## 1. วิเคราะห์โจทย์
ปัญหา: หาผลรวมสูงสุดของ subarray ต่อเนื่องในอาร์เรย์แบบ "วงกลม" (circular array) — กล่าวคือ subarray อาจ wrap รอบจากปลายกลับมาที่จุดเริ่มต้น

วิธีที่ใช้:
- ใช้ Kadane เพื่อหาค่า `maxNormal`: ค่าสูงสุดของ subarray ปกติ (ไม่ wrap)
- ใช้แนวคิดคู่ขนาน (Kadane บนค่าสลับเครื่องหมาย) เพื่อหาค่า `minSub`: ค่าต่ำสุดของ subarray ต่อเนื่อง
- ถ้าไม่ใช่กรณีที่สมาชิกทั้งหมดเป็นลบ (`maxNormal >= 0`) ให้ค่าสูงสุดแบบ circular เป็น `max(maxNormal, totalSum - minSub)`
  - เพราะ `totalSum - minSub` คือการเลือก subarray ที่ wrap ครอบคลุมส่วนที่ไม่ใช่ minSub (complement)
- ถ้าทุกสมาชิกเป็นลบ `maxNormal` จะเป็นค่าสูงสุด (ค่าที่น้อยที่สุดเป็นลบที่ใหญ่ที่สุด)

สรุป: ใช้สองครั้ง Kadane (หนึ่งครั้งหาค่าสูงสุด อีกครั้งหาค่าต่ำสุด) และหาผลรวมทั้งหมด → เวลา Θ(N)

---

## 2. วิเคราะห์โค้ด

โค้ดทำงานดังนี้:
- อ่าน `N` และอาร์เรย์ `a[0..N-1]`
- กำหนดตัวแปรเริ่มต้นจาก `a[0]`:
  - `totalSum` = ผลรวมทั้งหมด
  - `maxEnding`, `maxNormal` = ตัวแปรสำหรับ Kadane (หาค่าสูงสุด)
  - `minEnding`, `minSub` = ตัวแปรสำหรับหาค่าต่ำสุด (Kadane แบบกลับเครื่องหมาย)

ลูปสำหรับ i = 1..N-1:
- อัปเดต `totalSum += a[i]`
- อัปเดต Kadane ปกติ:
  - `maxEnding = max(a[i], maxEnding + a[i])`
  - `maxNormal = max(maxNormal, maxEnding)`
- อัปเดต Kadane สำหรับค่าต่ำสุด:
  - `minEnding = min(a[i], minEnding + a[i])`
  - `minSub = min(minSub, minEnding)`

หลังลูป:
- ถ้า `maxNormal < 0` (ทุกค่าเป็นลบ) → พิมพ์ `maxNormal`
- มิฉะนั้น → พิมพ์ `max(maxNormal, totalSum - minSub)` (ค่าที่เหมาะสมระหว่าง non-wrap และ wrap)

เหตุผลเชิงตรรกะ:
- `maxNormal` ครอบคลุมกรณีปกติ
- `totalSum - minSub` คือการเลือก subarray ที่ wrap — เอาทุกเซลล์นอกเหนือจากช่วงที่ให้ผลรวมต่ำสุด (minSub)
- ตรวจสอบกรณีทุกลบ เพราะถ้า minSub == totalSum (เมื่อ subarray ทั้งหมดเป็น min), `totalSum - minSub == 0` ซึ่งจะให้ผลไม่ถูกต้องสำหรับกรณีทั้งหมดเป็นลบ ดังนั้น return `maxNormal` แทน

---

## 3. ตัวอย่าง Test Case
Input:
```
15
1 2 -1 5 3 -8 -2 4 3 -4 -5 7 -1 -2 4
```
Output ที่คาด: `18`

คำนวณเชิงตัวเลข:
- totalSum = 6
- maxNormal (non-wrap max) = 10 (ตัวอย่าง subarray indices 0..4 → 1+2-1+5+3)
- minSub (minimum contiguous subarray) = -12 (subarray indices 5..10 → -8 -2 4 3 -4 -5)
- totalSum - minSub = 6 - (-12) = 18
- ผลลัพธ์ = max(10, 18) = 18

อธิบายว่าทำไม minSub เป็น -12:
- minSub เกิดจาก subarray [-8, -2, 4, 3, -4, -5] ที่ตำแหน่ง 6..11 (1-based) ผลรวม = -12
- การเลือก complement ของช่วงนี้ (wrap-around) คือ subarray indices 11..14 (7,-1,-2,4) และ 0..4 (1,2,-1,5,3) รวมเป็น 18

ASCII trace (กระบวนการ Kadane ทั้งสองและ complement):

Indices:    0  1  2  3  4   5   6  7  8   9   10 11  12  13  14
Values a:   [1, 2, -1, 5, 3, -8, -2, 4, 3, -4, -5, 7, -1, -2, 4]

Non-wrap best subarray (maxNormal):
- Best found at indices 0..4 → [1,2,-1,5,3] sum = 10

Min subarray (minSub):
- Found at indices 5..10 → [-8,-2,4,3,-4,-5] sum = -12

Wrap-around candidate = complement = indices 11..14 + 0..4 → [7,-1,-2,4,1,2,-1,5,3] sum = 18

Visual (wrap):

End segment:   [ 7  -1  -2   4 ]    (indices 11..14, sum=8)
Start segment: [ 1   2  -1   5   3 ] (indices 0..4, sum=10)
Combined (wrap) → sum = 8 + 10 = 18 (length 9)

ข้อสังเกต: wrap candidate เป็น subarray ที่ต่อเนื่องเมื่อนำอาร์เรย์มาวางเป็นวงกลม

---

## 4. Complexity (Big O / Big Theta)
- Time: แต่ละสมาชิกถูกประมวลผลครั้งเดียว (อัปเดตค่าคงที่หลายตัว) → Θ(N)
- Space: ใช้ O(1) extra space (นับตัวแปรคงที่); input array ใช้ Θ(N)

สรุป:
- Time = Θ(N)
- Space = Θ(1) extra (หรือ Θ(N) ถีนับพื้นที่สำหรับเก็บ input)

---
