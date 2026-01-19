# Binary Search 2

## 1. วิเคราะห์โจทย์

**โจทย์ต้องการอะไร:**เรามี Array ที่เรียงลำดับจากน้อยไปมาก (Sorted Array) จำนวน $N$ ตัว และมีคำถาม (Query) จำนวน $M$ ข้อสำหรับแต่ละคำถาม $X_i$ เราต้องหา **ค่าที่มากที่สุดใน Array ที่มีค่าน้อยกว่าหรือเท่ากับ** $X_i$ (Largest element not exceeding $X_i$) หากไม่มีค่าใดเลยที่น้อยกว่าหรือเท่ากับ $X_i$ ให้ตอบ -1

**ข้อจำกัด:**
* $N, M \le 100,000$ (จำนวนเยอะมาก)
* Time Limit: 1 วินาที
* ห้ามใช้ Library สำเร็จรูป (เช่น `std::lower_bound` หรือ `std::upper_bound`)

**วิธีการแก้ปัญหา:** เนื่องจาก Array เรียงลำดับมาแล้ว และเราต้องค้นหาตำแหน่งที่เหมาะสม การใช้ **Linear Search** (วนลูปหาทีละตัว) จะใช้เวลา $O(N)$ ต่อ 1 คำถาม รวมทั้งหมดเป็น $O(M \times N)$ ซึ่งจะเกินเวลา ($10^{10}$ รอบ)

ดังนั้น เราต้องใช้ **Binary Search (การค้นหาแบบทวิภาค)** ซึ่งจะตัดขอบเขตการค้นหาลงครึ่งหนึ่งเสมอ ทำให้ใช้เวลาเพียง $O(\log N)$ ต่อ 1 คำถาม รวมทั้งหมดเป็น $O(M \log N)$ ซึ่งทันเวลาแน่นอน

---

## 2. แนวคิดหลัก
โค้ดนี้ใช้เทคนิค Binary Search เพื่อหา "คำตอบที่ดีที่สุด" (ตำแหน่งขวาสุดที่เป็นไปได้)

**ส่วนฟังก์ชัน** `find_num(int k):`
* **การตั้งค่าขอบเขต** (`low`, `high`):
  * `int low = -1;`: ให้เริ่มที่ -1 เพื่อรองรับกรณีที่ไม่มีคำตอบเลย (ค่า $k$ น้อยกว่าทุกตัวใน Array)
  * `int high = N - 1;`: ขอบเขตขวาสุดคือตัวสุดท้ายของ Array
```cpp
int find_num(int k) {
    int low = -1;
    int high = N - 1;
    //...
```
* **ลูปการค้นหา** (`while (low < high)`):
  * ลูปจะทำงานตราบใดที่ขอบเขตล่างยังไม่ชนกับขอบเขตบน
  * **การหาค่ากลาง:** `int middle = (low + high + 1) / 2;`
    * *จุดสังเกต:* มีการ `+1` ก่อนหาร 2 เพื่อปัดเศษขึ้น (Ceiling) การทำแบบนี้ป้องกัน "Infinite Loop" ในกรณีที่ `low` และ `high` อยู่ติดกัน (เช่น low=0, high=1 ถ้าไม่บวก 1 `middle` จะได้ 0 ซึ่งทำให้ `low` ไม่ขยับ)
```cpp
while (low < high) {
        int middle = (low + high + 1) / 2;
        //...
```
* **การตรวจสอบเงื่อนไข:**
  * `if (v[middle] <= k)`:
    * ถ้าค่าตรงกลาง **น้อยกว่าหรือเท่ากับ** $k$ แปลว่าตัวนี้ "**อาจจะเป็นคำตอบ**" หรือคำตอบอาจจะอยู่ทางขวาอีก (ค่าที่มากกว่านี้แต่ยัง $\le k$)
    * ดังนั้นเราขยับ `low = middle` (เก็บตำแหน่งนี้ไว้ ไม่ข้ามไป `middle + 1` เพราะตัวนี้อาจจะดีที่สุดแล้ว)
  * `else` (`v[middle] > k`):
    * ถ้าค่าตรงกลาง **มากกว่า** $k$ แปลว่าตัวนี้และทางขวาทั้งหมดใช้ไม่ได้
    * ดังนั้นเราตัดทิ้งโดยขยับ `high = middle - 1`
```cpp
if (v[middle] <= k) {
    low = middle;
}
else {
    high = middle - 1;
}
```
* **คืนค่า:**
  * เมื่อลูปจบ (`low == high`), ตัวแปร `high` (หรือ `low`) จะชี้ไปที่ Index ที่มากที่สุดที่มีค่า $\le k$ หรือเป็น -1 ถ้าไม่มี
