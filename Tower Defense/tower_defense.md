# Tower Defense

## 1. วิเคราะห์โจทย์

**โจทย์ต้องการหาค่าพลังรวมของ Monster ที่เหลือน้อยที่สุด (Min Sum HP)** หลังจากเราสั่งให้ป้อมปืน (Towers) ทุกป้อมทำการยิง Monster
**เงื่อนไขสำคัญ:** 
* ป้อมปืน K ป้อม แต่ละป้อมยิงได้ 1 ครั้ง
* ป้อมปืนจะยิง Monster ได้ก็ต่อเมื่อ Monster อยู่ในระยะ W (ช่วง `[t[i]-W, t[i]+W]`)
* เราต้อง "เลือก" ว่าป้อมแต่ละป้อมจะยิง Monster ตัวไหน เพื่อให้ผลลัพธ์ออกมาดีที่สุด

**วิธีการแก้ปัญหาในโค้ด (Algorithm):** ใช้วิธี **Brute Force (Exhaustive Search)** ด้วยการทำ **Recursion (Backtracking)**
* แนวคิด: ลองทุกความเป็นไปได้ในการจับคู่ "ป้อมปืน" กับ "Monster"
* สมมติมีป้อม 2 ป้อม และ Monster 3 ตัว โค้ดจะลองจับคู่ทั้งหมด 3 * 3 = 9 แบบ
* เมื่อจับคู่ครบทุกป้อมแล้ว (Base Case) โปรแกรมจะคำนวณดาเมจจริง โดยเช็คระยะ W และหักลบเลือด Monster เพื่อหาว่าวิธีไหนทำให้เลือดเหลือน้อยที่สุด

---

## 2. แนวคิดหลัก
มาดูการทำงานของโค้ดทีละส่วน

**ส่วนประกาศตัวแปร (Global Variables):** 
 ```cpp
int n; //map size
int m; //number of monsters
int k; //number of towers
int w; //shooting range
vector<int> p; //The position of each monster
vector<int> h; //The health of each monster
vector<int> t; //The location of each turret
vector<int> a; //Which monster does the tower i chose target??
int min_sum = 0;
```
* `n, m, k, w:` รับค่าขนาดแผนที่, จำนวนมอนสเตอร์, จำนวนป้อม, ระยะยิง
* `p, h, t:` เวกเตอร์เก็บตำแหน่งมอนสเตอร์, เลือดมอนสเตอร์, ตำแหน่งป้อม
* `a:` ตัวแปรสำคัญ ใช้เก็บ State ว่า "ป้อมที่ i เลือกยิง Monster ตัวเลขที่ `a[i]`"
* `min_sum:` เก็บค่าเลือดรวมที่ต่ำที่สุดที่เคยเจอ
ฟังก์ชัน shooting(int step):นี่คือฟังก์ชัน Recursive หลัก
* Parameter step: หมายถึงเรากำลังตัดสินใจเลือกเป้าหมายให้ "ป้อมปืนลำดับที่ step"

**Base Case**
```cpp
if (step == k) {
    vector<int> hit(m);
    for (int j = 0 ; j < k ; j++) {
        int tower_pos = t[j];
        int monster_pos = a[j];
        if (abs(p[monster_pos] - tower_pos) <= w) {
            hit[monster_pos]++;
            hit[monster_pos] = min(hit[monster_pos],h[monster_pos]);
        }
    }

    int sum = 0;
    for (int i = 0;i < m;i++) {
        sum += max(h[i] - hit[i],0);
    }

    if (sum < min_sum) {
        min_sum = sum;
    }
}
```
* **(`if (step == k)`):** เมื่อ `step == k` แปลว่าป้อมทุกป้อม (0 ถึง k-1) ได้เลือกเป้าหมายครบแล้ว
  1. สร้างตัวแปร `hit` มานับจำนวนครั้งที่ Monster แต่ละตัวโดนยิง
  2. วนลูปเช็คป้อมทุกป้อม:
    * ถ้า `abs(ตำแหน่งมอน - ตำแหน่งป้อม) <= w` (อยู่ในระยะยิง)
    * ให้เพิ่มค่า `hit` ของ Monster ตัวนั้น (แต่ไม่เกินเลือดที่มี)
  3. คำนวณ `sum:` ผลรวมเลือดที่เหลือของ Monster ทุกตัว (`h[i] - hit[i]`)
  4. อัปเดต `min_sum:` ถ้า sum น้อยกว่าค่าที่เคยหาได้ ให้บันทึกค่าใหม่

**Recursive Case**
```cpp
else {
    for (int i = 0 ; i < m ; i++) {
        a[step] = i;
        shooting(step + 1);
    }
}
```
ส่วนนี้จะทำการสร้าง Tree ของการตัดสินใจ แตกกิ่งไปเรื่อยๆ จนครบทุกป้อม
---

