#include <iostream>
#include <vector>

using namespace std;

int n,m;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> a[i];
    }
    for (int i = 0 ; i < m ; i++) {
        int input,k = 0;
        cin >> input;
        for (int j = 0 ; j < n ; j++) {
            if (a[j] > input) {
                k++;
            }
            else if (a[j] == input) {
                break;
            }
        }
        cout << k << endl;
    }
}