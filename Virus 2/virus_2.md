# Virus 2

## 1. วิเคราะห์โจทย์

**แนวคิดหลัก:** โจทย์ข้อนี้เป็นปัญหาลักษณะ **โครงสร้างย่อยที่ซ้ำกัน (Recursive Structure)** โดยระบุชัดเจนว่า:
* ไวรัสขนาดใหญ่ ($2^k$) เกิดจากไวรัสขนาดเล็กกว่า ($2^{k-1}$) 2 ตัวมาต่อกัน
* มีเงื่อนไขการต่อกันคือ: จำนวนเลข `1` ของทั้งสองฝั่งต้องต่างกันไม่เกิน 1

**วิธีการที่ใช้: Divide and Conquer (แบ่งแยกและเอาชนะ)** เนื่องจากโจทย์นิยามปัญหาในรูปแบบ Recursive (ไวรัสใหญ่เกิดจากไวรัสเล็ก) วิธีที่เหมาะสมที่สุดคือการเขียนฟังก์ชัน **Recursion** โดยมีขั้นตอนดังนี้:
* **Divide:** แบ่งสายรหัสพันธุกรรมออกเป็น 2 ส่วนเท่าๆ กัน (ซ้ายและขวา)
* **Conquer:** เรียกฟังก์ชันตัวเองซ้ำ (Recursion) เพื่อตรวจสอบว่าส่วนซ้ายและส่วนขวาเป็นไวรัสที่ถูกต้องหรือไม่ และนับจำนวนเลข `1` กลับมา
* **Combine:** นำผลลัพธ์จากซ้ายและขวามาเช็คเงื่อนไข:
  * ซ้ายต้องเป็น DIVOC
  * ขวาต้องเป็น DIVOC
  * ผลต่างจำนวนเลข `1` ของซ้ายและขวา ต้อง $\le 1$

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
5 2
0 0 0 0
0 0 1 1
0 1 1 1
1 0 0 0
0 1 0 1
```

**Input:** $k=2$ (ความยาว $2^2 = 4$)

**Case A:** `0 0 1 1` -> **Output: no**
สาเหตุที่ตอบ no เพราะแม้ว่าคู่ย่อยจะดูโอเค แต่เมื่อรวมร่างกัน จำนวนเลข 1 ต่างกันเกินไป

```
[Check Whole: 0 0 1 1]
      /                      \
  [Left: 0 0]            [Right: 1 1]
  Count 1 = 0            Count 1 = 2
  Status = YES           Status = YES
      \                      /
       \                    /
        --------------------
        Compare Counts: |0 - 2| = 2
        Condition: 2 <= 1 ?  -> FALSE!
        
        Result: NO
```

**Case B:** `0 1 1 1` -> **Output: yes**
กรณีนี้ผ่านเงื่อนไขทุกชั้น

```
Step 1: แบ่งครึ่ง
       [Check Whole: 0 1 1 1]
             /        \
        [0 1]          [1 1]

Step 2: ย่อยลงไปอีก (Base Case)
      /     \         /     \
    [0]     [1]     [1]     [1]
   cnt=0   cnt=1   cnt=1   cnt=1
    OK      OK      OK      OK

Step 3: รวมร่างชั้นล่าง (Combine k=1)
    [0 1] -> |0-1|=1 (OK) -> Sum ones = 1
    [1 1] -> |1-1|=0 (OK) -> Sum ones = 2

Step 4: รวมร่างชั้นบนสุด (Combine k=2)
    Left Count = 1
    Right Count = 2
    Diff = |1 - 2| = 1  (<= 1 is TRUE)
    
    Result: YES
```

**Case C:** `1 0 0 0` -> **Output: yes**

```
       [1 0 0 0]
      /         \
   [1 0]       [0 0]
  (cnt=1)     (cnt=0)
     |           |
     -------------
     Diff = |1 - 0| = 1 (OK) -> YES
```

### Output

```
yes
no
yes
yes
yes
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: $O(N \cdot 2^k)$

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct virus {
    bool is_divoc;
    int count_one;
};

virus test_divoc(vector<int> gene , int start , int end , int k) {
    if (k == 0) {
        return {true, gene[start]};
    }

    int mid = (start + end) / 2;
    virus left = test_divoc(gene, start, mid, k - 1);
    virus right = test_divoc(gene, mid + 1, end, k - 1);

    bool current_is_divoc = left.is_divoc && right.is_divoc && (abs(left.count_one - right.count_one) <= 1);

    return {current_is_divoc, left.count_one + right.count_one};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n,k;
    cin >> n >> k;
    int virus_length = pow(2, k);

    for (int i = 0; i < n; i++) {
        vector<int> gene(virus_length);
        for (int j = 0; j < virus_length; j++) {
            cin >> gene[j];
        }

        virus final_result = test_divoc(gene , 0, virus_length - 1, k);

        if (final_result.is_divoc) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
        
    }
}
```