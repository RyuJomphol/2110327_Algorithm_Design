# Virus 2

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

**ส่วนที่ 1: โครงสร้างข้อมูล (Struct)**

```cpp
struct virus {
    bool is_divoc;  // เก็บสถานะว่าเป็นไวรัสที่ถูกต้องตามกฎหรือไม่
    int count_one;  // เก็บจำนวนเลข 1 ในช่วงนั้นๆ (เพื่อใช้เทียบกับอีกฝั่ง)
};
```

* เราจำเป็นต้องส่งค่ากลับ 2 ค่า คือ "เป็น/ไม่เป็น" และ "จำนวนเลข 1" จึงสร้าง `struct` ขึ้นมาเพื่อมัดรวมข้อมูลนี้ส่งกลับขึ้นไปใน Recursion

**ส่วนที่ 2: ฟังก์ชันตรวจสอบ (Recursive Function)**

```cpp
virus test_divoc(vector<int> gene , int start , int end , int k) {
    // Base Case: เมื่อแบ่งจนเหลือขนาดเล็กที่สุด (k=0 หรือความยาว 1 ตัว)
    if (k == 0) {
        // ถือว่าเป็นจริงเสมอ และส่งค่าตัวเลขนั้นกลับไปเป็น count_one (0 หรือ 1)
        return {true, gene[start]};
    }

    // Divide: หาจุดกึ่งกลาง
    int mid = (start + end) / 2;

    // Conquer: เรียกตัวเองซ้ำเพื่อเช็คฝั่งซ้ายและขวา ลดค่า k ลงทีละ 1
    virus left = test_divoc(gene, start, mid, k - 1);
    virus right = test_divoc(gene, mid + 1, end, k - 1);

    // Combine: เช็คเงื่อนไขสำคัญ
    // 1. ซ้ายต้องผ่าน 2. ขวาต้องผ่าน 3. จำนวนเลข 1 ต่างกันไม่เกิน 1
    bool current_is_divoc = left.is_divoc && right.is_divoc && (abs(left.count_one - right.count_one) <= 1);

    // Return: ส่งผลลัพธ์และผลรวมเลข 1 ของชั้นนี้กลับขึ้นไป
    return {current_is_divoc, left.count_one + right.count_one};
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