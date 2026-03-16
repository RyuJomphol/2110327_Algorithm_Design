#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Monster {
    int L, R, id;
    bool operator<(const Monster& other) const {
        return L < other.L; // Sort by L
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k, w;
    cin >> n >> m >> k >> w;

    vector<int> monster_positions(m);
    for (int i = 0; i < m; i++) {
        cin >> monster_positions[i];
    }

    vector<long long> health(m);
    long long total_health = 0;
    for (int i = 0; i < m; i++) {
        cin >> health[i];
        total_health += health[i];
    }

    vector<Monster> monsters(m);
    for (int i = 0; i < m; i++) {
        monsters[i].L = max(1, monster_positions[i] - w);
        monsters[i].R = min(n, monster_positions[i] + w);
        monsters[i].id = i;
    }

    sort(monsters.begin(), monsters.end());

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int monster_index = 0;
    long long max_damage = 0;

    for (int x = 1; x <= n; x++) {
        while (monster_index < m && monsters[monster_index].L <= x) {
            pq.push({monsters[monster_index].R, monsters[monster_index].id});
            monster_index++;
        }

        while (!pq.empty() && pq.top().first < x) {
            pq.pop();
        }

        if (!pq.empty()) {
            int monster_id = pq.top().second;
            health[monster_id]--;
            max_damage++;

            if (health[monster_id] == 0) {
                pq.pop();
            }
        }
    }
    long long actual_damage = min(max_damage , (long long)k);

    long long remaining_health = total_health - actual_damage;
    cout << remaining_health << endl;
}