//This code is for the problem "Horse Racing" from the 2024 ICPC Asia Regional Contest - Bangkok. The problem requires generating
//This problem is H E L L
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// ฟังก์ชันคำนวณจำนวนรอบ m สำหรับกรณี k=2
ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;
    ll res = 1;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// กรณี n = 2: ใช้ Circle Method (Round-Robin)
void solve_n2(int k) {
    int num_horses = 2 * k;
    int num_rounds = num_horses - 1;
    cout << num_rounds << "\n";

    vector<int> circle;
    for (int i = 2; i <= num_horses; ++i) circle.push_back(i);
    int m = circle.size();

    for (int r = 0; r < num_rounds; ++r) {
        // สนามที่ 1: ม้าตัวที่ 1 เจอกับม้าในวงกลมตามลำดับ r
        cout << 1 << " " << circle[r];
        
        // สนามอื่นๆ: จับคู่ม้าที่อยู่ตำแหน่งสะท้อนกันในวงกลม
        for (int i = 1; i < k; ++i) {
            int idx1 = (r - i + m) % m;
            int idx2 = (r + i) % m;
            cout << " " << circle[idx1] << " " << circle[idx2];
        }
        cout << "\n";
    }
}

// กรณี k = 2: สร้าง Subset ขนาด n และส่วนเติมเต็ม
void generate_k2(int n, int start, vector<int>& current, int total) {
    if (current.size() == n) {
        vector<bool> in_field1(total + 1, false);
        for (int i = 0; i < n; ++i) {
            cout << current[i] << (i == n - 1 ? "" : " ");
            in_field1[current[i]] = true;
        }
        for (int i = 1; i <= total; ++i) {
            if (!in_field1[i]) cout << " " << i;
        }
        cout << "\n";
        return;
    }
    for (int i = start; i <= total; ++i) {
        current.push_back(i);
        generate_k2(n, i + 1, current, total);
        current.pop_back();
    }
}

void solve_k2(int n) {
    int total = 2 * n;
    // จำนวนรอบคือการเลือก n-1 ตัวจากที่เหลือ (เพราะ Fix ม้าหมายเลข 1 ไว้ในสนามแรกเสมอ)
    cout << nCr(total - 1, n - 1) << "\n";
    vector<int> current;
    current.push_back(1); // Fix ม้าตัวที่ 1 เพื่อเลี่ยงการนับซ้ำสนาม
    generate_k2(n, 2, current, total);
}

int main() {
    // ปรับปรุงความเร็ว I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n;
    if (!(cin >> k >> n)) return 0;

    if (n == 2) {
        solve_n2(k);
    } else if (k == 2) {
        solve_k2(n);
    }

    return 0;
}