## 3. ตัวอย่าง Test Case พร้อม Recursion Tree

### Input

```
100 3 2 1 
80 70 60 
1 1 1 
70 71 69
```
* N=100, M=3, K=2, W=1
* **Monsters:**
  * M0: Pos 80, HP 1
  * M1: Pos 70, HP 1
  * M2: Pos 60, HP 1
* **Towers:**
  * T0: Pos 70 (ยิงได้ช่วง 69-71) -> ยิงโดน M1 ได้ตัวเดียว
  * T1: Pos 71 (ยิงได้ช่วง 70-72) -> ยิงโดน M1 ได้ตัวเดียว
* **Total HP เริ่มต้น:** $1+1+1 = 3$

### Recursion Tree

```
shooting(0) : ป้อม T0 เลือกเป้าหมาย
├── T0 เล็ง M0 (Pos 80, ระยะห่าง 10 -> ยิงไม่โดน)
│   └── shooting(1) : ป้อม T1 เลือกเป้าหมาย
│       ├── T1 เล็ง M0 (ยิงไม่โดน) -> ทั้งคู่ยิงว่าว -> HP เหลือ 3
│       ├── T1 เล็ง M1 (ยิงโดน!)   -> T1 ลด HP M1 -> HP เหลือ 2 *คำตอบที่ดีที่สุด*
│       └── T1 เล็ง M2 (ยิงไม่โดน) -> ทั้งคู่ยิงว่าว -> HP เหลือ 3
│
├── T0 เล็ง M1 (Pos 70, ระยะห่าง 0 -> ยิงโดน!)
│   └── shooting(1) : ป้อม T1 เลือกเป้าหมาย
│       ├── T1 เล็ง M0 (ยิงไม่โดน) -> T0 ลด HP M1 -> HP เหลือ 2 *คำตอบที่ดีที่สุด*
│       ├── T1 เล็ง M1 (ยิงโดน!)   -> T0 และ T1 รุม M1 (Overkill) -> HP เหลือ 2 *คำตอบที่ดีที่สุด*
│       └── T1 เล็ง M2 (ยิงไม่โดน) -> T0 ลด HP M1 -> HP เหลือ 2 *คำตอบที่ดีที่สุด*
│
└── T0 เล็ง M2 (Pos 60, ระยะห่าง 10 -> ยิงไม่โดน)
    └── shooting(1) : ป้อม T1 เลือกเป้าหมาย
        ├── T1 เล็ง M0 (ยิงไม่โดน) -> HP เหลือ 3
        ├── T1 เล็ง M1 (ยิงโดน!)   -> T1 ลด HP M1 -> HP เหลือ 2 *คำตอบที่ดีที่สุด*
        └── T1 เล็ง M2 (ยิงไม่โดน) -> HP เหลือ 3

```
**สรุปการทำงาน:** โปรแกรมจะวนลูปจนเจอว่า มีหลายกรณีที่ทำให้ HP รวมเหลือ 2 (ต่ำสุดที่เป็นไปได้) จึงตอบ **2**

### Output

```
2
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(M^K * (K + M))`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>

using namespace std;

int n; //map size
int m; //number of monsters
int k; //number of towers
int w; //shooting range
vector<int> p; //The position of each monster
vector<int> h; //The health of each monster
vector<int> t; //The location of each turret
vector<int> a; //Which monster does the tower i chose target??
int min_sum = 0;

using namespace std;

void shooting(int step) {
    if (step == k) {
        vector<int> hit(m);
        for (int j = 0 ; j < k ; j++) {
            int tower_pos = t[j];
            int monster_pos = a[j];
            if (abs(p[monster_pos] - tower_pos) <= w) {
                hit[monster_pos]++;
                hit[monster_pos] = min(hit[monster_pos],h[monster_pos]);
            }
        }

        int sum = 0;
        for (int i = 0;i < m;i++) {
            sum += max(h[i] - hit[i],0);
        }

        if (sum < min_sum) {
            min_sum = sum;
        }
    }
    
    else {
        for (int i = 0 ; i < m ; i++) {
            a[step] = i;
            shooting(step + 1);
        }
    }
}

int main() {
    cin >> n >> m >> k >> w;
    p.resize(m);
    h.resize(m);
    t.resize(k);
    a.resize(k);
    for (int i = 0 ; i < m ; i++) {
        cin >> p[i];
    }
    for (int i = 0 ; i < m ; i++) {
        cin >> h[i];
        min_sum += h[i];
    }
    for (int i = 0 ; i < k ; i++) {
        cin >> t[i];
    }
    shooting(0);
    cout << min_sum << endl;
}
```