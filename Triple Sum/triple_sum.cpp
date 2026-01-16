#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N,M;
    cin >> N >> M;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int j = 0 ; j < M ; j++) {
        long long num;
        cin >> num;
        bool found = false;

        for (int i = 0 ; i < N - 2; i++) {
            int left = i + 1;
            int right = N - 1;

            while (left < right) {
                long long current_sum = A[i] + A[left] + A[right];

                if (current_sum == num) {
                    found = true;
                    break;
                } else if (current_sum < num) {
                    left++;
                } else {
                    right--;
                }
            }
            if (found) break;
        }
        if (found) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}