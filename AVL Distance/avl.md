# AVL Distance

## 1. วิเคราะห์โจทย์

ปัญหา: หาจำนวนของคู่โหนด (pair of nodes) ในต้นไม้ที่มีระยะห่าง (distance) เท่ากับ `k` ที่กำหนด

**นิยาม:**
- ระยะห่าง (distance) ระหว่างสองโหนด = จำนวนขอบในเส้นทางที่สั้นที่สุดระหว่างสองโหนด
- ต้นไม้ (tree) = กราฟที่เชื่อมต่อและไม่มี cycle

**วิธีแก้:** DFS (Depth-First Search) + Dynamic Programming (DP)
- ใช้ `dp[u][i]` = จำนวนโหนดที่มีระยะห่าง `i` จากโหนด `u` ภายในสับปริมาณ (subtree) ที่มี `u` เป็นราก
- ตัดสินใจ DFS ปกติมีการนับคู่โหนดที่มีระยะห่าง `k` เมื่อพิจารณาเส้นทางผ่านโหนดปัจจุบัน

---

## 2. วิเคราะห์โค้ด

**โครงสร้างข้อมูลสำคัญ:**
```cpp
vector<vector<int>> adj;      // adjacency list ของต้นไม้
int ans = 0;                  // ตัวนับผลลัพธ์ (จำนวนคู่ที่ระยะห่าง = k)
vector<int> dfs(int u);       // ฟังก์ชัน returns current_dp
```

**ฟังก์ชัน DFS (ทำการประมวล subtree):**
```cpp
vector<int> dfs(int u) {
    vector<int> current_dp(k + 1, 0);
    current_dp[0] = 1;  // โหนด u เองอยู่ที่ระยะ 0 จาก u
```

เริ่มต้น `current_dp[0] = 1` (แทนโหนด u ตัวเอง)

**ลูปประมวลลูกทั้งหมด:**
```cpp
    for(int v : adj[u]) {
        vector<int> child_dp = dfs(v);  // รับ dp ของลูก v
```

สำหรับแต่ละลูก `v` ของโหนด `u`:
1. เรียก `dfs(v)` ได้รับ `child_dp` ซึ่งเก็บจำนวนโหนดในสับปริมาณของ v ที่ระยะ i จาก v

2. **นับคู่โหนดที่ระยะ k:**
```cpp
        for (int i = 0; i < current_dp.size(); i++) {
            int dist_from_u = i;
            int needed_dist_from_v = k - dist_from_u - 1;

            if (needed_dist_from_v >= 0 && needed_dist_from_v < child_dp.size()) {
                ans += current_dp[dist_from_u] * child_dp[needed_dist_from_v];
            }
        }
```

คำนวณ: ถ้ามีโหนด A จากด้านซ้ายของ u ที่ระยะ `i` จาก u และโหนด B จากสับปริมาณของ v ที่ระยะ `needed_dist_from_v` จาก v แล้วระยะห่าง A-u-v-B = i + 1 + needed_dist_from_v = k

3. **อัปเดต current_dp:**
```cpp
        for (int j = 0 ; j < child_dp.size() ; j++) {
            if (j + 1 <= k) {
                current_dp[j + 1] += child_dp[j];
            }
        }
```

เพิ่มโหนดจากสับปริมาณของ v โดยเพิ่มระยะ 1 (เพราะเพิ่มขอบ u-v)

4. **Return dp:**
```cpp
    return current_dp;
```

---

## 3. ตัวอย่าง Test Case (ตามที่ให้)

Input:
```
6 2
1 2
1 5
5 6
2 4
2 3
```

ต้นไม้:
- โหนด 6 ตัว
- ต้องการระยะห่าง k = 2
- ขอบ: (1,2), (1,5), (5,6), (2,4), (2,3)

**โครงสร้างต้นไม้** (1 เป็นราก):
```
         1
        / \
       2   5
      / \   \
     4   3   6
```

Expected Output: **5**

**ขั้นตอนการนับคู่ที่ระยะ 2:**

| คู่โหนด | เส้นทาง | ระยะห่าง | นับหรือไม่ |
|--------|--------|----------|----------|
| (1, 4) | 1-2-4 | 2 | ✓ |
| (1, 3) | 1-2-3 | 2 | ✓ |
| (1, 6) | 1-5-6 | 2 | ✓ |
| (2, 5) | 2-1-5 | 2 | ✓ |
| (4, 3) | 4-2-3 | 2 | ✓ |
| (5, 4) | 5-1-2-4 | 3 | ✗ |
| (5, 3) | 5-1-2-3 | 3 | ✗ |
| (4, 6) | 4-2-1-5-6 | 4 | ✗ |

