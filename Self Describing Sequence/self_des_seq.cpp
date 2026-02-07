#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_K = 676767;

long long SELF_DESCRIBING_SEQUENCE[MAX_K + 1];
int PREV_SELF_DESCRIBING_SEQUENCE[MAX_K + 1];

void precompute() {
    PREV_SELF_DESCRIBING_SEQUENCE[1] = 1;
    PREV_SELF_DESCRIBING_SEQUENCE[2] = 2;
    PREV_SELF_DESCRIBING_SEQUENCE[3] = 2;

    int current_index = 4;
    for (int i = 3; current_index <= MAX_K; i++) {
        for (int j = 0; j < PREV_SELF_DESCRIBING_SEQUENCE[i] && current_index <= MAX_K; j++) {
            PREV_SELF_DESCRIBING_SEQUENCE[current_index++] = i;
        }
    }

    SELF_DESCRIBING_SEQUENCE[1] = 1;
    for (int i = 2; i <= MAX_K; i++) {
        SELF_DESCRIBING_SEQUENCE[i] = SELF_DESCRIBING_SEQUENCE[i - 1] + PREV_SELF_DESCRIBING_SEQUENCE[i];
    }
}

void SDS() {
    int x;
    cin >> x;

    auto it = lower_bound(SELF_DESCRIBING_SEQUENCE + 1, SELF_DESCRIBING_SEQUENCE + MAX_K + 1, x);
    cout << (it - SELF_DESCRIBING_SEQUENCE) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int N;
    cin >> N;
    while (N--) {
        SDS();
    }
}