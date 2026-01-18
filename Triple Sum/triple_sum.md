# Triple Sum

## 1. วิเคราะห์โจทย์

**โจทย์ต้องการอะไร:** ให้หาว่าในอาร์เรย์ `A` มีตัวเลข 3 ตัวที่ไม่ซ้ำตำแหน่งกัน (i, j, k ต้องต่างกัน) ที่รวมกันแล้วได้ค่าเท่ากับค่า `query` หรือไม่ โดยต้องทำแบบนี้กับหลายๆ query

**เงื่อนไขสำคัญ:**
* **เวลาจำกัด (Time Limit):** 1 วินาที
* **ขนาดข้อมูล:** N <= 600, M <= 200
* **ชนิดข้อมูล:** ค่าผลรวมอาจสูงถึง 1.5 x 10^9 (เพราะ 500,000,000 x 3) ดังนั้นต้องใช้ตัวแปรแบบ `long long` เพื่อป้องกัน Overflow
* **ข้อมูลเรียงแล้ว:** โจทย์บอกว่า "The array A is already sorted" ซึ่งเป็นข้อได้เปรียบมาก

**วิธีแก้ปัญหา (The Algorithm):** หากใช้ Loop 3 ชั้น (O(N^3)) จะคำนวณไม่ทัน (ประมาณ 216,000,000 รอบต่อ 1 query) ดังนั้นเราต้องลดความซับซ้อนลง

เราจะใช้เทคนิค **Fix One, Two Pointers (ล็อกหนึ่ง วิ่งสอง):** 
* ล็อกตัวแรก (A[i]): ใช้ Loop วนเพื่อเลือกตัวเลขตัวแรก
* **หาอีกสองตัวที่เหลือ:** เมื่อเราล็อก A[i] แล้ว โจทย์จะเปลี่ยนเป็น "หาเลข 2 ตัวในส่วนที่เหลือที่รวมกันได้ `query - A[i]`" ซึ่งนี่คือปัญหา **2-Sum**
* **ใช้ Two Pointers:** เนื่องจากอาร์เรย์เรียงแล้ว ให้ตั้งตัวชี้ซ้าย (`left`) ถัดจาก i และตัวชี้ขวา (`right`) ที่ท้ายอาร์เรย์
  * ถ้าผลรวม 3 ตัว **น้อยกว่า** เป้าหมาย -> ขยับ `left` ไปทางขวา (เพื่อเพิ่มค่า)
  * ถ้าผลรวม 3 ตัว **มากกว่า** เป้าหมาย -> ขยับ `right` ไปทางซ้าย (เพื่อลดค่า)
  * ถ้าเจอเท่ากัน -> จบการทำงาน (ตอบ YES)

---

## 2. แนวคิดหลัก
มาดูการทำงานของโค้ดทีละส่วน

```
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 1. รับค่า N (จำนวนข้อมูล) และ M (จำนวนคำถาม)
    int N,M;
    cin >> N >> M;

    // 2. รับค่าอาร์เรย์ A ใช้ long long กันพลาดเรื่องขนาดตัวเลข
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    // 3. เริ่มประมวลผลทีละ Query
    for (int j = 0 ; j < M ; j++) {
        long long num; // ค่าเป้าหมายที่ต้องการ (Target)
        cin >> num;
        bool found = false; // ตัวแปรเช็คว่าเจอหรือไม่

        // 4. Loop ล็อกตัวแรก (A[i])
        // วนถึง N-2 เพราะต้องเหลือที่ให้อีก 2 ตัว (left, right)
        for (int i = 0 ; i < N - 2; i++) {
            
            // 5. ตั้งค่า Two Pointers
            int left = i + 1; // ตัวถัดจาก i
            int right = N - 1; // ตัวสุดท้าย

            // 6. Loop บีบเข้าหากัน
            while (left < right) {
                // คำนวณผลรวม 3 ตัว
                long long current_sum = A[i] + A[left] + A[right];

                if (current_sum == num) {
                    found = true; // เจอแล้ว!
                    break;        // ออกจาก while loop ทันที
                } else if (current_sum < num) {
                    left++;       // ผลรวมน้อยไป ขยับซ้ายไปขวาเพื่อเพิ่มค่า
                } else {
                    right--;      // ผลรวมมากไป ขยับขวามาซ้ายเพื่อลดค่า
                }
            }
            if (found) break; // ถ้าเจอแล้วใน while ก็ออกจาก for loop นี้ด้วย
        }

        // 7. แสดงผลลัพธ์
        if (found) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
```

