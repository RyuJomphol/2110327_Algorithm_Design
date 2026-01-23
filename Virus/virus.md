# Virus

## 1. วิเคราะห์โจทย์

**โจทย์ต้องการอะไร:** นี่คือโจทย์แนว **Divide and Conquer (แบ่งแยกและเอาชนะ)**
โจทย์กำหนดโครงสร้างแบบ **Recursive (เวียนเกิด)** ชัดเจน:
* **Base Case ($k=1$):** ไวรัสต้องเป็น `[0, 1]` เท่านั้น
* **Recursive Step ($k > 1$):**
  * ไวรัสขนาด $2^k$ เกิดจาก ไวรัสขนาด $2^{k-1}$ สองตัวมาต่อกัน (ซ้าย + ขวา)
  * **กฎสำคัญ:** ส่วน "ขวา" จะต้องเป็นไวรัสที่สมบูรณ์เสมอ แต่ส่วน "ซ้าย" อาจจะเป็นไวรัสสมบูรณ์ **หรือ** ไวรัสที่ถูกกลับด้าน (Reverse) ก็ได้

**อัลกอริทึม (Algorithm Logic):** เราจะเขียนฟังก์ชัน `check(array)` ที่ทำงานดังนี้:
* ถ้าความยาวอาเรย์คือ 2: เช็คเลยว่าคือ `[0, 1]` หรือไม่? ถ้าใช่คืนค่า `True` ถ้าไม่ใช่ `False`
* ถ้าความยาว > 2: แบ่งอาเรย์เป็นครึ่งซ้าย (`Left`) และครึ่งขวา (`Right`)
* ตรวจสอบครึ่งขวา (`Right`): **ต้อง** เป็นไวรัสที่ถูกต้อง (`check(Right)` ต้องเป็น `True`)
* ตรวจสอบครึ่งซ้าย (`Left`):
  * กรณี 1: `Left` เป็นไวรัสปกติ (`check(Left)` เป็น `True`) -> **ผ่าน**
  * กรณี 2: `Left` เป็นไวรัสกลายพันธุ์ ให้ลองกลับด้าน Left แล้วเช็ค (`check(reverse(Left))` เป็น `True`) -> **ผ่าน**
* ถ้าเงื่อนไขข้อ 3 และ 4 เป็นจริงทั้งคู่ จึงจะตอบว่า **"yes"**

---

## 2. แนวคิดหลัก

**ส่วน Include และ namespace**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
```

* `<iostream>` ใช้สำหรับ input / output
* `<vector>` ใช้เก็บ sequence ของตัวเลข
* `<algorithm>` ใช้ฟังก์ชัน `reverse()`
* `<cmath>` ใช้ฟังก์ชัน `pow()`
* `using namespace std;` เพื่อลดการเขียน `std::`

---

**ส่วน** `ฟังก์ชัน isDivoc`:
```cpp
bool isDivoc(vector<int> v , int k)
```

ฟังก์ชันนี้ใช้ตรวจสอบว่า vector `v` เป็น Divoc sequence ระดับ `k` หรือไม่

**Base Case**

```cpp
if (k == 1) {
    return (v.size() == 2 && v[0] == 0 && v[1] == 1);
}
```

* เมื่อ `k == 1` ความยาว sequence ต้องเป็น 2
* Divoc ที่ถูกต้องในระดับนี้ต้องเป็น `[0, 1]` เท่านั้น

ถ้าไม่ตรง → return `false`

---

**Divide (แบ่งปัญหา)**

```cpp
int n = v.size();
int mid = n / 2;

vector<int> left(v.begin(), v.begin() + mid);
vector<int> right(v.begin() + mid, v.end());
```

* แบ่ง vector ออกเป็น 2 ส่วนเท่า ๆ กัน

  * `left`  = ครึ่งซ้าย
  * `right` = ครึ่งขวา

---

**ตรวจสอบฝั่งขวา (บังคับต้องถูก)**

```cpp
if (!isDivoc(right, k - 1)) {
    return false;
}
```

* **เงื่อนไขสำคัญของ Divoc**
* ครึ่งขวา *ต้อง* เป็น Divoc ระดับ `k-1`
* ถ้าไม่ใช่ → ตัดสินได้ทันทีว่าไม่ใช่ Divoc

---

**ตรวจสอบฝั่งซ้าย (ยืดหยุ่นได้)**

```cpp
bool leftNormal = isDivoc(left, k - 1);

reverse(left.begin(), left.end());
bool leftReversed = isDivoc(left, k - 1);

