#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> all_array;

void permu(vector<int> test, int N, int M, int len) {
    if (N == 0) {
        all_array.push_back(test);
        return;
    }

    if (len == 0) {
        for (int i = 1; i <= M; i++) {
            test[len] = i;
            permu(test, N - 1, M, len + 1);
        }
    }

    else if (len == 1) {
        for (int i = 1; i <= M; i++) {
            if (i != test[0]) {
                test[len] = i;
                permu(test, N - 1, M, len + 1);
            }
        }
    }

    else {
        if (test[len - 2] < test[len - 1]) { // 2 3 X so we can only put 1 2
            for (int j = 1; j < test[len - 1]; j++) {
                test[len] = j;
                permu(test, N - 1, M, len + 1);
            }
        }
        else {
            for (int j = test[len - 1] + 1; j <= M; j++) { // 3 2 X so we can only put 3 4 5
                test[len] = j;
                permu(test, N - 1, M, len + 1);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<int> sol(N , 0);
    permu(sol, N, M, 0);

    for(auto x : all_array) {
        for (int i = 0 ; i < x.size() ; i++) {
            cout << x[i] << " ";
        }
        cout << "\n";
    }
}