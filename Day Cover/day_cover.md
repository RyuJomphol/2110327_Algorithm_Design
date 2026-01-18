# Day Cover

## 1. วิเคราะห์โจทย์

**โจทย์ต้องการหาจำนวนนิสิตที่ น้อยที่สุด (min)** ที่เมื่อรวมวันว่างของทุกคนแล้ว จะต้องครอบคลุมทุกวันตั้งแต่วันที่ 1 ถึง n

**ข้อจำกัด (Constraints):** 
* จำนวนวัน n <= 1000
* จำนวนนิสิต m <= 20

**วิธีการแก้ปัญหาในโค้ด (Algorithm):** เนื่องจากจำนวนนิสิต (m) มีค่าน้อยมาก (ไม่เกิน 20 คน) เราจึงสามารถใช้วิธี **Brute Force** หรือ **Exhaustive Search** (การค้นหาทุกความเป็นไปได้) ได้ โดยใช้เทคนิค **Recursion (Backtracking)**

เราจะลองพิจารณานิสิตทีละคน (ตั้งแต่นิสิตคนแรกถึงคนสุดท้าย) โดยแต่ละคนเรามีทางเลือก 2 ทางคือ:
  * **1. เลือก** นิสิตคนนี้มาช่วยงาน (จำนวนคนเพิ่มขึ้น, จำนวนวันที่ครอบคลุมเปลี่ยนไป)
  * **2. ไม่เลือก** นิสิตคนนี้ (จำนวนคนเท่าเดิม, จำนวนวันที่ครอบคลุมเท่าเดิม)
  
เมื่อทำจนครบทุกคน หรือได้คำตอบที่ครอบคลุมทุกวันแล้ว เราจะบันทึกค่าจำนวนคนที่น้อยที่สุดเอาไว้ (Global Min)

*เพิ่มเติม:* ในโค้ดมีการใช้เทคนิค **Pruning (การตัดกิ่ง)** คือถ้าจำนวนคนที่เลือกมา ณ ปัจจุบัน มากกว่าหรือเท่ากับค่าต่ำสุดที่เคยหาได้แล้ว เราจะหยุดคิดในเส้นทางนั้นทันที เพื่อประหยัดเวลา

---

## 2. แนวคิดหลัก
มาดูการทำงานของโค้ดทีละส่วน

**ส่วนประกาศตัวแปร (Global Variables):** 
 ```cpp
int student_min = 20;
int n,m;
vector<vector<int>> students;
vector<int> dayCoveredCount;
int currentDaysCovered = 0;
```
* `student_min:` เก็บคำตอบจำนวนนิสิตที่น้อยที่สุด (ตั้งค่าเริ่มต้นไว้สูงๆ คือ 20 เท่ากับ max m)
* `dayCoveredCount:` อาร์เรย์เก็บว่าแต่ละวัน มีคนมาช่วยงานกี่คนแล้ว (ถ้า > 0 แปลว่าวันนั้นมีคนทำแล้ว)
* `currentDaysCovered:` ตัวนับว่าตอนนี้เราครอบคลุมไปแล้วกี่วัน (ถ้าเท่ากับ n คือครบ)

ฟังก์ชัน `combi(studentIdx, num_student_use)`
ฟังก์ชันนี้ทำหน้าที่ตัดสินใจเลือกนิสิตคนที่ studentIdx

**Base Case**
```cpp
if (num_student_use >= student_min) {
    return;
}
    
if (currentDaysCovered == n) {
    student_min = min(student_min, num_student_use);
    return;
}

if (studentIdx == m) {
    return;
}
```
* `if (num_student_use >= student_min):` ถ้าจำนวนคนที่ใช้ตอนนี้ เยอะกว่าสถิติที่ดีที่สุดที่เคยทำได้ ให้หยุด (Pruning)
* `if (currentDaysCovered == n):` ถ้าวันครบแล้ว บันทึกสถิติใหม่ (`student_min`) แล้วหยุด
* `if (studentIdx == m):` ถ้าพิจารณาครบทุกคนแล้วแต่ยังไม่ครบเงื่อนไข ให้หยุด

**Recursive Case**
```cpp
for (int day : students[studentIdx]) {
    if (dayCoveredCount[day] == 0) {
        currentDaysCovered++;
    }
    dayCoveredCount[day]++;
}

combi(studentIdx + 1 , num_student_use + 1);

for (int day : students[studentIdx]) {
    dayCoveredCount[day]--;
    if (dayCoveredCount[day] == 0) {
        currentDaysCovered--;
    }
}

combi(studentIdx + 1, num_student_use);
```
* **1. กรณี "เลือก" นิสิตคนนี้:**
  * วนลูปเอาวันที่นิสิตคนนี้ว่าง ไปบวกเพิ่มใน `dayCoveredCount`
  * ถ้าวันไหนเพิ่งมีคนทำเป็นคนแรก ให้เพิ่ม `currentDaysCovered`
  * เรียก `combi(studentIdx + 1, num_student_use + 1)`
  * **Backtracking (ย้อนกลับ):** หลังจากเรียกฟังก์ชันเสร็จ ต้องคืนค่า `dayCoveredCount` และ `currentDaysCovered` ให้เหมือนเดิม เพื่อให้พร้อมสำหรับกรณีถัดไป
