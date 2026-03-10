#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int f, w, n;
    cin >> f >> w >> n;

    vector<int> food(f);
    for (int i = 0; i < f; i++) {
        cin >> food[i];
    }

    sort(food.begin(), food.end());

    int light_count = 0;
    int last_covered = -1;

    for (int i = 0; i < f; i++) {
        if (food[i] > last_covered) {
            light_count++;
            last_covered = food[i] + (2 * w);
        }
    }

    cout << light_count << endl;
}