# ABC Permutation

## 1. วิเคราะห์โจทย์

โจทย์นี้เป็นโจทย์แนว **Brute Force + Recursion (Backtracking)**

โจทย์กำหนดให้:

* สร้างสายอักขระความยาว **N**
* ใช้ตัวอักษร

  * `A` ได้ไม่เกิน **i ตัว**
  * `B` ได้ไม่เกิน **j ตัว**
  * `C` ได้ไม่เกิน **k ตัว**
* ต้องแสดง **การเรียงสับเปลี่ยนทั้งหมด (Permutation)** ที่เป็นไปได้
* แสดงผลลัพธ์ **เรียงตามลำดับพจนานุกรม** โดยกำหนดว่า `A < B < C`

เงื่อนไขสำคัญ:

* ค่า `i + j + k` **ไม่จำเป็นต้องเท่ากับ N**
* ถ้าไม่สามารถสร้างสตริงความยาว N ได้ จะไม่มีผลลัพธ์
* กำหนด `1 ≤ N ≤ 12` ทำให้สามารถใช้ Brute Force ได้

---

## 2. แนวคิดหลัก

เนื่องจากจำนวนตัวอักษรมีน้อย และ N ไม่เกิน 12
เราสามารถใช้ Recursive Backtracking เพื่อสร้างทุกสตริงที่เป็นไปได้

แนวคิดคือ:

* เริ่มจากสตริงว่าง `""`
* ในแต่ละตำแหน่ง เลือกใส่ตัวอักษร `A`, `B`, หรือ `C`
* ใส่ได้ก็ต่อเมื่อจำนวนตัวอักษรนั้นยังเหลืออยู่
* เมื่อใส่แล้ว ให้ลดจำนวนตัวอักษรที่เหลือ และลดความยาวที่ต้องสร้างลง 1

**Base Case**
```cpp
if (n == 0) {
    all_word.push_back(word);
    return;
}
```

* เมื่อสร้างครบความยาว `N` → เก็บหรือแสดงผลลัพธ์

**Recursive Case**
```cpp
if(a > 0) recursive(word + "A", n - 1, a - 1, b, c);
if(b > 0) recursive(word + "B", n - 1, a, b - 1, c);
if(c > 0) recursive(word + "C", n - 1, a, b, c - 1);
```

**เหตุผลที่เรียงตามพจนานุกรมได้เอง**

* เรียก recursion ตามลำดับ `A → B → C`
* ทำให้ผลลัพธ์ออกมาตามลำดับพจนานุกรมโดยไม่ต้อง sort เพิ่ม

---

## 3. ตัวอย่าง Test Case พร้อม Recursion Tree

### Input

```
2 1 1 3
```

หมายความว่า:

* ความยาวสตริง = 2
* ใช้ `A` ได้ 1 ตัว
* ใช้ `B` ได้ 1 ตัว
* ใช้ `C` ได้ 3 ตัว

### Recursion Tree

```
""
├── A
│   ├── AB
│   └── AC
├── B
│   ├── BA
│   └── BC
└── C
    ├── CA
    ├── CB
    └── CC
```

### Output

```
7
AB
AC
BA
BC
CA
CB
CC
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(3^N)`
  * Big-Θ: `Θ(3^N)` (ในกรณีที่ทุกตัวอักษรยังใช้ได้)

### เฉลยโค้ด

```cpp
 #include <iostream>
 #include <vector>

 using namespace std;

 vector<string> all_word;

 void recursive(string word , int n , int a , int b , int c) {
     if (n == 0) {
         all_word.push_back(word);
         return;
     }
     else {
         if(a > 0) recursive(word + "A", n - 1 , a - 1 , b , c);
         if(b > 0) recursive(word + "B", n - 1 , a , b - 1 , c);
         if(c > 0) recursive(word + "C", n - 1 , a , b , c - 1);
     }
 }

 int main() {
     ios_base::sync_with_stdio(false); cin.tie(0);
     int N,i,j,k;
     cin >> N >> i >> j >> k;
     recursive("",N,i,j,k);
     cout << all_word.size() << "\n";
     for (auto x : all_word) {
         cout << x << "\n";
     } 
}
```