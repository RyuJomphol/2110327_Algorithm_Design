# Matrix Modulo

## 1. วิเคราะห์โจทย์

* เราต้องการหาค่าของเมทริกซ์ $A$ ยกกำลัง $n$ ($A^n$)
* แล้วนำสมาชิกแต่ละตัวไป mod ด้วย $k$
**ข้อจำกัด (Constraints):** ค่า $n$ สูงถึง $2^{30}$ (ประมาณ 1 พันล้าน) หากเราใช้ลูป `for` คูณกัน $n$ ครั้ง (Linear Time $O(n)$) จะใช้เวลานานเกินกำหนด (Time Limit 1 วินาที รับได้ประมาณ $10^8$ คำสั่ง)

**วิธีการแก้ปัญหา:**
* เราต้องใช้วิธี **Matrix Exponentiation** (หรือ Binary Exponentiation สำหรับเมทริกซ์)
* หลักการคือการเปลี่ยนจากการคูณทีละ 1 ครั้ง เป็นการ "ยกกำลังสอง" ไปเรื่อยๆ (Squaring)
* **ตัวอย่าง:** หากต้องการคำนวณ $A^8$
  * แบบช้า: $A \times A \times A \times ...$ (7 ครั้ง)
  * แบบเร็ว: $A^2 = A \times A$ , $A^4 = A^2 \times A^2$ , $A^8 = A^4 \times A^4$
  * **ใช้การคูณเพียง 3 ครั้งเท่านั้น**
* ความซับซ้อนของเวลาจะลดลงจาก $O(n)$ เหลือเพียง $O(\log n)$ ซึ่งเร็วมากและผ่านโจทย์ข้อนี้ได้สบาย ๆ

---

## 2. แนวคิดหลัก

**ส่วนโครงสร้างข้อมูลและการคูณเมทริกซ์** (`struct Matrix` & `multiply`)
```cpp
struct Matrix {
    long long mat[2][2]; // เก็บข้อมูลเมทริกซ์ 2x2 ใช้ long long กันค่าล้นก่อน mod
};

Matrix multiply(Matrix A, Matrix B, int k) {
    Matrix C;
    for(int i = 0 ; i < 2 ; i++) {
        for(int j = 0 ; j < 2 ; j++) {
            C.mat[i][j] = 0;
            for (int l = 0; l < 2; l++) {
                // สูตรคูณเมทริกซ์: แถวของ A * หลักของ B
                // ใส่ % k ในทุกขั้นตอนการบวกเพื่อป้องกันค่าเกิน
                C.mat[i][j] = (C.mat[i][j] + (A.mat[i][l] * B.mat[l][j])) % k;
            }
        }
    }
    return C;
};
```

* `struct Matrix` : สร้าง type ใหม่เพื่อเก็บตาราง 2x2 ทำให้ส่งค่าผ่านฟังก์ชันง่ายขึ้น
* `multiply` : ฟังก์ชันคูณเมทริกซ์มาตรฐาน 2x2 โดยมีการ Modulo $k$ ทุกครั้งที่มีการคำนวณเพื่อรักษาค่าให้อยู่ในช่วงที่กำหนด

---

**ส่วนการยกกำลังแบบเร็ว** `(power)`:
```cpp
Matrix power(Matrix A, int n, int k) {
    Matrix res;
    // สร้าง Identity Matrix (เมทริกซ์เอกลักษณ์) เริ่มต้น
    // [1 0]
    // [0 1]
    res.mat[0][0] = 1; res.mat[0][1] = 0;
    res.mat[1][0] = 0; res.mat[1][1] = 1;

    // Mod ค่า A ก่อนเริ่มเพื่อความปลอดภัย
    A.mat[0][0] %= k; A.mat[0][1] %= k;
    A.mat[1][0] %= k; A.mat[1][1] %= k;

    while (n > 0) {
        // ถ้ายกกำลังเป็นเลขคี่ ให้คูณผลลัพธ์ด้วย A ปัจจุบันหนึ่งครั้ง
        if (n % 2 == 1) {
            res = multiply(res, A, k);
        }
        // เอามารอยกกำลังสองเสมอ (A^1 -> A^2 -> A^4 -> A^8...)
        A = multiply(A, A, k);
        n /= 2; // หารกำลังลงครึ่งหนึ่ง
    }
    return res;
};
```

* นี่คือหัวใจของอัลกอริทึม Binary Exponentiation
* เราตั้งค่า `res` เป็นเมทริกซ์เอกลักษณ์ (เหมือนเลข 1 ในการคูณ)
* ในแต่ละรอบของ Loop เราจะทำการยกกำลังสองค่า $A$ เสมอ และถ้ารอบไหนเลขชี้กำลัง ($n$) เป็นเลขคี่ เราจะ "เก็บ" ค่า $A$ ณ ตอนนั้นมาคูณเข้ากับคำตอบ (`res`)

---

**ส่วน** `main`:

```cpp
int main () {
    // รับค่า n และ k
    // รับค่าเมทริกซ์เริ่มต้น
    // เรียกฟังก์ชัน power
    // แสดงผลลัพธ์
}
```

---

## 3. ตัวอย่าง Test Case

### Input

```
2 10
1 2 3 4
```

