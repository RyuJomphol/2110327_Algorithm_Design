#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int n;
    cin >> n;
    int num_horses;
    int total_horses = 0;
    vector<pair<int, int>> horses(n);
    for (int i = 0; i < n; i++) {
        cin >> num_horses;
        horses[i] = {num_horses, i + 1};
        total_horses += num_horses;
    }

    sort(horses.begin(), horses.end());

    int sum_all = total_horses;
    int rigil_sum = 0;
    int i = 0;
    while(i < n && sum_all - horses[i].first > rigil_sum + horses[i].first) {
        sum_all -= horses[i].first;
        rigil_sum += horses[i].first;
        i++;
    } 

    cout << n - i << "\n";
    for (int j = i; j < n; j++) {
        cout << horses[j].second << " ";
    }

}