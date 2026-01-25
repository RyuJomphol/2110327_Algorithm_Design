# Triforce

## 1. วิเคราะห์โจทย์

**แนวคิดหลัก:** โจทย์ข้อนี้เป็นปัญหาลักษณะ **Fractal** หรือโครงสร้างที่ซ้อนทับกันเป็นชั้นๆ (Recursive Structure) โดยมีเงื่อนไขการตรวจสอบที่ชัดเจนระหว่าง "กรณีฐาน" (ขนาดเล็กสุด) และ "กรณีแบ่งส่วน" (ขนาดใหญ่)

**วิธีการแก้ปัญหา:** ใช้เทคนิค **Divide and Conquer (แบ่งแยกและเอาชนะ)** หรือ **Recursion (การเรียกซ้ำ)**

* **Divide (แบ่ง):** แบ่งตารางขนาด $n \times n$ ออกเป็น 4 ส่วนย่อยขนาด $\frac{n}{2} \times \frac{n}{2}$ ได้แก่ $P$ (บนซ้าย), $Q$ (บนขวา), $R$ (ล่างซ้าย), และ $S$ (ล่างขวา)
* **Conquer (เอาชนะ):**
  * ตรวจสอบส่วน $S$ ว่าเป็นเลข 0 ทั้งหมดหรือไม่
  * เรียกฟังก์ชันตัวเองซ้ำ (Recursion) เพื่อหา "ประเภท" ของ $P, Q, R$
* **Combine (รวมผลลัพธ์):**
  * ถ้า $P, Q, R$ คืนค่ามาเป็นประเภทที่ถูกต้อง (ไม่ใช่ 0) และ $S$ เป็น 0 ทั้งหมด
  * ให้นับว่าประเภทของ $P, Q, R$ มีตัวไหนซ้ำกันบ้าง (Majority Vote) แล้วคืนค่าประเภทนั้นกลับไป
* Base Case (กรณีฐาน): เมื่อ $n = 2$ ให้ตรวจสอบตามเงื่อนไขเฉพาะที่โจทย์กำหนด

---

## 2. แนวคิดหลัก

**ส่วนที่ 1: การประกาศตัวแปรและฟังก์ชันเช็ค 0 (`isAllZero`)**

```cpp
int grid[256][256]; // จองพื้นที่ตารางขนาดใหญ่สุด (2^8 = 256) เป็น Global เพื่อให้ทุกฟังก์ชันเรียกใช้ได้

// ฟังก์ชันตรวจสอบว่าพื้นที่สี่เหลี่ยมย่อย เป็นเลข 0 ทั้งหมดหรือไม่
// r, c = พิกัดเริ่มต้น (แถว, หลัก), s = ขนาด (size)
bool isAllZero(int r, int c, int s) {
    for (int i = r; i < r + s ; i++) {
        for (int j = c; j < c + s ; j++) {
            if (grid[i][j] != 0) return false; // ถ้าเจอตัวที่ไม่ใช่ 0 แม้แต่ตัวเดียว ให้ตอบ false ทันที
        }
    }
    return true; // ถ้าวนครบแล้วไม่เจออะไรผิดปกติ แสดงว่าเป็น 0 ทั้งหมด
}
```

**ส่วนที่ 2: ฟังก์ชันหลักในการหาคำตอบ (`getTriforceType`)**
ฟังก์ชันนี้แบ่งการทำงานเป็น 2 ส่วน คือ **Base Case** (หยุดเรียกซ้ำ) และ **Recursive Step** (เรียกซ้ำ)

**2.1 Base Case: เมื่อ n = 2** นี่คือหน่วยย่อยที่สุดของ Triforce

