# Hadamard Transform (FWHT)

## 1. วิเคราะห์โจทย์
โจทย์นี้ทำการแปลงเวกเตอร์ขนาดกำลังสองของสอง (n = 2^k) ด้วยการใช้ Fast Walsh–Hadamard Transform (FWHT)
- แนวคิดหลัก: แบ่งเวกเตอร์เป็นสองครึ่งแล้วคำนวณผลรวมและผลต่างของคู่องค์ประกอบคู่กัน (sum/difference), ทำแบบนี้แบบ recursive จนเหลือขนาด 1
- ผลลัพธ์เป็นการแปลงแบบ Hadamard (ไม่ normalized) เหมาะสำหรับการคำนวณ convolution บางประเภท (เช่น XOR convolution)

## 2. วิเคราะห์โค้ด
ฟังก์ชันหลัก:

```cpp
void fwht(vector<int>& arr, int start , int len) {
    if(len == 1) return;

    int half = len / 2;

    for(int i = 0; i < half; i++) {
        int u = arr[start + i];
        int v = arr[start + half + i];

        arr[start + i] = u + v;
        arr[start + half + i] = u - v; 
    }
    fwht(arr, start, half);
    fwht(arr, start + half, half);
}
```
- Base case: เมื่อ `len==1` หยุด
- ขั้นผสม (butterfly): สำหรับแต่ละคู่ตำแหน่ง `(start+i)` และ `(start+half+i)` คำนวณ `u+v` และ `u-v` แทนค่ากลับลงไป
- เรียก recursive ซ้ายและขวา (divide & conquer)

ใน `main()` อ่าน `n` และเวกเตอร์ `v[0..n-1]` แล้วเรียก `fwht(v,0,n)` และพิมพ์ผล

หมายเหตุ: นี่เป็นเวอร์ชัน in-place ของ FWHT และเป็นการแปลงแบบ forward (inverse จะต้องทำการกลับขั้นตอนและหารด้วย `2` ที่แต่ละระดับ หรือหารด้วย `n` ท้ายสุด)

## 3. ตัวอย่าง Test Case และขั้นตอน (ASCII)
Input:
```
4
1 2 4 8
```
Output ที่คาด: `15 -5 -9 3`

การคำนวณทีละขั้น:
- เริ่มต้น: v = [1, 2, 4, 8]

ระดับบนสุด (len=4, half=2): ทำ pair-wise
- คู่ (0,2): u=1, v=4 → new0 = 1+4 = 5 ; new2 = 1-4 = -3
- คู่ (1,3): u=2, v=8 → new1 = 2+8 = 10; new3 = 2-8 = -6
→ หลังขั้นผสมระดับ 1: v = [5, 10, -3, -6]

เรียก fwht บนซีกซ้าย (start=0, len=2):
- half=1: pair (0,1): u=5,v=10 → v[0]=15, v[1]= -5
→ ซีกซ้ายเป็น [15, -5]

เรียก fwht บนซีกขวา (start=2, len=2):
- pair (2,3): u=-3,v=-6 → v[2]= -9, v[3]= 3
→ ซีกขวาเป็น [-9, 3]

ผลสุดท้าย: v = [15, -5, -9, 3]

ASCII trace (แสดงมุมมอง tree ของการแบ่ง):

Initial:      [ 1 ,  2 ,  4 ,  8 ]
After mix L1:  [ 5 , 10 , -3 , -6 ]
After L2 left: [15, -5, -3, -6]
After L2 right: [15, -5, -9,  3]

(สรุป: ขั้นแรกจับคู่และคำนวณ u+v, u-v แล้วชวนเรียกซ้ำบนครึ่งซ้ายและครึ่งขวา)

### ความหมายเชิงปฏิบัติ
- ค่า `15` คือผลรวมทั้งหมดของบางลักษณะคอมบิเนชันของบิต (ขึ้นกับการตีความ Hadamard)
- ค่าที่ได้ใช้ในแอปพลิเคชันเช่นการคำนวณ XOR convolution โดยการแปลงทั้งสองเวกเตอร์ด้วย FWHT คูณค่าตามตำแหน่ง แล้วทำ inverse FWHT

## 4. Complexity — Big O / Big Theta
- เวลา: แต่ละระดับของ recursion ทำงาน O(n) (เพราะมี `len/2` ขั้นผสม) และมี `log n` ระดับ →

  Time = Θ(n log n)

- พื้นที่: in-place transform ใช้ O(1) extra space (นับนอก array) แต่ใช้ recursion stack depth = O(log n)

  Space = Θ(1) extra (stack O(log n))

---