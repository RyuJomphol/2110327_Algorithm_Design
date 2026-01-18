# Huge Array

## 1. วิเคราะห์โจทย์

**ปัญหา:** โจทย์ต้องการหาค่าของตัวเลขในตำแหน่งที่ P หลังจากนำชุดตัวเลขทั้งหมดมาเรียงต่อกันและ **เรียงลำดับจากน้อยไปมากข้อจำกัด:** ขนาดของ Array ผลลัพธ์ (S) อาจใหญ่ถึง 2,000,000,000 (2 พันล้าน) ซึ่งใหญ่เกินกว่าจะสร้าง Array จริง ๆ ในหน่วยความจำ (RAM) ได้

**แนวทางแก้ไข:** 
* **Sorting Pairs:** แทนที่จะสร้าง Array ใหญ่ๆ เราเก็บข้อมูลเป็นคู่ `(ค่าตัวเลข X, จำนวน C)` แล้วนำคู่เหล่านี้มาเรียงลำดับตามค่า X จากน้อยไปมาก
* **Prefix Sum (ผลรวมสะสม):** เมื่อเรียงแล้ว เราจะรู้ว่าตัวเลขชุดแรกกินพื้นที่ index ตั้งแต่ 1 ถึง $C_1$, ชุดที่สองกินพื้นที่ต่อจากนั้น แนวคิดนี้ทำให้เราสร้าง "ช่วงของ Index" สำหรับตัวเลขแต่ละค่าได้
* **Binary Search:** เมื่อโจทย์ถามหาตำแหน่งที่ P เราไม่ต้องไล่หาทีละตัว แต่ใช้การค้นหาแบบ Binary Search (ใน C++ คือ `lower_bound`) บน Array ของผลรวมสะสม เพื่อหาว่า P ตกอยู่ในช่วงของตัวเลขชุดไหน

---

## 2. แนวคิดหลัก
มาดูการทำงานของโค้ดทีละส่วน

**ส่วนประกาศตัวแปร (Global Variables):** 
 ```cpp
cin >> N >> Q;
vector<pair<long long, long long>> sort_array(N);
for (int i = 0; i < N; ++i) {
    cin >> sort_array[i].first >> sort_array[i].second;
}
```
* สร้าง `vector<pair<long long, long long>> sort_array` เพื่อเก็บคู่ของ `(X, C)`
* ใช้ `long long` เพื่อรองรับค่าที่อาจเกิน 2 พันล้าน

**Sort & Prefix Sum**
```cpp
sort(sort_array.begin(), sort_array.end());
vector<long long> num_before(N);
    num_before[0] = sort_array[0].second;
    for (int i = 0 ; i < N - 1 ; i++) {
        num_before[i + 1] = num_before[i] + sort_array[i + 1].second;
    }
}
```
* `sort(sort_array.begin(), sort_array.end());`: เรียงลำดับคู่ข้อมูล โดยจะเรียงตามตัวหน้า (X) ก่อน ทำให้เรารู้ลำดับของตัวเลขจากน้อยไปมาก
* สร้าง `num_before`: เป็น Array ที่เก็บ "ตำแหน่งสุดท้าย" ของตัวเลขชุดนั้นๆ
  * `num_before[i]` จะเก็บผลรวมจำนวนตัวเลขทั้งหมดตั้งแต่ชุดที่ 0 ถึงชุดที่ i
  * นี่คือแผนที่ที่บอกว่า "ตัวเลขชุดที่ i สิ้นสุดที่ Index ไหน"
---

**Query Processing**
```cpp
for (int i = 0 ; i < Q ; i++) {
    long long input;
    cin >> input;
    long long real_idx = lower_bound(num_before.begin(),num_before.end(),input) - num_before.begin();
    cout << sort_array[real_idx].first << endl;
}
```
* รับค่า `input` (ตำแหน่ง P ที่โจทย์ถาม)
* `lower_bound(..., input)`: ค้นหาค่าตัวแรกใน `num_before` ที่มีค่า มากกว่าหรือเท่ากับ `input`
* นำ Index ที่ได้จาก `lower_bound` ไปชี้กลับไปที่ `sort_array` เพื่อเอาค่า X (ค่าตัวเลข) มาตอบ

## 3. ตัวอย่าง Test Case

### Input

```
5 2 
1 1 
10 1 
5 1 
1 1 
3 1 
5 
1
```
**Step 1: รับค่าและ Sort** ข้อมูลดิบ: `(1,1), (10,1), (5,1), (1,1), (3,1)` หลังจาก `sort()` (เรียงตามค่าตัวเลข):

|Index (i) | 0 |1 | 2 | 3 | 4
| ---- | ---- | ---- | ---- | ---- | ----
|Pair (Val, Count)| (1, 1) | (1, 1) | (3, 1) | (5, 1) | (10, 1)

**Step 2: สร้างตาราง Prefix Sum** (`num_before`)คำนวณตำแหน่งสิ้นสุดของแต่ละบล็อก:
* i = 0: จบที่ 1
* i = 1: จบที่ 1 + 1 = 2
* i = 2: จบที่ 2 + 1 = 3
* i = 3: จบที่ 3 + 1 = 4
* i = 4: จบที่ 4 + 1 = 5
จะได้ `num_before` = `[1, 2, 3, 4, 5]`

**Visualization (จำลอง Array เสมือน):** Array จริงๆ หน้าตาจะเป็นแบบนี้ (ถ้าเราสร้างมัน): `[ 1, 1, 3, 5, 10 ]` ตำแหน่ง: `1 2 3 4 5`

**Step 3: การตอบคำถาม (Query)**

**คำถามที่ 1:** ต้องการตำแหน่งที่ 5
* ดูที่ `num_before`: `[1, 2, 3, 4, 5]`
* ใช้ `lower_bound` หาเลข 5
* เจอที่ Index `4` (ค่าคือ 5)
* ไปดู `sort_array[4]` คือคู่ `(10, 1)`
* **คำตอบคือ 10**
**คำถามที่ 2:** ต้องการตำแหน่งที่ 1
* ดูที่ `num_before`: `[1, 2, 3, 4, 5]`
* ใช้ `lower_bound` หาเลข 1
* เจอที่ Index `0` (ค่าคือ 1)
* ไปดู `sort_array[0]` คือคู่ `(1, 1)`
* **คำตอบคือ 1**

### Output

```
10
1
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O((N + Q)logN)`
  * Big-Θ: `Θ((N + Q)logN)`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long N,Q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> N >> Q;
    vector<pair<long long, long long>> sort_array(N);
    for (int i = 0; i < N; ++i) {
        cin >> sort_array[i].first >> sort_array[i].second;
    }
    sort(sort_array.begin(), sort_array.end());

    vector<long long> num_before(N);
    num_before[0] = sort_array[0].second;
    for (int i = 0 ; i < N - 1 ; i++) {
        num_before[i + 1] = num_before[i] + sort_array[i + 1].second;
    }

    for (int i = 0 ; i < Q ; i++) {
        long long input;
        cin >> input;
        long long real_idx = lower_bound(num_before.begin(),num_before.end(),input) - num_before.begin();
        cout << sort_array[real_idx].first << endl;
    }
}
```