```cpp
int getTriforceType(int r, int c, int n) {
    if (n == 2) {
        // เงื่อนไข 1: ช่องล่างขวา (grid[r+1][c+1]) ต้องเป็น 0
        if (grid[r + 1][c + 1] != 0) return 0;

        int v1 = grid[r][c];         // บนซ้าย
        int v2 = grid[r][c + 1];     // บนขวา
        int v3 = grid[r + 1][c];     // ล่างซ้าย

        // เงื่อนไข 2: ทั้ง 3 ช่องที่เหลือ ต้องไม่ใช่ 0
        if (v1 == 0 || v2 == 0 || v3 == 0) return 0;

        // เงื่อนไข 3: หาคู่ที่ซ้ำกัน (v1==v2 หรือ v1==v3 หรือ v2==v3)
        if (v1 == v2 || v1 == v3) return v1;
        if (v2 == v3) return v2;

        return 0; // ถ้าตัวเลขไม่ซ้ำกันเลย ก็ไม่ใช่ Triforce
    }
    // ... (ต่อส่วน Recursive)
```
**2.2 Recursive Step: เมื่อ n > 2** บ่งปัญหาใหญ่เป็นปัญหาย่อย

```cpp
int m = n / 2; // หาขนาดครึ่งหนึ่ง

    // ขั้นตอนสำคัญ: เช็คส่วน S (ล่างขวา) ก่อนเพื่อนเลย
    // พิกัดของ S คือ (r+m, c+m) ถ้าไม่เป็น 0 ทั้งหมด ก็จบเลย ไม่ต้องไปเช็ค P,Q,R ให้เสียเวลา
    if(!isAllZero(r + m, c + m, m)) return 0;

    // เรียกตัวเองซ้ำ (Recursion) เพื่อไปถามว่า P, Q, R เป็น Triforce ประเภทไหน
    int typeP = getTriforceType(r, c, m);       // P: บนซ้าย
    int typeQ = getTriforceType(r, c + m, m);   // Q: บนขวา
    int typeR = getTriforceType(r + m, c, m);   // R: ล่างซ้าย

    // ถ้าส่วนประกอบย่อยส่วนใดส่วนหนึ่ง "พัง" (เป็น 0) ของใหญ่ก็พังด้วย
    if (typeP == 0 || typeQ == 0 || typeR == 0) return 0;

    // หา Majority Vote: ถ้ามี 2 ใน 3 ส่วน เป็นประเภทเดียวกัน ให้ตอบประเภทนั้น
    if (typeP == typeQ || typeP == typeR) return typeP;
    if (typeQ == typeR) return typeQ;

    return 0; // ถ้า P, Q, R เป็นคนละเลขหมดเลย (เช่น 1, 2, 3)
}
```

**ส่วนที่ 3: ฟังก์ชันหลัก (Main)**
* รับค่า $n$ และ $k$
* คำนวณความยาวอาเรย์ด้วย `pow(2, k)`
* วนลูปรับข้อมูลทีละชุด แล้วเรียก `test_divoc` จากนั้นพิมพ์ `yes` หรือ `no` ตามผลลัพธ์ `final_result.is_divoc`

---

## 3. ตัวอย่าง Test Case

### Input

```
4
1 1 2 2
1 0 1 0
1 2 0 0
2 0 0 0
8
1 1 2 2 3 3 2 1
1 0 1 0 1 0 1 0
1 2 0 0 1 3 0 0
2 0 0 0 3 0 0 0
2 1 2 2 0 0 0 0
2 0 2 0 0 0 0 0
2 1 0 0 0 0 0 0
2 0 0 0 0 0 0 0
2
1 2
3 0 
```

**Test Case 1: n = 4**

```
1 1 2 2 
1 0 1 0 
1 2 0 0 
2 0 0 0
```

**Step 1: แบ่งเป็น 4 ส่วน (P, Q, R, S)**
ขนาด $n=4$ แบ่งครึ่งเป็น $m=2$

```
+-------+-------+
| P     | Q     |
| 1 1   | 2 2   |
| 1 0   | 1 0   |
+-------+-------+
| R     | S     |
| 1 2   | 0 0   |
| 2 0   | 0 0   |
+-------+-------+
```

**Step 2: ตรวจสอบ S (ล่างขวา)**
* $S$ เป็น `0 0 / 0 0` $\rightarrow$ **ผ่าน** (เป็น 0 ทั้งหมด)

