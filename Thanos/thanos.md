# Thanos

## 1. วิเคราะห์โจทย์

**แนวคิดหลัก:** โจทย์ข้อนี้เป็นปัญหา **Minimization** (หาค่าตํ่าสุด) โดยใช้โครงสร้างแบบ **Divide and Conquer** (แบ่งแยกและเอาชนะ) คล้ายกับ Merge Sort

**ความท้าทาย (Constraints Analysis):**
* **ขนาดพื้นที่ ($n$):** โจทย์ให้ $n = 2^p$ โดย $p$ สูงสุด 30 นั่นคือ $n \approx 10^9$ (พันล้านช่อง)
    * ❌ **สร้าง Array `int base[1000000000]` ไม่ได้** เพราะ Memory Limit 512MB จะระเบิดแน่นอน
    * ✅ **ต้องใช้ข้อมูลพิกัด (Positions) ของ Avengers แทน** และใช้การค้นหาช่วงเพื่อคำนวณจำนวนคน

**วิธีการแก้ปัญหา:**
เราต้องเปรียบเทียบค่าใช้จ่าย 2 ทางเลือกเสมอสำหรับช่วง `[L, R]`:
1. **ดีดนิ้วทำลายเลย (Destroy Now):**
    * ถ้าไม่มีคน: จ่าย $A$
    * ถ้ามีคน ($m$ คน): จ่าย $B \times m \times (R - L + 1)$
2. **แบ่งครึ่งแล้วค่อยทำลาย (Split & Destroy):**
    * จ่ายค่าทำลายฝั่งซ้าย + ค่าทำลายฝั่งขวา
    * สูตร: `solve(L, mid) + solve(mid+1, R)`

**เงื่อนไขหยุด (Base Case / Pruning):**
* ถ้าเหลือช่องเดียว ($L=R$): ต้องทำลายเลย (แบ่งไม่ได้แล้ว)
* ถ้าช่วงนั้น **ไม่มี Avengers เลย ($m=0$):** ให้ทำลายเลยด้วยราคา $A$ (ไม่ต้องแบ่งต่อ เพราะ $A$ ย่อมถูกกว่าหรือเท่ากับ $A+A$ เสมอ)

---

## 2. แนวคิดหลัก Implementation

**ส่วนที่ 1: การนับจำนวน Avengers ในช่วง (`count_avengers`)**
เนื่องจากเราสร้าง Array ไม่ได้ เราจึงเก็บตำแหน่ง Avengers ใน `vector<long long> pos` และทำการ **Sort** ไว้ก่อน เพื่อใช้ **Binary Search**

```cpp
vector<ll> pos; // เก็บตำแหน่งของ Avengers (เรียงลำดับแล้ว)

// ฟังก์ชันหาจำนวน Avengers ในช่วง [L, R]
ll count_avengers(ll L, ll R) {
    // lower_bound: หาตัวแรกที่มีค่า >= L
    auto it1 = lower_bound(pos.begin(), pos.end(), L);
    
    // upper_bound: หาตัวแรกที่มีค่า > R (ตัวที่เกินขอบขวาไปแล้ว)
    auto it2 = upper_bound(pos.begin(), pos.end(), R);
    
    // ระยะห่างระหว่าง 2 iterators คือจำนวนตัวเลขในช่วงนั้น
    return distance(it1, it2);
}
```

**ส่วนที่ 2: ฟังก์ชันเรียกซ้ำ** (`destroy_base`) หัวใจหลักของการคำนวณ เปรียบเทียบราคาระหว่าง "ทำลายทันที" กับ "แบ่งครึ่ง"

