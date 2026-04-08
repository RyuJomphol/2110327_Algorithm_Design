#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

const int MAXN = 105;

int n;
double W, ans = 0;

struct Item {
    double w, v;
    // เรียงตามน้ำหนักจากมากไปน้อย (ตามโค้ดเดิม)
    bool operator < (const Item &other) const {
        return w > other.w;
    }
} a[MAXN], fraction[MAXN][MAXN];

// ฟังก์ชันเปรียบเทียบความคุ้มค่า (v/w)
bool compare(const Item &p, const Item &q) {
    return p.v * q.w > q.v * p.w;
}

// ฟังก์ชันคำนวณขอบเขตบน (Upper Bound)
double getHeuristic(int i, double remainingW) {
    double h = 0;
    int j = i;

    while (j < n) {
        if (remainingW >= fraction[i][j].w) {
            h += fraction[i][j].v;
            remainingW -= fraction[i][j].w;
        } else {
            // กรณีใส่ได้ไม่เต็มชิ้น (Fractional)
            h += (remainingW / fraction[i][j].w) * fraction[i][j].v;
            break;
        }
        j++;
    }
    return h;
}

void knapsack(int i, double sumw, double sumv) {
    // กรณีน้ำหนักเกิน
    if (sumw > W) return;

    // กรณีพิจารณาครบทุกชิ้นแล้ว
    if (i == n) {
        if (sumv > ans) ans = sumv;
        return;
    }

    // Branch and Bound: ถ้าผลรวมปัจจุบัน + อนาคตที่ดีที่สุด สู้คำตอบปัจจุบันไม่ได้ ให้ตัดกิ่ง
    if (sumv + getHeuristic(i, W - sumw) <= ans) return;

    // เลือกไอเทมชิ้นที่ i
    knapsack(i + 1, sumw + a[i].w, sumv + a[i].v);
    
    // ไม่เลือกไอเทมชิ้นที่ i
    knapsack(i + 1, sumw, sumv);
}

int main() {
    // เพิ่มประสิทธิภาพให้ cin/cout
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> W >> n)) return 0;

    for (int i = 0; i < n; i++) cin >> a[i].v;
    for (int i = 0; i < n; i++) cin >> a[i].w;

    // เรียงลำดับพื้นฐาน
    sort(a, a + n);

    // เตรียมตารางไอเทมที่เรียงตามความคุ้มค่าไว้ล่วงหน้าสำหรับแต่ละตำแหน่ง i
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            fraction[i][j] = a[j];
        }
        sort(fraction[i] + i, fraction[i] + n, compare);
    }

    knapsack(0, 0.0, 0.0);

    // แสดงผลทศนิยม 4 ตำแหน่ง (หรือปรับตามโจทย์)
    cout << fixed << setprecision(4) << ans << endl;

    return 0;
}