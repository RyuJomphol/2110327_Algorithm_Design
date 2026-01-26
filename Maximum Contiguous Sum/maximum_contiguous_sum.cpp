#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    int a;
    int current_sum;
    int max_sum;

    for(int i = 0; i < N; i++) {
        cin >> a;
        if (i == 0) {
            current_sum = a;
            max_sum = a;
        }
        else {
            current_sum = max(a , current_sum + a);
            max_sum = max(max_sum, current_sum);
        }
    }
    cout << max_sum << endl;
}