* **2. กรณี "ไม่เลือก" นิสิตคนนี้:**
  * เรียก `combi(studentIdx + 1, num_student_use)` โดยไม่ต้องทำอะไรกับวันว่าง
---

## 3. ตัวอย่าง Test Case พร้อม Recursion Tree

### Input

```
5 4 
3 1 3 5 
3 1 2 3 
2 2 5 
2 3 4
```
* n = 5 (ต้องครบ 5 วัน), m = 4 (มีนิสิต 4 คน)
* คนที่ 0: ว่าง 1, 3, 5
* คนที่ 1: ว่าง 1, 2, 3
* คนที่ 2: ว่าง 2, 5
* คนที่ 3: ว่าง 3, 4

### Recursion Tree

```
Start: combi(S:0, Cnt:0) [Covered: {}]
│
├── [ทางเลือก 1: เลือกนิสิตคนที่ 0 (1,3,5)]
│   State: Cnt=1, Covered={1,3,5} (3/5 วัน)
│   Call: combi(S:1, Cnt:1)
│   │
│   ├── [ทางเลือก 1.1: เลือกนิสิตคนที่ 1 (1,2,3)]
│   │   State: Cnt=2, Covered={1,2,3,5} (4/5 วัน) -> ได้วัน 2 เพิ่มมา
│   │   Call: combi(S:2, Cnt:2)
│   │   │
│   │   ├── [ทางเลือก 1.1.1: เลือกนิสิตคนที่ 2 (2,5)]
│   │   │   State: Cnt=3, Covered={1,2,3,5} (4/5 วัน) -> ไม่ได้วันเพิ่ม (ซ้ำ)
│   │   │   Call: combi(S:3, Cnt:3)
│   │   │   │
│   │   │   ├── [ทางเลือก 1.1.1.1: เลือกนิสิตคนที่ 3 (3,4)]
│   │   │   │   State: Cnt=4, Covered={1,2,3,4,5} (5/5 วัน) -> **ครบ!**
│   │   │   │   Result: update student_min = 4
│   │   │   │   Return (Backtrack)
│   │   │   └── [ทางเลือก 1.1.1.2: ไม่เลือกนิสิตคนที่ 3] ... (ไม่ครบ)
│   │   │
│   │   └── [ทางเลือก 1.1.2: ไม่เลือกนิสิตคนที่ 2]
│   │       State: Cnt=2, Covered={1,2,3,5}
│   │       Call: combi(S:3, Cnt:2)
│   │       │
│   │       ├── [ทางเลือก 1.1.2.1: เลือกนิสิตคนที่ 3 (3,4)]
│   │       │   State: Cnt=3, Covered={1,2,3,4,5} (5/5 วัน) -> **ครบ!**
│   │       │   Result: update student_min = 3 (ดีกว่า 4)
│   │       │   Return (Backtrack)
│   │       └── ...
│   │
│   └── [ทางเลือก 1.2: ไม่เลือกนิสิตคนที่ 1] ...
│
└── [ทางเลือก 2: ไม่เลือกนิสิตคนที่ 0] ...

```
**สรุปการทำงาน:** 
* โปรแกรมจะพยายามเลือกคนแรกๆ เข้ามาก่อน จนกระทั่งครบ 5 วัน
* เส้นทางแรกๆ อาจจะได้คำตอบเป็น 4 คน (เช่น เลือกทุกคน)
* แต่เมื่อ Backtrack และลองเปลี่ยนตัวเลือก (เช่น เลือกคนที่ 0, 1 แล้วข้าม 2 ไปเลือก 3 เลย) จะพบว่าใช้แค่ 3 คนก็ครบแล้ว (min จะถูกอัปเดตเป็น 3)
* ท้ายที่สุดจะได้คำตอบคือ 3

### Output

```
3
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(n * 2^m)`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int student_min = 20; // 1 <= n <= 1000 & 1 <= m <=20
int n,m;
vector<vector<int>> students;
vector<int> dayCoveredCount;
int currentDaysCovered = 0;

void combi(int studentIdx, int num_student_use) {
    if (num_student_use >= student_min) {
        return;
    }
    
    if (currentDaysCovered == n) {
        student_min = min(student_min, num_student_use);
        return;
    }

    if (studentIdx == m) {
        return;
    }

    //(Update State)
    for (int day : students[studentIdx]) {
        if (dayCoveredCount[day] == 0) {
            currentDaysCovered++;
        }
        dayCoveredCount[day]++;
    }

    combi(studentIdx + 1 , num_student_use + 1);

    //(Undo State)
    for (int day : students[studentIdx]) {
        dayCoveredCount[day]--;
        if (dayCoveredCount[day] == 0) {
            currentDaysCovered--;
        }
    }

    combi(studentIdx + 1, num_student_use);
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cin >> n >> m;
    students.resize(m);
    dayCoveredCount.resize(n + 1, 0);

    for (int i = 0 ; i < m ; i++) {
        int k;
        cin >> k;
        students[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> students[i][j];
        }
    }
    combi(0,0);

    cout << student_min << endl;
}
```

**หมายเหตุ**
โค้ดดังกล่าวอาจจะติด `T` ใน grader เคสที่ 15 แนะนำให้เปลี่ยนชื่อตัวแปรให้สั้นลง