```cpp
ll destroy_base(ll L, ll R) {
    // 1. หาจำนวนคนในพื้นที่นี้ก่อน
    ll m = count_avengers(L, R);
    
    // 2. คำนวณราคาถ้า "ดีดนิ้วทำลายทันที"
    ll cost_destroy;
    if (m == 0) {
        cost_destroy = A; // ไม่มีคน จ่ายราคาเหมา A
    } else {
        cost_destroy = B * m * (R - L + 1); // มีคน จ่ายตามสูตร B * คน * ความยาว
    }

    // 3. Base Case & Pruning (จุดหยุด)
    // - ถ้าเหลือช่องเดียว (L==R) ต้องจ่ายราคานี้เลย แบ่งไม่ได้
    // - ถ้าไม่มีคนเลย (m==0) จ่าย A คุ้มสุดแล้ว ไม่ต้องแบ่งให้เสียเวลา (Optimization)
    if (L == R || m == 0) {
        return cost_destroy;
    }

    // 4. Recursive Step: ลองแบ่งครึ่ง
    ll mid = L + (R - L) / 2;
    ll cost_split = destroy_base(L, mid) + destroy_base(mid + 1, R);

    // 5. คืนค่าที่ถูกที่สุด ระหว่าง "ทำลายเลย" vs "แบ่งครึ่ง"
    return min(cost_destroy, cost_split);
}
```

**ส่วนที่ 3: Main Setup** จัดการเรื่อง $2^p$ โดยใช้ Bitwise Operation

```cpp
cin >> P >> K >> A >> B;
    // ... รับค่า pos และ sort ...

    // คำนวณขนาดกระดาน 2^P
    // 1LL คือการบอกว่าเป็น Long Long แล้ว Shift bit ไปทางซ้าย P ครั้ง
    ll n = 1LL << P; 

    cout << destroy_base(1, n) << endl;
```

---

## 3. ตัวอย่าง Test Case

### Input

```
2 2 1 2
1 3
```

**การตั้งค่าเบื้องต้น (Setup)**
* **P = 2:** ความยาวฐานทัพ $n = 2^2 = 4$ ช่อง (ช่วง 1 ถึง 4)
* **K = 2:** มี Avengers 2 คน
* **A = 1:** ค่าพลังทำลายพื้นที่ว่าง
* **B = 2:** ค่าสัมประสิทธิ์พลังทำลายพื้นที่ที่มีคน
* **ตำแหน่ง:** `1` และ `3`

```
ตำแหน่ง:  [ 1 ] [ 2 ] [ 3 ] [ 4 ]
ข้อมูล:   [ Av] [   ] [ Av] [   ]  <-- Av = มี Avenger
```

**Step 1: พิจารณาช่วงเต็ม [1, 4]**
* **สถานะ:** มี Avengers 2 คน (ที่เลข 1, 3), ความยาว 4
* **ทางเลือกที่ 1 (ทุบเลย):** $Cost = B \times m \times l = 2 \times 2 \times 4 = \mathbf{16}$
* **ทางเลือกที่ 2 (แบ่งครึ่ง):** แบ่งเป็น `[1,2]` กับ `[3,4]` (รอดูล่าง)

```
      [Range 1-4]
      Avengers: 2
     Length: 4
    /           \
[Option 1]    [Option 2]
ทุบเลย = 16    แบ่งครึ่ง (รอผลรวมจากลูก)
                 |
        +--------+--------+
        |                 |
   [Range 1-2]       [Range 3-4]
```

**Step 2: พิจารณาปีกซ้าย [1, 2]**
* **สถานะ:** มี Avengers 1 คน (ที่เลข 1), ความยาว 2
* **ทางเลือกที่ 1 (ทุบเลย):** $Cost = 2 \times 1 \times 2 = \mathbf{4}$
* **ทางเลือกที่ 2 (แบ่งครึ่ง):** แบ่งเป็น `[1,1]` กับ `[2,2]`
  * **ย่อย 1 [1,1]:** มีคน 1 คน, ยาว 1 (Base Case)
    * Cost = $2 \times 1 \times 1 = \mathbf{2}$
  * **ย่อย 2 [2,2]: ไม่มีคน** (Base Case)
    * Cost = $A = \mathbf{1}$
  * **รวมค่าแบ่งครึ่ง:** $2 + 1 = \mathbf{3}$
* **ตัดสินใจปีกซ้าย:** เปรียบเทียบ "ทุบเลย (4)" vs "แบ่ง (3)" $\rightarrow$ **เลือก 3**

```
      [Range 1-2]
      Avengers: 1
       Length: 2
      /         \
  ทุบเลย=4     แบ่งครึ่ง
              /     \
         [1,1]      [2,2]
        (มีคน)      (ว่าง)
        Cost=2      Cost=1
           \       /
            รวม = 3
    
    Result: เลือก 3 (เพราะ 3 < 4)
```

