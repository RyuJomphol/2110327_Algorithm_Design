# Permutation with Constraint

## 1. วิเคราะห์โจทย์

โจทย์ข้อนี้เป็นปัญหาทาง **Combinatorics** (คอมบินาทอริก) ที่ต้องการหา **Permutation** (การเรียงสับเปลี่ยน) ของตัวเลข 0 ถึง n-1 ทั้งหมดที่เป็นไปได้ แต่มีความซับซ้อนเพิ่มขึ้นด้วย **Precedence Constraints** (เงื่อนไขลำดับก่อนหลัง) หรือที่เรียกว่า Topological Constraints

**วิธีการที่ใช้แก้ปัญหา: Backtracking (การย้อนรอย)**

เราไม่สามารถใช้ลูปซ้อนกัน n ชั้นได้ เพราะค่า n ไม่คงที่ ดังนั้น **Recursion** (การเรียกซ้ำ) จึงเป็นเครื่องมือที่เหมาะสมที่สุด โดยมีหลักการดังนี้:
* **Lexicographical Order (เรียงตามพจนานุกรม):** เพื่อให้ผลลัพธ์เรียงจากน้อยไปมากตามที่โจทย์ต้องการ ในแต่ละขั้นตอนของการเติมตัวเลข (Step) เราจะวนลูปเลือกตัวเลข (`i`) ตั้งแต่ `0` ถึง `n-1` เสมอ
* **State Space Search:** เราจะสร้างอาร์เรย์ `used[]` เพื่อจำว่าตัวเลขไหนถูกใช้ไปแล้ว
* **Constraint Checking (เช็คเงื่อนไข):** จุดสำคัญที่สุดของโจทย์นี้คือ ก่อนจะหยิบเลข `i` มาใส่ในตำแหน่งปัจจุบัน เราต้องเช็ค 2 เงื่อนไข:
  * เลข `i` ต้องยังไม่ถูกใช้ (`used[i] == false`)
  * เงื่อนไขพิเศษ: ถ้าเลข `i` มีตัวที่ต้องมาก่อน (สมมติว่าเป็น `a` ซึ่งเก็บใน `before[i]`) ตัวเลข `a` นั้นจะต้องถูกหยิบมาใช้ก่อนหน้านี้แล้ว (`used[a] == true`) หรือถ้า `i` ไม่มีเงื่อนไขต้องตามหลังใคร ก็ถือว่าผ่าน

ด้วยโครงสร้างข้อมูลที่โจทย์รับประกันว่า "ค่า b แต่ละค่าจะไม่ซ้ำกันเลย" (1 ตัว มีเงื่อนไขต้องตามหลังได้แค่ 1 ตัว หรือไม่มีเลย) เราจึงใช้อาร์เรย์ `before` เพียงตัวเดียวเพื่อเก็บเงื่อนไขนี้ได้ง่ายๆ `เช่น before[b] = a`

---

## 2. แนวคิดหลัก
มาดูการทำงานของโค้ดทีละส่วน

ส่วนประกาศตัวแปรและ Main Function  
 ```cpp
// ส่วน Global Variable เพื่อให้เรียกใช้ได้ทุกที่ใน Recursion
int n, m;
vector<int> all_permutation; // เก็บผลลัพธ์ที่กำลังสร้างในรอบนั้นๆ
vector<int> before;          // เก็บเงื่อนไข: before[x] = y แปลว่า y ต้องมาก่อน x
vector<bool> used;           // เช็คว่าเลขนี้ถูกหยิบไปหรือยัง

int main() {
    // ... (การรับค่า input) ...
    
    // ตั้งค่าเริ่มต้น (Initialization)
    before.resize(n, -1); // ให้ทุกช่องเป็น -1 (แปลว่าไม่มีตัวต้องมาก่อน)
    used.resize(n, false);
    all_permutation.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        before[b] = a; // บันทึกว่า ถ้าจะใช้ b ต้องมี a มาก่อนนะ
    }

    // เริ่มเรียกฟังก์ชัน Backtracking ที่ตำแหน่งแรก (index 0)
    permutation(n, all_permutation, 0, used);
}
```

**Base Case**
```cpp
if (step == n) {
        for (auto x : all_permutation) {
            cout << x << " ";
        }
        cout << endl;
    }
```
-  ถ้าเติมตัวเลขครบ n ตัวแล้ว (step == n) พิมพ์ผลลัพธ์ออกมา

**Recursive Case**
```cpp
for (int i = 0; i < n; i++) {
            
            // เงื่อนไขหัวใจสำคัญ:
            // 1. used[i] == false : เลข i ต้องยังไม่เคยถูกใช้
            // 2. (before[i] == -1 || used[before[i]]) :
            //    - ถ้า before[i] เป็น -1 แสดงว่า i ลงได้เลยไม่ต้องรอใคร
            //    - หรือ ถ้ามีตัวต้องมาก่อน (parent) ตัว parent นั้นต้องถูกใช้ไปแล้ว (used[true])
            
            if (used[i] == false && (before[i] == -1 || used[before[i]])) {
                
                // Do: เลือก i
                used[i] = true;
                all_permutation[step] = i;
                
                // Recurse: ไปทำตำแหน่งถัดไป (step + 1)
                permutation(n, all_permutation, step + 1, used);
                
                // Undo (Backtrack): ถอยกลับเพื่อลองเลขอื่นในรอบถัดไป
                used[i] = false;
            }
        }
```
เงื่อนไขตัดกิ่ง (Pruning)
- ถ้าจำนวน `1` เกิน `A` → หยุด
- ถ้าจำนวนตำแหน่งที่เหลือไม่พอให้ใส่ `1` ครบ `A` → หยุด
---

