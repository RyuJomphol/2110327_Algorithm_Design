# Longest Common Subsequence (LCS)

## 1. วิเคราะห์โจทย์ Longest Common Subsequence
ให้สตริงสองตัว `A` และ `B`   

- `A = a₁ a₂ ... aₙ`  
- `B = b₁ b₂ ... bₘ`

"Subsequence" หมายถึงการลบตัวอักษรบางตัวออกโดยยังคงลำดับเดิมไว้
เช่น `a₂ a₄ aₙ` เป็น subsequence ของ `A` แต่ `a₄ a₁ a₂` ไม่ใช่

Longest common subsequence คือ subsequence ยาวที่สุดที่เป็นของร่วมทั้งสองสตริง
โจทย์: คืน **ความยาว** ของ LCS ของ `A` และ `B`

---

## 2. วิเคราะห์ที่มาสมการ Recurrence Relation
นิยาม `dp[i][j]` = ความยาวของ LCS ของ `A[1..i]` และ `B[1..j]`

ฐาน:
```
dp[0][j] = 0  for all j
dp[i][0] = 0  for all i
```

เมื่อ `i ≥ 1` และ `j ≥ 1`:
- ถ้าอักขระท้ายตรงกัน (`aᵢ == bⱼ`):  
  `dp[i][j] = dp[i-1][j-1] + 1`   
  (สามารถต่ออักขระนั้นเข้าไปใน LCS ของ prefix)
- มิฉะนั้น:  
  `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`  
  (ทิ้งตัวบนสุดหรือซ้ายสุดแล้วเลือกค่ามากกว่า)

คำตอบคือ `dp[n][m]` ซึ่งเท่ากับความยาว LCS ของทั้งสองสตริง

---

## 3. อธิบายโค้ด + ยกตัวอย่าง testcase
โค้ดใน `lcs.cpp` อ่านสตริงทั้งสองด้วยสั่น:  

```cpp
string a, b;
cin >> a >> b;
int n = a.length();
int m = b.length();
vector<vector<int>> dp(n+1, vector<int>(m+1,0));
for(int i=1;i<=n;i++){
  for(int j=1;j<=m;j++){
    if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1]+1;
    else dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
  }
}
cout<<dp[n][m]<<"\n";
```

### ตัวอย่าง
```
acbdegcedbg
begcfeubk
```
- LCS ยาวที่สุดอาจเป็น `b e g c e b` หรือชุดอื่น ๆ ความยาว **6**
- โปรแกรมคืนค่า `6` ตามที่ต้องการ

---

## 4. Time Complexity
- ลูปสองชั้น `i=1..n`, `j=1..m` → **O(n*m)**
- พื้นที่ **O(n*m)** สำหรับตาราง `dp` 

สามารถลดพื้นที่เป็น `O(min(n,m))` ด้วยการเก็บเพียงสองแถวสุดท้ายถ้าจำเป็น

---

สรุป: LCS ใช้ DP สองมิติที่เป็นแบบคลาสสิก เป็นพื้นฐานสำหรับปัญหา
string comparison, diff tools และ bioinformatics