## 3. ตัวอย่าง Test Case

### Input

```
4 5
-2 1 5 6
1 3 5 6 7
```
**Array A:** `[-2, 1, 5, 6]` (มี 4 ตัว: Index 0 ถึง 3)

**ตัวอย่างที่ 1: Query = 5 (Output: YES)**
เป้าหมายคือหา A[i] + A[L] + A[R] = 5

**Step 1:** ล็อก i ที่ Index 0 (ค่า -2)
* ตั้ง `Left = 1` (ค่า 1), `Right = 3` (ค่า 6)

```
[ -2 ,  1 ,  5 ,  6 ]
  ^     ^         ^
  i     L         R

Sum = (-2) + 1 + 6 = 5
Target = 5
Result: เจอแล้ว! (Equal) -> set found = true -> break
```

**ตัวอย่างที่ 2: Query = 1 (Output: NO)**
เป้าหมายคือหา A[i] + A[L] + A[R] = 1
**Step 1:** ล็อก i ที่ Index 0 (ค่า -2)
* ตั้ง `Left = 1` (ค่า 1), `Right = 3` (ค่า 6)

```
[ -2 ,  1 ,  5 ,  6 ]
  ^     ^         ^
  i     L         R

Sum = (-2) + 1 + 6 = 5
Target = 1
Result: 5 > 1 (มากไป) -> ลดค่าโดยขยับ R ถอยหลัง (R--)
```

**Step 2:** ขยับ `Right` มาที่ Index 2 (ค่า 5)
```
[ -2 ,  1 ,  5 ,  6 ]
  ^     ^    ^
  i     L    R

Sum = (-2) + 1 + 5 = 4
Target = 1
Result: 4 > 1 (มากไป) -> ลดค่าโดยขยับ R ถอยหลัง (R--)
```

**Step 3:** ขยับ `Right` มาชน `Left` (Index 1) -> Loop จบ (เพราะเงื่อนไขคือ L < R)
* หมดคู่สำหรับ i=0 แล้ว
* ขยับ i ไปตัวถัดไป

**Step 4:** ล็อก i ที่ Index 1 (ค่า 1)
* ตั้ง `Left = 2` (ค่า 5), `Right = 3` (ค่า 6)

```
[ -2 ,  1 ,  5 ,  6 ]
        ^    ^    ^
        i    L    R

Sum = 1 + 5 + 6 = 12
Target = 1
Result: 12 > 1 (มากไป) -> ขยับ R--
```

* R ชน L -> จบ Loop
* ไม่มี i ตัวถัดไปให้ขยับแล้ว (เพราะต้องเหลือที่ให้ 2 ตัว)
  **Output:** NO

### Output

```
NO
NO
YES
NO
NO
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(N^2)`
  * Big-Θ: `Θ(N^2)`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N,M;
    cin >> N >> M;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int j = 0 ; j < M ; j++) {
        long long num;
        cin >> num;
        bool found = false;

        for (int i = 0 ; i < N - 2; i++) {
            int left = i + 1;
            int right = N - 1;

            while (left < right) {
                long long current_sum = A[i] + A[left] + A[right];

                if (current_sum == num) {
                    found = true;
                    break;
                } else if (current_sum < num) {
                    left++;
                } else {
                    right--;
                }
            }
            if (found) break;
        }
        if (found) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
```