# Line Paint

## 1. วิเคราะห์โจทย์

โจทย์ข้อนี้เรียกกันว่า **Interval Merging (การรวมช่วง)**
**เป้าหมาย:** รวมช่วงที่ทับกัน (Overlap) หรือติดกันให้เป็นช่วงเดียว เพื่อให้จำนวนช่วงน้อยที่สุด

**หลักการคิด (Algorithm: Sort & Sweep)** หัวใจสำคัญของการแก้โจทย์นี้คือ **"ถ้าเราเรียงลำดับช่วงตามจุดเริ่มต้น (Start Time) เราจะเช็คการซ้อนทับได้ง่ายมาก"**
**ขั้นตอนการทำงาน:**
* **เก็บข้อมูล:** เก็บช่วงทั้งหมด N ช่วง ในรูปแบบคู่ลำดับ `(start, end)`
* **เรียงลำดับ (Sorting):** เรียงข้อมูลทั้งหมดจากน้อยไปมาก โดยดูที่ค่า `start` เป็นหลัก
* **การรวมช่วง (Merging):** สร้างตัวแปรมาเก็บ "ช่วงปัจจุบันที่กำลังพิจารณา" (`current_start, current_end`) แล้ววนลูปดูช่วงถัดไป:
  * ถ้าช่วงถัดไป **ซ้อนทับ** หรือ **ต่อกันพอดี** กับช่วงปัจจุบัน -> ให้ขยาย `current_end` ไปให้ไกลที่สุด
  * ถ้าช่วงถัดไป **ขาดตอน** (ไม่ซ้อนทับ) -> แปลว่าช่วงปัจจุบันสิ้นสุดแล้ว ให้บันทึก/ปริ้นผลลัพธ์ แล้วเริ่มนับช่วงใหม่
---

## 2. แนวคิดหลัก
มาดูการทำงานของโค้ดทีละส่วน

**สร้าง struct หรือ pair เพื่อเก็บช่วง a ถึง b** 
 ```cpp
struct Interval {
    int start, end;
    bool operator<(const Interval& other) const {
        if (start != other.start)
            return start < other.start;
        return end < other.end;
    }
};
```
* สร้างเพื่อใช้สำหรับ sort ตามค่า start และ end

**Sort**
```cpp
int n;
    cin >> n;
    vector<Interval> intervals(n);
    vector<int> result;
    for (int i = 0 ; i < n ; i++) {
        cin >> intervals[i].start >> intervals[i].end;
    }

    sort(intervals.begin(), intervals.end());
```
* `intervals:`: เป็น Array ที่เก็บ "ช่วง" การทาสีไว้ 
* สร้าง `result`: เป็น Array ที่เก็บผลลัพธ์
---

**Merging Logic**
```cpp
int current_start = intervals[0].start;
int current_end = intervals[0].end;

for (int i = 1; i < n; i++) {
    if (intervals[i].start <= current_end + 1) {
        current_end = max(current_end, intervals[i].end);
    } else {
        cout << current_start << " " << current_end << " ";
            
        current_start = intervals[i].start;
        current_end = intervals[i].end;
    }
}
    
cout << current_start << " " << current_end;
```
* กำหนดให้ `start` , `end` คู่แรก
* เช็คว่าช่วงถัดไป ซ้อนทับ หรือ ต่อกันพอดี กับช่วงปัจจุบันหรือไม่ เงื่อนไข: start ตัวถัดไป <= end ตัวปัจจุบัน + 1 (+1 เพราะโจทย์ระบายสี ถ้า 1-5 และ 6-10 ถือว่าต่อกันเป็น 1-10)
  * ถ้ารวมได้ ให้ขยาย current_end เป็นค่าที่มากที่สุด
  * ถ้ารวมไม่ได้ (ขาดตอน) ให้บันทึกช่วงเก่า
* อย่าลืมปริ้นช่วงชุดสุดท้าย

## 3. ตัวอย่าง Test Case

### Input