**Step 3: ตรวจสอบ P, Q, R (ขนาด 2x2)**
* **P (บนซ้าย):**
  * มุมขวาล่างเป็น 0 $\rightarrow$ ผ่าน
  * เลขที่เหลือ: 1, 1, 1
  * มีเลขซ้ำกันคือ 1 $\rightarrow$ **P เป็น Triforce ประเภท 1**
* **Q (บนขวา):**
  * มุมขวาล่างเป็น 0 $\rightarrow$ ผ่าน
  * เลขที่เหลือ: 2, 2, 1
  * มีเลขซ้ำกันคือ 2 $\rightarrow$ **Q เป็น Triforce ประเภท 2**
* **R (ล่างซ้าย):**
  * มุมขวาล่างเป็น 0 $\rightarrow$ ผ่าน
  * เลขที่เหลือ: 1, 2, 2
  * มีเลขซ้ำกันคือ 2 $\rightarrow$ **R เป็น Triforce ประเภท 2**
* **Step 4: ประมวลผลรวม**
  * ได้ประเภทมาคือ: `P=1`, `Q=2`, `R=2`
  * หาตัวซ้ำ (Majority): มีเลข 2 ซ้ำกันสองตัว
  * **คำตอบ:** 2

**Test Case 2: n = 8**

```
Input Matrix (8x8)
---------------------------------
P (4x4)         | Q (4x4)
(ผลลัพธ์เป็น 2)   | (ผลลัพธ์เป็น ?) 
                | 
----------------+----------------
R (4x4)         | S (4x4)
(ผลลัพธ์เป็น ?)   | 0 0 0 0
                | 0 0 0 0
                | 0 0 0 0
                | 0 0 0 0
---------------------------------
```

* **เช็ค S:** เป็น 0 ทั้งหมด $\rightarrow$ ผ่าน
* **เช็ค P, Q, R:** ระบบจะเรียก Recursion ลงไปเช็คย่อยๆ แบบเดียวกับ Test Case 1 สุดท้ายจะได้คำตอบออกมา
* **คำตอบ:** 2 (ตาม Output ตัวอย่าง)

**Test Case 3: n = 2**

```
1 2 
3 0
```

**Step 1: เข้าเงื่อนไข Base Case ทันที** ($n=2$)
* ตำแหน่ง $A[2][2]$ (ล่างขวา) เป็น 0 $\rightarrow$ ผ่าน
* ตำแหน่งที่เหลือคือ $1, 2, 3$
* ตรวจสอบว่ามีเลขไหนซ้ำกันไหม?
  * 1 ไม่เท่ากับ 2
  * 1 ไม่เท่ากับ 3
  * 2 ไม่เท่ากับ 3
* ไม่มีคู่ซ้ำเลย
* **คำตอบ:** 0

### Output

```
2
2
0
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: $O(n^2)$

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>

using namespace std;

int grid[256][256];

bool isAllZero(int r, int c, int s) {
    for (int i = r; i < r + s ; i++) {
        for (int j = c; j < c + s ; j++) {
            if (grid[i][j] != 0) return false;
        }
    }
    return true;
}

int getTriforceType(int r, int c, int n) {
    if (n == 2) {
        if (grid[r + 1][c + 1] != 0) return 0;

        int v1 = grid[r][c];
        int v2 = grid[r][c + 1];
        int v3 = grid[r + 1][c];

        if (v1 == 0 || v2 == 0 || v3 == 0) return 0;

        if (v1 == v2 || v1 == v3) return v1;
        if (v2 == v3) return v2;

        return 0;
    }

    int m = n / 2;

    if(!isAllZero(r + m, c + m, m)) return 0;

    int typeP = getTriforceType(r, c, m);
    int typeQ = getTriforceType(r, c + m, m);
    int typeR = getTriforceType(r + m, c, m);

    if (typeP == 0 || typeQ == 0 || typeR == 0) return 0;

    if (typeP == typeQ || typeP == typeR) return typeP;
    if (typeQ == typeR) return typeQ;

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int test = 0 ; test < 3 ; test++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
        cout << getTriforceType(0, 0, n) << "\n";
    }
}
```