# Consecutive Ones

## 1. วิเคราะห์โจทย์

เป็นโจทย์แนว **Backtracking / Recursion (Brute Force with pruning เล็กน้อย)**  
เนื่องจากต้องการสร้างเลขฐานสองทุกความเป็นไปได้ขนาด `n` บิต แล้วคัดกรองเฉพาะกรณีที่มีเลข `1` **ติดกันอย่างน้อย `k` บิต**

**โจทย์กำหนดให้**
- รับจำนวนเต็ม `n` และ `k` โดย `0 ≤ k ≤ n ≤ 20`
- แสดงเลขฐานสองความยาว `n` บิต
- เงื่อนไข: ต้องมีเลข `1` ที่ติดกันอย่างน้อย `k` ตัว
- แสดงผลเรียงจากค่าน้อยไปมาก (binary order)

---

## 2. แนวคิดหลัก

ใช้ **Recursion** เพื่อสร้างสตริงเลขฐานสองทีละตำแหน่ง  
โดยในแต่ละขั้นจะเลือกได้ 2 ทาง:
- เติม `"0"`
- เติม `"1"`

พร้อมกับเก็บข้อมูลสำคัญระหว่างทาง:
- `one` → จำนวนเลข `1` ที่ติดกันล่าสุด
- `check` → เคยมีเลข `1` ติดกันถึง `k` แล้วหรือยัง

เมื่อสร้างครบ `n` บิต (`n == 0`)  
ถ้า `check == true` แสดงว่าเลขนี้ผ่านเงื่อนไข → นำไปเก็บในผลลัพธ์

**Check Case**
```cpp
if (one >= k) {
    check = true;
}
```
* ถ้าพบว่าเลข `1` ติดกันถึง `k` แล้ว
  → ตั้ง `check = true` และค่านี้จะถูกส่งต่อไปยัง recursive ถัด ๆ ไป

**Base Case**
```cpp
if (n == 0) {
    if (check) all_nums.push_back(num);
    return;
}
```

**Recursive Case**
```cpp
recursive(num + "0" , n - 1 , k , 0 , check);
recursive(num + "1" , n - 1 , k , one + 1 , check);
```
* เติม `0` → เลข `1` ที่ติดกันถูกตัด → `one = 0` 
* เติม `1` → เพิ่มจำนวนเลข `1` ที่ติดกัน
---

## 3. ตัวอย่าง Test Case พร้อม Recursion Tree

### Input

```
3 2
```

### Recursion Tree

```
                         ""
              /----------------------\
            "0"                      "1"
        (one=0)                  (one=1)
         /      \                 /      \
      "00"     "01"            "10"     "11"
     (0)      (1)             (0)      (2 ✔)
     /  \     /  \           /  \      /   \
  "000" "001" "010" "011✔" "100" "101" "110✔" "111✔"
```
✔ = มีเลข `1` ติดกันอย่างน้อย 2 ตัว

เลขที่ผ่านเงื่อนไข:

* `011`
* `110`
* `111`

และเรียงจากน้อยไปมากตาม Binary Order

### Output

```
011
110
111
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(2^n)`
  * Big-Θ: `Θ(2^N)`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>

using namespace std;

vector<string> all_nums;

void recursive(string num , int n , int k , int one , bool check) {
    if (one >= k) {
        check = true;
    }

    if (n == 0) {
        if (check) all_nums.push_back(num);
        return;
    }

    recursive(num + "0" , n - 1 , k , 0 , check);
    recursive(num + "1" , n - 1 , k , one + 1 , check);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n , k;
    cin >> n >> k;
    recursive("" , n , k ,  0 , false);
    for (auto num : all_nums) {
        cout << num << "\n";
    }
}
```