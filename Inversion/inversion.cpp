#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> v(N);
    for (int i = 0 ; i < N ; i++) {
        cin >> v[i];
    }
    int count = 0;
    for (int i = 0 ; i < v.size() ; i++) {
        for (int j = i ; j < v.size() ; j++) {
            if (v[i] > v[j]) count++;
        }
    }
    cout << count << endl;
}