**Step 3: พิจารณาปีกขวา [3, 4]**
* **สถานะ:** มี Avengers 1 คน (ที่เลข 3), ความยาว 2
* **ทางเลือกที่ 1 (ทุบเลย):** $Cost = 2 \times 1 \times 2 = \mathbf{4}$
* **ทางเลือกที่ 2 (แบ่งครึ่ง):** แบ่งเป็น `[3,3]` กับ `[4,4]`
  * **ย่อย 1 [3,3]:** มีคน 1 คน, ยาว 1
    * Cost = $2 \times 1 \times 1 = \mathbf{2}$
  * **ย่อย 2 [4,4]: ไม่มีคน**
    * Cost = $A = \mathbf{1}$
  * **รวมค่าแบ่งครึ่ง:** $2 + 1 = \mathbf{3}$
* **ตัดสินใจปีกขวา:** เปรียบเทียบ "ทุบเลย (4)" vs "แบ่ง (3)" $\rightarrow$ **เลือก 3**

```
      [Range 3-4]
      Avengers: 1
       Length: 2
      /         \
  ทุบเลย=4     แบ่งครึ่ง
              /     \
         [3,3]      [4,4]
        (มีคน)      (ว่าง)
        Cost=2      Cost=1
           \       /
            รวม = 3
    
    Result: เลือก 3 (เพราะ 3 < 4)
```

* **Step 4: สรุปผลที่ Root Node [1, 4]**
  * **ทางเลือกที่ 1 (ทุบเลย):** ราคา 16
  * **ทางเลือกที่ 2 (แบ่งครึ่ง):** ได้ผลจากปีกซ้าย (3) + ผลจากปีกขวา (3) = **6**

**การตัดสินใจครั้งสุดท้าย:** เปรียบเทียบ 16 กับ 6
$\rightarrow$ **เลือก 6**

```
LEVEL 1:           [Range 1-4]
                   Av:2, Len:4
             ทุบ=16  VS  แบ่ง=?
                         |
           +-------------+-------------+
           |                           |
LEVEL 2: [Range 1-2]                 [Range 3-4]
         Av:1, Len:2                 Av:1, Len:2
      ทุบ=4 VS แบ่ง=?             ทุบ=4 VS แบ่ง=?
               |                           |
        +------+------+             +------+------+
        |             |             |             |
LV 3: [1,1]         [2,2]         [3,3]         [4,4]
      (Av=1)        (Av=0)        (Av=1)        (Av=0)
      Cost:2        Cost:1        Cost:2        Cost:1
        |             |             |             |
        +------+------+             +------+------+
               |                           |
Return:    Sum = 3                     Sum = 3
(เลือก 3 เพราะ < 4)            (เลือก 3 เพราะ < 4)
               |                           |
               +-------------+-------------+
                             |
Final Return:             Sum = 6
                  (เลือก 6 เพราะ < 16)
                             |
                        Output: 6
```

### Output

```
6
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O:  $O(k \cdot \log n)$

### เฉลยโค้ด

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll P, K, A, B;
vector<ll> pos;

ll count_avengers(ll L, ll R) {
    auto it1 = lower_bound(pos.begin(), pos.end(), L);
    auto it2 = upper_bound(pos.begin(), pos.end(), R);
    return distance(it1, it2);
}

ll destroy_base(ll L, ll R) {
    ll m = count_avengers(L, R);
    ll cost_destroy;

    if (m == 0) {
        cost_destroy = A;
    }
    else {
        cost_destroy = B * m * (R - L + 1);
    }

    if (L == R || m == 0) {
        return cost_destroy;
    }

    ll mid = L + (R - L) / 2;

    return min(cost_destroy, destroy_base(L, mid) + destroy_base(mid + 1, R));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> P >> K >> A >> B;

    pos.resize(K);
    for (int i = 0; i < K; i++) {
        cin >> pos[i];
    }
    sort(pos.begin(), pos.end());

    ll n = 1LL << P;
    cout << destroy_base(1, n) << endl;

    return 0;
}
```