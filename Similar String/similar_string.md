# Similar String

## 1. วิเคราะห์โจทย์
โจทย์: ให้สตริงสองตัว `a` และ `b` (ความยาวเท่ากัน) ตรวจสอบว่าทั้งสอง "เหมือนกันตามนิยามพิเศษ" หรือไม่ โดยอนุญาตให้สลับครึ่งซ้าย-ขวาได้ซ้ำ ๆ เมื่อความยาวเป็นคู่ (even).

วิธีที่ใช้: Recursive canonicalization (divide-and-conquer)
- ถ้าความยาวเป็นคี่ ให้สตริงคงที่ (ไม่สามารถสลับได้) — canonical = s
- ถ้าความยาวเป็นคู่ แบ่งเป็นสองครึ่ง s = s_left + s_right
  - คำนวณ canonical ของทั้งสองครึ่ง (`c1`, `c2`) แบบ recursive
  - canonical ของ s คือ `min(c1+c2, c2+c1)` (จัดเรียงพยัญชนะสองครึ่งให้เป็นลำดับน้อยที่สุด lexicographically)
- สตริงสองตัวถือว่า "similar" หาก canonical(a) == canonical(b)

เหตุผล: การสลับครึ่งซ้าย-ขวาซ้ำ ๆ จะเกิดแต่ในกรณีที่ความยาวเป็นคู่ และการจัด canonical ให้ผลเดียวสำหรับทุกลำดับการสลับที่เป็นไปได้ — การเปรียบเทียบ canonical จึงตรวจสอบความเท่ากันในคลาสการสลับทั้งหมด

---

## 2. วิเคราะห์โค้ด (`similar_string.cpp`)
ฟังก์ชันหลัก:

```cpp
string getCanonical(string s) {
    int n = s.length();
    if (n % 2 != 0) return s;
    string s1 = getCanonical(s.substr(0,n/2));
    string s2 = getCanonical(s.substr(n/2));
    if (s1 < s2) return s1 + s2; else return s2 + s1;
}
```

- เมื่อ n คี่: คืน s เอง
- เมื่อ n คู่: แบ่งครึ่ง สร้าง canonical ของซีกซ้ายและขวา แล้วคืนการรวมแบบน้อยที่สุดระหว่าง `c1+c2` กับ `c2+c1`
- ใน `main()` อ่าน `a`, `b` และเปรียบเทียบ `getCanonical(a)` กับ `getCanonical(b)` — ถ้าเท่าพิมพ์ `YES` มิฉะนั้น `NO`.

ข้อสังเกตเชิงประสิทธิภาพ: ฟังก์ชันทำงานแบบ recursive แยกครึ่งความยาวทุกระดับ การคำนวณซ้ำสามารถหลีกเลี่ยงด้วย memoization แต่สำหรับความยาวที่พอเหมาะ (เช่น ≤ 2^20) โค้ดปัจจุบันมักเพียงพอ

---

## 3. ตัวอย่าง Test Case
Input:
```
aaba
abaa
```
Output:
```
YES
```

เหตุผลโดยย่อ (trace canonicalization):
- a = "aaba" (n=4 even)
  - left="aa" → n=2 even → left="a"(odd) => "a"; right="a" => "a" → c_left = min("a"+"a","a"+"a") = "aa"
  - right="ba" → left="b" => "b"; right="a" => "a" → c_right = min("b"+"a","a"+"b") = "ab"
  - canonical(a) = min("aa"+"ab" = "aaab", "ab"+"aa" = "abaa") = "aaab"

- b = "abaa"
  - left="ab" -> c_left = min("a"+"b","b"+"a") = "ab"
  - right="aa" -> c_right = "aa"
  - canonical(b) = min("ab"+"aa" = "abaa", "aa"+"ab" = "aaab") = "aaab"

ทั้งคู่ได้ canonical เดียวกัน "aaab" → ดังนั้นพิมพ์ `YES`.

ASCII visualization (แบ่งและเรียง):

aaba:  [aa] [ba]
       c1="aa"  c2="ab"  -> choose order c2+c1="aaab"

abaa:  [ab] [aa]
       c1="ab"  c2="aa"  -> choose order c2+c1="aaab"

---

## 4. Complexity (Big O / Big Theta)
- ให้ n = |s|.
- การแบ่งครึ่งทำให้ recursion มีความลึก O(log n).
- แต่ที่แต่ละระดับ เราสสร้างและรวมสตริงขนาด n (การคัดลอกเกิดขึ้นเมื่อรวมและ substr) — ถ้าไม่ใช้ sharing/rope ผลงานรวมเป็น:

Time = T(n) = 2 T(n/2) + O(n) → T(n) = O(n log n).

- Space: การเรียก stack O(log n) และการสร้างสตริงชั่วคราวรวม O(n log n) ในการคัดลอกแบบ naive; ถาใช้แชร์หน่วยความจำ (เช่น memoization หรือ string views) อาจลดไป O(n).

สรุป:
- Time = Θ(n log n) (โดยการคัดลอกสตริงแบบ naive)
- Space = Θ(n log n) worst-case for temporaries (stack O(log n))
