# Billboard Feng Shui - วิเคราะห์และคำอธิบาย

## 1. วิเคราะห์โจทย์

### ปัญหา
ถนนเส้นหนึ่งยาว **N** กิโลเมตร ในแต่ละกิโลเมตรสามารถติดป้ายโฆษณาได้ 1 อัน

**เป้าหมาย:** เลือกติดป้ายโฆษณาให้ผลรวมจำนวนคนที่เห็นมากที่สุด

### ข้อจำกัด
1. **กฎทั่วไป:** ไม่ติดป้ายติดกัน
   - ถ้าติดที่ตำแหน่ง i แล้ว ไม่ติดที่ i-1 และ i+1
   
2. **กฎฮวงจุ้ย (Pattern Forbidden):** มี pattern ความยาว K ที่ห้าม
   - Pattern P[0..K-1] ห้ามปรากฏในตำแหน่งติดต่อกัน K ตำแหน่ง
   - P[i] = 1 หมายถึงติดป้าย, P[i] = 0 หมายถึงไม่ติด

### ตัวอย่าง
- N = 5, K = 3, C = [10, 11, 12, 13, 14], P = [1, 0, 1]
- Pattern [1, 0, 1] ห้ามปรากฏ
- ห้าม: [1,0,1,x,x], [x,1,0,1,x], [x,x,1,0,1]

---

## 2. Recurrence Relation (สมการ DP)

### แนวคิด: State Machine DP

เราใช้ **Aho-Corasick-like state machine** ติดตามว่าเรากำลังสร้าง pattern ห้ามเพียงใด

**State DP:**
```
dp[i][j][bit] = ผลรวมสูงสุดของคนที่เห็นเมื่อ:
  - พิจารณาเสร็จสิ้น i กิโลเมตรแรก
  - j = ความยาวของคำนำหน้า pattern ที่ตรงกับ k ตำแหน่งสุดท้าย
  - bit = ก่อนหน้านี้ติดป้าย (1) หรือไม่ติด (0) เพื่อเข้มงวด non-adjacent
```

### Transition

**ที่ตำแหน่ง i → i+1 มี 2 ตัวเลือก:**

#### ตัวเลือก 1: ไม่ติดป้าย (bit = 0)
```
- ทำ trans[j][0] เพื่ออัพเดท prefix ที่ตรงกับ pattern
- ถ้า trans[j][0] < K แสดงว่ายังไม่เกิด pattern
  - dp[i+1][trans[j][0]][0] = max(dp[i+1][trans[j][0]][0], dp[i][j][bit])
```

#### ตัวเลือก 2: ติดป้าย (bit = 1) - เฉพาะเมื่อก่อนหน้าไม่ติด (bit == 0)
```
- ทำ trans[j][1] เพื่ออัพเดท prefix
- ถ้า trans[j][1] < K แสดงว่ายังไม่สร้าง pattern ห้าม
  - dp[i+1][trans[j][1]][1] = max(..., dp[i][j][0] + C[i+1])
```

### Precompute Transitions

ฟังก์ชัน `precompute_transitions()` คำนวณ:
```
trans[j][bit] = ความยาว prefix ใหม่เมื่อ:
  - หลังจากคำนำหน้า P[0..j-1] ที่ตรงกับ j ตำแหน่ง
  - เพิ่มบิต bit ใหม่เข้าไป
  - ค้นหา overlap ที่ยาวที่สุดระหว่าง P[0..k-1]
```

---

## 3. ตัวอย่าง Test Case การคำนวณ

### Input
```
5 3
10 11 12 13 14
1 0 1
```

### Data
- N = 5 (5 km)
- K = 3 (pattern length)
- C = [10, 11, 12, 13, 14] (visibility at each position)
- P = [1, 0, 1] (forbidden pattern)

### Precompute Transitions

สำหรับ P = [1, 0, 1]:

| j | bit | current_seq | overlap len | trans[j][bit] |
|---|-----|-------------|-------------|---------------|
| 0 | 0   | [0]         | 0 (no match) | 0             |
| 0 | 1   | [1]         | 1 (match P[0:1]) | 1          |
| 1 | 0   | [1,0]       | 0 (no match) | 0             |
| 1 | 1   | [1,1]       | 0 (no match) | 0             |
| 2 | 0   | [1,0,0]     | 0 (no match) | 0             |
| 2 | 1   | [1,0,1]     | -1 (ERROR/K) | - (invalid)   |

> Note: เมื่อ trans[j][1] = K หรือเกิน K แสดงว่าเกิด pattern ห้าม จึงไม่ทำ transition

### DP Computation

**Initial:**
```
dp[0][0][0] = 0  (เริ่มต้น)
```

**ตัวอย่างเส้นทาง DP:**

Position i=0 → i=1 (เลือก position 0):
- ไม่ติดป้าย: `dp[1][0][0] = 0`
- ติดป้าย: `dp[1][1][1] = 0 + 10 = 10`