return leftNormal || leftReversed;
```

ฝั่งซ้ายมี 2 ความเป็นไปได้:

1. เป็น Divoc ตามลำดับเดิม
2. เป็น Divoc หลังจากกลับลำดับ (reverse)

ถ้า **อย่างใดอย่างหนึ่งเป็นจริง** → ถือว่า valid

นี่คือจุดที่ทำให้โจทย์ไม่ใช่ brute force แต่เป็น **recursive decision**

---

**ส่วน** `main`:

```cpp
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
```

* เพิ่มความเร็วในการรับ–ส่งข้อมูล (เหมาะกับ input ขนาดใหญ่)

---

**รับค่า n และ k**

```cpp
int n,k;
cin >> n >> k;
int length = pow(2, k);
```

* `n` = จำนวน sequence
* `k` = ระดับ Divoc
* ความยาวของ sequence = `2^k`

---

**อ่าน sequence และตรวจสอบ**

```cpp
for (int i = 0; i < n; i++) {
    vector<int> sequence(length);
    for (int j = 0; j < length; j++) {
        cin >> sequence[j];
    }
```

* อ่านข้อมูลแต่ละ sequence เข้า vector

---

**แสดงผลลัพธ์**

```cpp
if (isDivoc(sequence, k)) {
    cout << "yes" << endl;
} else {
    cout << "no" << endl;
}
```

* เรียกฟังก์ชัน `isDivoc`
* ถ้าเป็น Divoc → `yes`
* ถ้าไม่ใช่ → `no`

---

## 3. ตัวอย่าง Test Case

### Input

```
5 2
1 0 1 0
0 1 1 0
0 1 0 1
1 0 0 1
0 1 0 1
```

**Case 1:** `1 0 1 0` **(Output: no)**
```
Step 1: ตรวจสอบ [1 0 1 0] (ขนาด 4)
        แบ่งเป็น ซ้าย=[1 0], ขวา=[1 0]

Step 2: เช็ค "ขวา" [1 0] ก่อน
        Base Case: ขนาด 2
        เป็น [0 1] หรือไม่? -> ไม่ใช่ (มันคือ 1 0) -> Return False

Result: เนื่องจากขวาผิดกฎ จึงตอบ "no" ทันที
```

**Case 2:** `0 1 1 0` **(Output: no)**
```
Step 1: ตรวจสอบ [0 1 1 0] (ขนาด 4)
        แบ่งเป็น ซ้าย=[0 1], ขวา=[1 0]

Step 2: เช็ค "ขวา" [1 0]
        เป็น [0 1] หรือไม่? -> ไม่ใช่ -> Return False

Result: "no"
```


**Case 4:** `1 0 0 1` **(Output: yes)**
```
[ START ] ตรวจสอบ: 1 0 0 1
    |
    |--- แบ่งครึ่ง: Left=[1 0], Right=[0 1]
    |
    |--- 1. ตรวจสอบ Right [0 1]
    |       |---> ขนาด 2 และเป็น [0 1] -> [PASS]
    |
    |--- 2. ตรวจสอบ Left [1 0]
            |
            |---> ลองแบบปกติ: เช็ค [1 0]
            |       |---> ขนาด 2 แต่ไม่ใช่ [0 1] -> [FAIL]
            |
            |---> ลองแบบกลายพันธุ์: Reverse [1 0] กลายเป็น [0 1]
                    |---> เช็ค [0 1]
                            |---> ขนาด 2 และเป็น [0 1] -> [PASS]

Result: ขวาผ่าน และ ซ้าย(แบบกลายพันธุ์)ผ่าน -> ตอบ "yes"
```

### Output

```
no
no
yes
yes
yes
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(n log n)`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool isDivoc(vector<int> v , int k) {
    if (k == 1) {
        return (v.size() == 2 && v[0] == 0 && v[1] == 1);
    }

    int n = v.size();
    int mid = n / 2;

    vector<int> left(v.begin(), v.begin() + mid);
    vector<int> right(v.begin() + mid, v.end());

    if (!isDivoc(right, k - 1)) {
        return false;
    }

    bool leftNormal = isDivoc(left, k - 1);
    
    reverse(left.begin(), left.end());
    bool leftReversed = isDivoc(left, k - 1);

    return leftNormal || leftReversed;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,k;
    cin >> n >> k;
    int length = pow(2, k);

    for (int i = 0; i < n; i++) {
        vector<int> sequence(length);
        for (int j = 0; j < length; j++) {
            cin >> sequence[j];
        }

        if (isDivoc(sequence, k)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
}
```