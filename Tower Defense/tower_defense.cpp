#include <iostream>
#include <vector>

using namespace std;

int n; //map size
int m; //number of monsters
int k; //number of towers
int w; //shooting range
vector<int> p; //The position of each monster
vector<int> h; //The health of each monster
vector<int> t; //The location of each turret
vector<int> a; //Which monster does the tower i chose target??
int min_sum = 0;

using namespace std;

void shooting(int step) {
    if (step == k) {
        vector<int> hit(m);
        for (int j = 0 ; j < k ; j++) {
            int tower_pos = t[j];
            int monster_pos = a[j];
            if (abs(p[monster_pos] - tower_pos) <= w) {
                hit[monster_pos]++;
                hit[monster_pos] = min(hit[monster_pos],h[monster_pos]);
            }
        }

        int sum = 0;
        for (int i = 0;i < m;i++) {
            sum += max(h[i] - hit[i],0);
        }

        if (sum < min_sum) {
            min_sum = sum;
        }
    }
    
    else {
        for (int i = 0 ; i < m ; i++) {
            a[step] = i;
            shooting(step + 1);
        }
    }
}

int main() {
    cin >> n >> m >> k >> w;
    p.resize(m);
    h.resize(m);
    t.resize(k);
    a.resize(k);
    for (int i = 0 ; i < m ; i++) {
        cin >> p[i];
    }
    for (int i = 0 ; i < m ; i++) {
        cin >> h[i];
        min_sum += h[i];
    }
    for (int i = 0 ; i < k ; i++) {
        cin >> t[i];
    }
    shooting(0);
    cout << min_sum << endl;
}