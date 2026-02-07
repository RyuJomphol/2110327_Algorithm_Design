# Lawn Mowing

## 1. วิเคราะห์โจทย์
โจทย์: ให้ความยาวสนามหญ้า `n` จำนวนหญ้าต่อแผ่น (positive integers) และพารามิเตอร์ `k` ค่าใช้จ่ายต่อแผ่นที่ต้องจ้างเพิ่ม (เช่น ค่าจ้างแรงงานต่อแผ่น) มี `m` คำถามแต่ละคำถามระบุจุดเริ่ม `l` และงบ `budget` ต้องการหาค่าสูงสุดของผลรวมหญ้าที่สามารถตัดเริ่มที่ `l` ต่อเนื่องไปทางขวา โดยข้อจำกัดคือ

total_cost = sum_of_grass + length * k ≤ budget

ต้องคืนผลรวมหญ้าสูงสุด (ไม่รวมค่าจ้าง) ที่ทำได้ภายใต้งบ

วิธีที่ใช้: Prefix sums + Binary search
- คำนวณ prefix sums `p[i]` เพื่อคำนวณผลรวมของช่วงแบบ O(1)
- สำหรับแต่ละคำถาม fix ตำแหน่ง `l` แล้ว binary-search หา `r` สูงสุดที่เงื่อนไข `p[r+1]-p[l] + (r-l+1)*k ≤ budget` เป็นจริง
- เวลาต่อคำถาม O(log n)

---

## 2. วิเคราะห์โค้ด

โครงสร้างหลัก:
- อ่าน `n, m, k`
- สร้าง `p[0..n]` เป็น prefix sums (p[0]=0, p[i] = sum of first i values)

สำหรับแต่ละคำถาม (l, budget):
- กำหนด search range `low = l`, `high = n-1` (index array เป็น 0-based ในโค้ด)
- หา `best_r = -1` เป็นค่าผลลัพธ์ชั่วคราว
- ใน loop binary search คำนวณ `mid` แล้วคำนวณ
  - `grass_sum = p[mid+1] - p[l]` (sum a[l..mid])
  - `total_cost = grass_sum + (mid - l + 1) * k`
- ถ้า `total_cost ≤ budget` → เก็บ `best_r = mid` และขยับ `low = mid + 1` (พยายามหาช่วงยาวขึ้น)
- มิฉะนั้น ขยับ `high = mid - 1`
- หลัง loop ถ้า `best_r == -1` พิมพ์ `0` (ไม่สามารถตัดแม้แต่จุดเดียว) มิฉะนั้นพิมพ์ `p[best_r+1] - p[l]` (ผลรวมหญ้าที่ได้)

เหตุผลการเลือก binary search: สำหรับ fixed `l` เงื่อนไข `total_cost ≤ budget` เป็นสมบัติ monotonic ใน `r` — ถ้าเป็นจริงสำหรับ `r` ใด ก็จะเป็นจริงสำหรับทุก `r'` ≤ `r` ดังนั้นสามารถหา `r` สูงสุดด้วย binary search

---

## 3. ตัวอย่าง Test Case (ตามที่ให้)
Input (format):
```
5 5 0
1 2 3 4 5
1 5
1 8
1 9
1 10
1 14
```
- `n=5, m=5, k=0` (ไม่มีค่าใช้จ่ายต่อแผ่น)
- ราคาต่อแผ่น `k=0` ดังนั้นเงื่อนไขเพียง `sum_of_grass ≤ budget`
- ค่า a = [1,2,3,4,5] (0-based indices 0..4)

คำถามทีละบรรทัด (l, budget) — โค้ดใช้ `l` เป็น index 0-based ดังนั้นถ้าคำถามให้ `l` เป็น 1-based ต้องระวัง (ในตัวอย่างโค้ดดูเหมือนรับ `l` 0-based). ที่นี่ตัวอย่างสอดคล้องกับโค้ด (สมมุติ l เป็น 0-based); ถ้าจริงเป็น 1-based ควรลบ 1 ก่อนใช้

เราจะตีความตามโค้ด: `l` เป็น 0-based. ดังนั้นคำถามเป็น:
1) l=1, budget=5 → start at index 1 value=2
2) l=1, budget=8
3) l=1, budget=9
4) l=1, budget=10
5) l=1, budget=14

คำนวณ prefix sums p:
```
p[0]=0
p[1]=1
p[2]=3
p[3]=6
p[4]=10
p[5]=15
```

คำถาม 1: l=1, budget=5
- possible r and grass_sum: r=1→2, r=2→2+3=5, r=3→2+3+4=9 >5 → so best_r=2 result=5
Output: 5

คำถาม 2: l=1, budget=8
- r=2 sum=5 ≤8, r=3 sum=9>8 → best_r=2 result=5
Output: 5

คำถาม 3: l=1, budget=9
- r=3 sum=9 ≤9 → best_r=3 result=9
Output: 9

คำถาม 4: l=1, budget=10
- r=3 sum=9 ≤10, r=4 sum=14>10 → best_r=3 result=9
Output: 9

คำถาม 5: l=1, budget=14
- r=4 sum=14 ≤14 → best_r=4 result=14
Output: 14

ผลลัพธ์ทั้งหมด (ตามลำดับ):
```
5
5
9
9
14
```

(ตรงกับตัวอย่าง)

ASCII visualization (prefix sums + binary search idea):

Array indices: 0  1  2  3  4
Values:        1  2  3  4  5
Prefix p:      0  1  3  6 10 15

Start l=1 (value 2). For each r≥1 compute sum = p[r+1]-p[1]. As r increases sums: 2,5,9,14 → stop when >budget and pick previous.

Binary search picture (for budget=9):
- low=1, high=4 → mid=2 → sum=5 ≤9 → best_r=2, low=3
- low=3, high=4 → mid=3 → sum=9 ≤9 → best_r=3, low=4
- low=4, high=4 → mid=4 → sum=14 >9 → high=3 → loop end → best_r=3

---

## 4. Complexity (Big O / Big Theta)
- Preprocessing prefix sums: Θ(n)
- สำหรับแต่ละคำถาม: binary search O(log n) และคำนวณ sum O(1)
- ดังนั้นรวมเวลา = Θ(n + m log n)
- Space: Θ(n) สำหรับ prefix array

สรุป:
- Time = Θ(n + m log n)
- Space = Θ(n)

---