```cpp
return high;
```

**ส่วน** `main`:
* รับค่า $N, M$ และรับ Array เข้ามาเก็บใน `vector<int> v`
* วนลูปรับค่า Query (`num2`) และเรียก `find_num`
* ถ้าได้ index -1 ให้พิมพ์ -1 ถ้าได้ index ปกติ ให้พิมพ์ค่าใน Array ณ index นั้น (`v[idx]`)
```cpp
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    v.resize(N);
    for(int i = 0 ; i < N ; i++) {
        cin >> num1;
        v[i] = num1;
    }
    while(M--) {
        cin >> num2;
        int idx = find_num(num2);
        if (idx == -1) cout << -1 << endl;
        else {cout << v[idx] << endl;} 
    }
}
```

## 3. ตัวอย่าง Test Case

### Input

```
4 7
14 15 20 30
10 11 14 15 16 21 68
```

**Array** `v`:
| Index | 0 | 1 | 2 | 3 |
| :--- | :-: | :-: | :-: | :-: | 
| Value | 14 | 15 | 20 | 30 |

**ตัวอย่างการรัน: ค้นหาเลข 16 (Query = 16)**
เป้าหมาย: หาเลขมากที่สุดที่ $\le 16$ (คำตอบควรเป็น 15 ที่ Index 1)

**ขั้นตอนการทำงาน (Step-by-Step):**

**Step 1:** เริ่มต้น
* `low = -1`, `high = 3`
* หา `middle` = $(-1 + 3 + 1) / 2 = 1.5 \rightarrow 1$ (ปัดเศษทิ้งใน integer)
* `v[1]` คือ **15**
* เช็คเงื่อนไข: $15 \le 16$ เป็น **จริง**
* อัปเดต: `low = 1` (คำตอบต้องอยู่ที่ Index 1 หรือมากกว่า)

```
Indices:  -1   0   1   2   3
Values:       14  15  20  30
Pointers:  L       M       H
                  (เก็บ 1 ไว้)
```

**Step 2:**
* `low = 1`, `high = 3`
* หา `middle` = $(1 + 3 + 1) / 2 = 2.5 \rightarrow 2$
* `v[2]` คือ **20**
* เช็คเงื่อนไข: $20 \le 16$ เป็น **เท็จ** (20 มากเกินไป)
* อัปเดต: `high = 2 - 1 = 1` (ตัดหางทิ้ง)

```
Indices:  -1   0   1   2   3
Values:       14  15  20  30
Pointers:          L   M   H
                   H
```

**Step 3:**
* `low = 1`, `high = 1`
* เงื่อนไข `while (low < high)` เป็นเท็จ (1 < 1 เป็นเท็จ) -> **จบลูป**
* Return `high` ซึ่งคือ **1**
**ผลลัพธ์:** ใน `main` ได้ค่า `idx = 1` พิมพ์ `v[1]` ออกมา คือ **15**

**ตรวจสอบคำตอบตาม Input ที่ให้มา**
* **Query 10:** น้อยกว่า 14 -> `high` จะลดลงเรื่อยๆ จนจบที่ -1 -> **Output: -1**
* **Query 11:** น้อยกว่า 14 -> **Output: -1**
* **Query 14:** เจอ 14 พอดี -> **Output: 14**
* **Query 15:** เจอ 15 พอดี -> **Output: 15**
* **Query 16:** (ตามตัวอย่างด้านบน) -> **Output: 15**
* **Query 21:** มากกว่า 20 แต่น้อยกว่า 30 -> **Output: 20**
* **Query 68:** มากกว่าทุกตัว low จะขยับไปจนสุดที่ 3 -> **Output: 30**

### Output

```
-1
-1
14
15
15
20
30
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `$$O(N + M \log N)$$`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>

using namespace std;

int N,M,num1,num2;
vector<int> v;

int find_num(int k) {
    int low = -1;
    int high = N - 1;
    while (low < high) {
        int middle = (low + high + 1) / 2;
        if (v[middle] <= k) {
            low = middle;
        }
        else {
            high = middle - 1;
        }
    }
    return high;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    v.resize(N);
    for(int i = 0 ; i < N ; i++) {
        cin >> num1;
        v[i] = num1;
    }
    while(M--) {
        cin >> num2;
        int idx = find_num(num2);
        if (idx == -1) cout << -1 << endl;
        else {cout << v[idx] << endl;} 
    }
}
```