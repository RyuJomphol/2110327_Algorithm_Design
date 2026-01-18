#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long N,Q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> N >> Q;
    vector<pair<long long, long long>> sort_array(N);
    for (int i = 0; i < N; ++i) {
        cin >> sort_array[i].first >> sort_array[i].second;
    }
    sort(sort_array.begin(), sort_array.end());
//  for (auto x : sort_array) {
//      cout << x.first << ' ' << x.second << endl;
//  }
    vector<long long> num_before(N);
    num_before[0] = sort_array[0].second;
    for (int i = 0 ; i < N - 1 ; i++) {
        num_before[i + 1] = num_before[i] + sort_array[i + 1].second;
    }
//  for (auto x : array_idx) {
//      cout << x << endl;
//  }
    for (int i = 0 ; i < Q ; i++) {
        long long input;
        cin >> input;
        long long real_idx = lower_bound(num_before.begin(),num_before.end(),input) - num_before.begin();
        cout << sort_array[real_idx].first << endl;
    }
}