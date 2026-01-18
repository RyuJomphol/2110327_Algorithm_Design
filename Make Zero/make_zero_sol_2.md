# Make Zero Solution 2

## 1. วิเคราะห์โจทย์

**มุมมองแบบกราฟ:**
* ให้ตัวเลขแต่ละตัวตั้งแต่ 0 ถึง 16,777,215 เป็น **Node (จุด)** ในกราฟ
* การทำ Operation คือการเดินจากจุดหนึ่งไปยังอีกจุดหนึ่ง (**Directed Edge**):
  * เส้นทางที่ 1: ไปยัง node (x + 1) % MOD (น้ำหนัก 1)
  * เส้นทางที่ 2: ไปยัง node (x * 2) % MOD (น้ำหนัก 1)
* **เป้าหมาย:** หาเส้นทางที่สั้นที่สุดจากจุดเริ่มต้น x ไปยังจุด 0

**ทำไมถึงใช้ BFS?** 
* เนื่องจาก "น้ำหนัก" หรือ "ต้นทุน" ของการทำ Operation แต่ละครั้งเท่ากัน (คือ 1 ครั้ง)
* อัลกอริทึม **BFS (การค้นหาในแนวกว้าง)** รับประกันว่า เมื่อเราเจอเป้าหมาย (เลข 0) ครั้งแรก เส้นทางที่พามานั้นจะเป็นเส้นทางที่สั้นที่สุดเสมอ (Shortest Path on Unweighted Graph)

---

## 2. แนวคิดหลัก
มาดูการทำงานของโค้ดทีละส่วน

**ส่วนประกาศตัวแปร (Global Variables):** 
 ```cpp
vector<int> dist(MOD, -1);
queue<int> q;
const int MOD_VAL = 16777216;
```
* `dist:` สร้างตารางเก็บระยะทาง (dist) ขนาดเท่ากับ MOD (ประมาณ 16 ล้านช่อง ค่า -1 หมายถึง "ยังไม่เคยเดินไปถึง"
* `q:` สร้างคิวสำหรับ BFS
* `MOD_VAL:` ค่า Modulo 2^24

**Special Case**
```cpp
if (start_x == 0) return 0;
```
* ถ้า `start_x` เป็น `0` อยู่แล้ว ไม่ต้องทำอะไรเลย ตอบ `0`

**Start**
```cpp
q.push(start_x);
dist[start_x] = 0;
```
* เก็บระยะทาง (dist) ของตัวเริ่มต้น = `0`

**Loop**
```cpp
while (!q.empty()) {
    int curr = q.front(); // ดึงตัวหน้าสุดมาพิจารณา
    q.pop();

    // --- ทางเลือกที่ 1: บวก 1 ---
    int next1 = (curr + 1) % MOD;
    if (next1 == 0) return dist[curr] + 1; // เจอ 0 แล้ว! คืนค่าคำตอบทันที
        
     // ถ้าจุด next1 ยังไม่เคยไปถึง (-1) ให้บันทึกระยะและใส่เข้าคิว
    if (dist[next1] == -1) {
        dist[next1] = dist[curr] + 1;
        q.push(next1);
    }

    // --- ทางเลือกที่ 2: คูณ 2 ---
    int next2 = (curr * 2) % MOD;
    if (next2 == 0) return dist[curr] + 1; // เจอ 0 แล้ว!
        
    if (dist[next2] == -1) {
        dist[next2] = dist[curr] + 1;
        q.push(next2);
    }
}
return -1; // กรณีไม่เจอ (ตามทฤษฎีข้อนี้ต้องเจอเสมอ)
```
---

## 3. ตัวอย่าง Test Case พร้อม Recursion Tree

### Input

```
255
```
### Visual Step

```
Level 0:          [ 255 ]
                 /       \
Level 1:   (+1)[256]    (*2)[510]
           /      \         /     \
Level 2: [257]  [512]* [511]  [1020]
                 /  \
Level 3:      [513] [1024]*
                    ...
                    ... (คูณ 2 ไปเรื่อยๆ ในกิ่งนี้)
                    ...
Level 17:        [ 0 ]  <-- เจอเป้าหมาย! หยุดทันที

```

### Output

```
17
```

---

## 4. อื่น ๆ

* **Time Complexity**

  * Big-O: `O(V + E)`
  * V (**Vertices**): จำนวน Node ทั้งหมดที่เป็นไปได้คือ MOD = 16,777,216
  * E (**Edges**): แต่ละ Node มีทางออก 2 ทาง (+1, x2) ดังนั้น E = 2 x MOD

### เฉลยโค้ด

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MOD = 16777216;

int solve_bfs(int start_x) {
    if (start_x == 0) return 0;

    // เก็บระยะทางจาก x เริ่มต้น (ใช้ -1 เพื่อบอกว่ายังไม่เคยไปถึง)
    vector<int> dist(MOD, -1);
    queue<int> q;

    q.push(start_x);
    dist[start_x] = 0;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        // ลอง Operation 1: (x + 1)
        int next1 = (curr + 1) % MOD;
        if (next1 == 0) return dist[curr] + 1;
        if (dist[next1] == -1) {
            dist[next1] = dist[curr] + 1;
            q.push(next1);
        }

        // ลอง Operation 2: (x * 2)
        int next2 = (curr * 2) % MOD;
        if (next2 == 0) return dist[curr] + 1;
        if (dist[next2] == -1) {
            dist[next2] = dist[curr] + 1;
            q.push(next2);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    long long x;
    cin >> x;

    int result = solve_bfs(x % MOD);
    cout << result << endl;

    return 0;
}
```