* $n = 2$ (เลขยกกำลัง)
* $k = 10$ (ตัวหาร Modulo)
* $A = \begin{bmatrix} 1 & 2 \\\ 3 & 4 \end{bmatrix}$
**เป้าหมาย:** คำนวณ $A^2 \pmod{10}$

**ขั้นตอนการทำงาน (Step-by-Step Trace)**
เริ่มฟังก์ชัน `power(A, n=2, k=10)` `res` เริ่มต้นคือ Identity Matrix
$\begin{bmatrix}1 & 0 \\\ 0 & 1\end{bmatrix}$

**Loop รอบที่ 1:**
* ตรวจสอบ `n = 2` (เลขคู่):
  * เงื่อนไข `n % 2 == 1` เป็นเท็จ -> **ไม่ทำอะไรกับ** `res`
* คำนวณ `A = multiply(A, A, 10)` (ยกกำลังสองตัวฐาน):
  * คำนวณ $A \times A$ : $$\begin{bmatrix} 1 & 2 \\\ 3 & 4 \end{bmatrix} \times \begin{bmatrix} 1 & 2 \\\ 3 & 4 \end{bmatrix}$$
    * ตำแหน่ง (0,0): $(1\times1 + 2\times3) = 7 \pmod{10} \rightarrow 7$
    * ตำแหน่ง (0,1): $(1\times2 + 2\times4) = 10 \pmod{10} \rightarrow 0$
    * ตำแหน่ง (1,0): $(3\times1 + 4\times3) = 15 \pmod{10} \rightarrow 5$
    * ตำแหน่ง (1,1): $(3\times2 + 4\times4) = 22 \pmod{10} \rightarrow 2$
  * ตอนนี้ $A$ กลายเป็น $\begin{bmatrix} 7 & 0 \\\ 5 & 2 \end{bmatrix}$
* ลดค่า `n`: `n = n / 2` $\rightarrow$ `n = 1`

**Loop รอบที่ 2:**
* ตรวจสอบ `n = 1` (เลขคี่):
  * เงื่อนไข `n % 2 == 1` เป็นจริง -> **คูณ** `res` **ด้วย** `A` **ปัจจุบัน**
  * `res` = $\begin{bmatrix} 1 & 0 \\\ 0 & 1 \end{bmatrix} \times \begin{bmatrix} 7 & 0 \\\ 5 & 2 \end{bmatrix}$
  * ผลลัพธ์ `res` กลายเป็น $\begin{bmatrix} 7 & 0 \\\ 5 & 2 \end{bmatrix}$
* คำนวณ `A = multiply(A, A, 10):`
  * $A$ ถูกยกกำลังต่อไป (กลายเป็น $A^4$) แต่รอบหน้าไม่ได้ใช้แล้ว
* ลดค่า `n`: `n = 1 / 2` $\rightarrow$ `n = 0`
**จบ Loop:** `n` เป็น 0 ออกจากลูป คืนค่า `res`

```
Matrix A             Matrix A
    +---+---+            +---+---+
    | 1 | 2 |            | 1 | 2 |
    +---+---+     X      +---+---+
    | 3 | 4 |            | 3 | 4 |
    +---+---+            +---+---+

Calculation Modulo 10:

Row 0, Col 0: (1*1) + (2*3) = 1 + 6  = 7  -> 7 mod 10 = 7
Row 0, Col 1: (1*2) + (2*4) = 2 + 8  = 10 -> 10 mod 10 = 0
Row 1, Col 0: (3*1) + (4*3) = 3 + 12 = 15 -> 15 mod 10 = 5
Row 1, Col 1: (3*2) + (4*4) = 6 + 16 = 22 -> 22 mod 10 = 2

      Result (A^2 mod 10)
    +---+---+
    | 7 | 0 |
    +---+---+
    | 5 | 2 |
    +---+---+
```

### Output

```
7 0 5 2
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: $O(M^3 \log n)$

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>

using namespace std;

struct Matrix {
    long long mat[2][2];
};

Matrix multiply(Matrix A, Matrix B, int k) {
    Matrix C;
    for(int i = 0 ; i < 2 ; i++) { 
        for(int j = 0 ; j < 2 ; j++) {
            C.mat[i][j] = 0;
            for (int l = 0; l < 2; l++) {
                C.mat[i][j] = (C.mat[i][j] + (A.mat[i][l] * B.mat[l][j])) % k;
            }
        }  
    }
    return C;
};

Matrix power(Matrix A, int n, int k) {
    Matrix res;
    res.mat[0][0] = 1; res.mat[0][1] = 0;
    res.mat[1][0] = 0; res.mat[1][1] = 1;

    A.mat[0][0] %= k; A.mat[0][1] %= k;
    A.mat[1][0] %= k; A.mat[1][1] %= k;

    while (n > 0) {
        if (n % 2 == 1) {
            res = multiply(res, A, k);
        }
        A = multiply(A, A, k);
        n /= 2;
    }
    return res;
};

int main () {
    int n,k;
    cin >> n >> k;

    Matrix A;
    cin >> A.mat[0][0] >> A.mat[0][1] >> A.mat[1][0] >> A.mat[1][1];

    Matrix result = power(A,n,k);
    cout << result.mat[0][0] << " " << result.mat[0][1] << " " << result.mat[1][0] << " " << result.mat[1][1];
}
```