## 3. ตัวอย่าง Test Case พร้อม Recursion Tree

### Input

```
3 1
1 2
```
ข้อมูลเบื้องต้น
* **Input:** `3 1` (มีเลข 0, 1, 2 และมี 1 เงื่อนไข)
* **Constraint:** `1 2` (เลข 1 ต้องมาก่อน 2)
* **Translation:** ถ้าจะหยิบเลข `2` มาใส่... `used[1]` ต้องเป็น `true` แล้วเท่านั้น

### Recursion Tree

```
START (Step 0)
│
├── เลือก 0 ──> [0] (Step 1)
│    │
│    ├── เลือก 1 ──> [0, 1] (Step 2)
│    │    │
│    │    └── เลือก 2 ──> [0, 1, 2] (PRINT)
│    │         (เงื่อนไขผ่าน: เพราะ 1 ถูกใช้ไปแล้วใน step ก่อนหน้า)
│    │
│    └── เลือก 2 ──> (หยุด!)
│         (เงื่อนไขไม่ผ่าน: ต้องการใช้ 2 แต่ 1 ยังไม่ได้ถูกใช้)
│
├── เลือก 1 ──> [1] (Step 1)
│    │
│    ├── เลือก 0 ──> [1, 0] (Step 2)
│    │    │
│    │    └── เลือก 2 ──> [1, 0, 2] (PRINT)
│    │         (เงื่อนไขผ่าน: เพราะ 1 ถูกใช้ไปแล้วตั้งแต่ step แรก)
│    │
│    └── เลือก 2 ──> [1, 2] (Step 2)
│         │    (เงื่อนไขผ่าน: เพราะ 1 ถูกใช้ไปแล้ว)
│         │
│         └── เลือก 0 ──> [1, 2, 0] (PRINT)
│
└── เลือก 2 ──> (หยุด!)
     (เงื่อนไขไม่ผ่านตั้งแต่เริ่ม: จะใช้ 2 แต่ 1 ยังไม่เคยถูกใช้เลย)

```
**คำอธิบายจุดตัด (Pruning Steps) ที่สำคัญ**

**1. กิ่งขวาสุด (เลือก 2 ตั้งแต่แรก):**

* เราพยายาม `used[2] = true`
* โค้ดเช็ค: `if (used[2] == false && (before[2] == -1 || used[1]))`
* ค่าจริง: `used[2]` เป็น false (ผ่าน) แต่ `used[1]` ก็เป็น false (ไม่ผ่านเงื่อนไข `used[before[i]]`)
* **ผลลัพธ์:** ลูป `continue` ข้ามไปเลย ไม่มีการเรียก `permutation(...)` ต่อ

**2. กิ่งซ้าย (เลือก 0 แล้วพยายามเลือก 2):**

* สถานะปัจจุบัน: `[0]` (ใช้ 0 ไปแล้ว)
* เราพยายามเลือก 2 ต่อ
* โค้ดเช็ค: `used[1]` เป็น true หรือยัง? -> ยัง
* **ผลลัพธ์:** ข้ามไป ทำให้ลำดับ `0 -> 2 -> ...` เกิดขึ้นไม่ได้

**3. กิ่งกลาง (เลือก 1):**

* สถานะปัจจุบัน: `[1]` (ใช้ 1 ไปแล้ว -> `used[1] = true`)
* หลังจากนี้ ไม่ว่าจะเลือก 2 ใน Step ไหนก็ได้หมด เพราะ `used[1]` เป็น true ตลอดสายการเรียกนี้แล้วครับ

### Output

```
0 1 2
1 0 2
1 2 0
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(n*n!)`
  * Big-Θ: กรณี m = 0: `Θ(n*n!)`

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>

using namespace std;

int n,m;
vector<int> all_permutation;
vector<int> before;
vector<bool> used;

void permutation(int n , vector<int> &all_permutation , int step , vector<bool> &used) {
    if (step == n) {
        for (auto x : all_permutation) {
            cout << x << " ";
        }
        cout << endl;
    }

    else {
        for(int i = 0 ; i < n ; i++) {
            if(used[i] == false && (before[i] == -1 || used[before[i]])) {
                used[i] = true;
                all_permutation[step] = i;
                permutation(n, all_permutation, step + 1, used);
                used[i] = false;
            }
            else {
                continue;
            }
        }
    }
}
 

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    //set up
    before.resize(n , -1); //before[i] = x means x must comes before i
    used.resize(n, false);
    all_permutation.resize(n);

    for (int i = 0 ; i < m ; i++) {
    int a,b;
    cin >> a >> b;
    before[b] = a; //a must comes before b
    }

    permutation(n , all_permutation , 0 , used);
}
```