```
6 
5 10 
15 20 
25 30 
35 40 
7 37 
2 3
```
**ขั้นตอนการทำงาน (Step-by-Step Execution)**

**Step 1: Sorting** (สำคัญมาก! ต้องเรียงก่อนเสมอ)หลังจากเรียงลำดับตามค่าเริ่มต้น (`start`) จะได้ลำดับใหม่ดังนี้:
`2  3` `5  10` `7  37` `15 20` `25 30` `35 40`

**Step 2: Sweeping (กวาดและรวม)**
* **รอบที่ 1 (เริ่ม):** หยิบ `[2, 3]` มาถือไว้
  * `Current`: Start=2, End=3
* **รอบที่ 2 (เจอ [5, 10]):**
  * เช็ค: `5` (ตัวใหม่) <= `3 + 1` (ตัวเก่า) หรือไม่?
  * ผล: **ไม่** (เกิดช่องว่าง)
  * Action: **Output "2 3"** และเริ่มช่วงใหม่ `[5, 10]`
  * `Current`: Start=5, End=10
* **รอบที่ 3 (เจอ [7, 37]):**
  * เช็ค: `7` <= `10 + 1` หรือไม่?
  * ผล: **ใช่** (ซ้อนทับกัน)
  * Action: ขยาย End เป็น `max(10, 37)` -> 37
  * `Current`: Start=5, End=37
* **รอบที่ 4 (เจอ [15, 20]):**
  * เช็ค: `15` <= `37 + 1` หรือไม่?
  * ผล: **ใช่** (อยู่ในช่วง)
  * Action: ขยาย End เป็น `max(37, 20)` -> 37 (เท่าเดิม)
  * `Current`: Start=5, End=37
* **รอบที่ 5 (เจอ [25, 30]):**
  * เช็ค: `25` <= `37 + 1` หรือไม่?
  * ผล: **ใช่** (อยู่ในช่วง)
  * Action: ขยาย End เป็น `max(37, 30)` -> 37 (เท่าเดิม)
  * `Current`: Start=5, End=37
* **รอบที่ 6 (เจอ [35, 40]):**
  * เช็ค: `35` <= `37 + 1` หรือไม่?
  * ผล: **ใช่** (ซ้อนทับช่วงปลาย)
  * Action: ขยาย End เป็น `max(37, 40)` -> 40
  * `Current`: Start=5, End=40
* **จบข้อมูล:** Output ช่วงสุดท้ายที่ถือไว้ "**5 40**"

**Visual Trace**

```
Input (Sorted):
1. [2-3]
2.      [5----10]
3.        [7--------------------------37]
4.                [15--20]
5.                          [25--30]
6.                                    [35--40]

Process (การรวม):
   [2-3]  <-- แยกเป็นกลุ่มแรก (จบเพราะ 5 > 3+1)
   
        [5----10]
          +
          [7--------------------------37] (Merge: 5 ถึง 37)
                                      +
                                      [35--40] (Merge: 5 ถึง 40)
        
Result (ผลลัพธ์):
   [2-3] [5--------------------------------40]
```

### Output

```
2 3 5 40
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(NlogN)`
  * Big-Θ: `Θ(NlogN)`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int start, end;
    bool operator<(const Interval& other) const {
        if (start != other.start)
            return start < other.start;
        return end < other.end;
    }
};

int main() {
    int n;
    cin >> n;
    vector<Interval> intervals(n);
    vector<int> result;
    for (int i = 0 ; i < n ; i++) {
        cin >> intervals[i].start >> intervals[i].end;
    }

    sort(intervals.begin(), intervals.end());

    int current_start = intervals[0].start;
    int current_end = intervals[0].end;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start <= current_end + 1) {
            current_end = max(current_end, intervals[i].end);
        } else {
            cout << current_start << " " << current_end << " ";
            
            current_start = intervals[i].start;
            current_end = intervals[i].end;
        }
    }
    
    cout << current_start << " " << current_end;

    return 0;
}
```