**รวม: 5 คู่**

---

## 4. ASCII Visualization ของขั้นตอน DFS

**ต้นไม้ (Tree Structure):**

```
         1
        / \
       2   5
      / \   \
     4   3   6
```

**ส่วนขอบเขต (Distances from each node):**

จากโหนด 1: [ระยะ 0] = {1}, [ระยะ 1] = {2,5}, [ระยะ 2] = {3,4,6}, ...
จากโหนด 2: [ระยะ 0] = {2}, [ระยะ 1] = {1,4,3}, [ระยะ 2] = {5}, ...
จากโหนด 4: [ระยะ 0] = {4}, [ระยะ 1] = {2}, [ระยะ 2] = {1,3}, ...

**ขั้นตอน DFS แบบลำดับ (Post-order Traversal):**

เริ่มจากโหนด 1 ทำ DFS:

**Step 1: DFS(4)**
- current_dp = [1, 0, 0] (โหนด 4 อยู่ระยะ 0 จากตัวเอง)
- ไม่มีลูก
- Return [1, 0, 0]

**Step 2: DFS(3)**
- current_dp = [1, 0, 0]
- ไม่มีลูก
- Return [1, 0, 0]

**Step 3: DFS(2)**
- current_dp = [1, 0, 0]
- ลูก 4: child_dp = [1, 0, 0]
  - ตรวจสอบการนับคู่:
    - dist_from_u=0, needed_dist_from_v=1: 1 ≥ 1? ✗
  - อัปเดต current_dp: current_dp[1] += 1 → [1, 1, 0]
- ลูก 3: child_dp = [1, 0, 0]
  - ตรวจสอบการนับคู่:
    - dist_from_u=0, needed_dist_from_v=1: 1 ≥ 1? ✗
    - dist_from_u=1, needed_dist_from_v=0: 1*1 → ans += 1 (คู่ 4-3)
  - อัปเดต current_dp: current_dp[2] += 1 → [1, 1, 1]
- Return [1, 1, 1]

**Step 4: DFS(6)**
- current_dp = [1, 0, 0]
- ไม่มีลูก
- Return [1, 0, 0]

**Step 5: DFS(5)**
- current_dp = [1, 0, 0]
- ลูก 6: child_dp = [1, 0, 0]
  - ตรวจสอบการนับคู่:
    - dist_from_u=0, needed_dist_from_v=1: 1 ≥ 1? ✗
  - อัปเดต current_dp: [1, 1, 0]
- Return [1, 1, 0]

**Step 6: DFS(1)**
- current_dp = [1, 0, 0]
- ลูก 2: child_dp = [1, 1, 1]
  - ตรวจสอบการนับคู่:
    - dist_from_u=0, needed_dist_from_v=1: 1*1 → ans += 1 (คู่ 1-(4หรือ3))
    - dist_from_u=1, needed_dist_from_v=0: (จะต้องตรวจสอบผลจาก current_dp หลังนี้)
  - อัปเดต current_dp: [1, 1+1, 0+1] = [1, 2, 1]
- ลูก 5: child_dp = [1, 1, 0]
  - ตรวจสอบการนับคู่:
    - dist_from_u=0, needed_dist_from_v=1: 1*1 → ans += 1 (คู่ 1-6)
    - dist_from_u=1, needed_dist_from_v=0: 2*1 → ans += 2 (คู่ 2-5, และคู่อื่น)
  - อัปเดต current_dp: [1, 2+1, 1+0] = [1, 3, 1]
- Final ans = 1 + 1 + 1 + 2 = 5

(ผลลัพธ์ = 5 ตรงกับ expected output)

---

## 5. Complexity (Big O / Big Theta)

- **Time Complexity:**
  - DFS traverses ทุกโหนด 1 ครั้ง = O(N)
  - ในแต่ละโหนด ใช้ for loop กับ child의 dp vector และ current_dp: O(k) per child
  - ทุกโหนดใช้ O(k) ต่อขอบเข้า (edge) → O(N*k) โดยรวม

  $$T(N, k) = \Theta(N \cdot k)$$

- **Space Complexity:**
  - DP vectors สำหรับแต่ละโหนด: O(k) per node
  - Recursion stack depth = O(N) ในกรณี worst (skewed tree)
  - Total: O(N * k) สำหรับเก็บ DP + O(N) สำหรับ stack

  $$S(N, k) = \Theta(N \cdot k)$$

---