Position i=1 → i=2 (จาก dp[1][1][1] = 10):
- ไม่ติดป้าย: `dp[2][1][0] = 10` (transition: trans[1][0] = 0? no, trans[1][0] = 0 เสมอ reencode)
- ติดป้าย: ห้าม (bit ต้อง 0 เท่านั้น)

Position i=1 → i=2 (จาก dp[1][0][0] = 0):
- ไม่ติดป้าย: `dp[2][0][0] = 0`
- ติดป้าย: `dp[2][1][1] = 0 + 11 = 11`

...อย่างนี้ต่อไปจนกว่าจะถึง i = N = 5

### Final Answer

**Optimal placement:** `[0, 1, 0, 0, 1]`
- Position 2: 11
- Position 5: 14
- **Total: 25** ✓

```
Verification:
- Adjacent check: ✓ (no two 1s adjacent)
- Pattern check: ✓ (no [1,0,1] substring)
- Sum: 11 + 14 = 25
```

---

## 4. Code Explanation + Example Trace

### Main Algorithm

```cpp
// Initialize DP table
dp[0][0][0] = 0;  // Start: 0 km done, prefix match = 0, previously no billboard

// Process each km
for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
        for (int bit = 0; bit < 2; bit++) {
            if (dp[i][j][bit] == -1) continue;  // Invalid state
            
            // Option 1: Don't place billboard at position i+1
            int nj0 = trans[j][0];  // Update prefix length
            if (nj0 < K) {
                dp[i + 1][nj0][0] = max(dp[i + 1][nj0][0], 
                                        dp[i][j][bit]);
            }
            
            // Option 2: Place billboard at position i+1
            // (only if previous position had no billboard)
            if (bit == 0) {
                int nj1 = trans[j][1];  // Update prefix length
                if (nj1 < K) {  // Must not complete the forbidden pattern
                    dp[i + 1][nj1][1] = max(dp[i + 1][nj1][1], 
                                            dp[i][j][bit] + C[i + 1]);
                }
            }
        }
    }
}

// Find maximum value at the end
long long ans = 0;
for (int j = 0; j < K; j++) {
    ans = max(ans, max(dp[N][j][0], dp[N][j][1]));
}
cout << ans << "\n";
```

### Key Variables

| Variable | ความหมาย |
|----------|---------|
| `C[i]` | จำนวนคนที่เห็นป้ายที่ i |
| `P[j]` | Forbidden pattern (P[j] = 1: ติด, 0: ไม่ติด) |
| `trans[j][bit]` | State transition: prefix length หลังจาก append bit |
| `dp[i][j][bit]` | DP value: ที่ position i, prefix match j, last bit |

---

## 5. Time Complexity

### Breakdown

1. **Precompute Transitions:**
   - For each j ∈ [0, K): O(K)
   - For each bit ∈ {0, 1}: O(2)
   - For each possible length len ∈ [K, 0]: O(K)
   - String matching inside: O(K)
   - **Total: O(K²) · O(K) = O(K³)**

2. **DP Computation:**
   - For each position i ∈ [0, N): O(N)
   - For each state j ∈ [0, K): O(K)
   - For each bit ∈ {0, 1}: O(2)
   - Transition per state: O(1)
   - **Total: O(N · K · 2) = O(N·K)**

3. **Find Answer:**
   - Scan all final states: O(K)

### Total Time Complexity
$$\boxed{O(K^3 + N \cdot K)}$$

**In practice:** เนื่องจาก K มักเล็ก (≤ 60) ส่วน N ใหญ่กว่า (≤ 60)
- Precompute: negligible
- DP dominates: **O(N·K)**

### Space Complexity
$$\boxed{O(N \cdot K)}$$
- DP table: `dp[N+1][K][2]`
- Transition table: `trans[K][2]`
- Pattern array: `P[K]`, `C[N]`

---

## 6. Edge Cases

| Case | วิธีแก้ |
|------|--------|
| K = N: Pattern ข้ามทั้งถนน | DP ต้อง track prefix ทั้งหมด |
| No valid placement | DP ส่งข้อมูล -1 → answer = 0 |
| Pattern เป็น all 0s | trans[j][0] ≤ j เสมอ |
| Greedy fails | ΔP ต้องใช้ DP เพราะ pattern interference |

---

## 7. สรุป

**Billboard Feng Shui** เป็นปัญหา **DP with Pattern Matching** ที่ต้อง:
1. ✓ หลีกเลี่ยง adjacent billboards (หน่วยความจำก่อนหน้า bit)
2. ✓ หลีกเลี่ยง forbidden pattern (state machine tracking prefix)
3. ✓ Maximize visibility sum (DP optimization)

**Key Insight:** ใช้ state machine คิดเหมือน **KMP/Aho-Corasick** แต่สำหรับ DP transitions แทน string matching

