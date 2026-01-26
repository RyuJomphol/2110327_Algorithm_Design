#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int N;
    cin >> N;
    vector<pair<int,int>> ordered_pair(N); 
    for (int i = 0 ; i < N ; i++) {
        cin >> ordered_pair[i].first >> ordered_pair[i].second;
    }

    sort(ordered_pair.begin(), ordered_pair.end(), [](auto &a, auto &b) {
        return a.first > b.first;
    });

    int maxY = -1;
    int count = 0;

    for (auto order : ordered_pair) {
        if (order.second > maxY) {
            count++;
            maxY = order.second;
        }
    }

    cout << count << endl;
}