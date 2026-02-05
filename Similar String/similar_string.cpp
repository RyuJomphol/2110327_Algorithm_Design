#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string getCanonical(string s) {
    int n = s.length();

    if (n % 2 != 0) {
        return s;
    }

    string s1 = getCanonical(s.substr(0,n / 2));
    string s2 = getCanonical(s.substr(n / 2));

    if (s1 < s2) {
        return s1 + s2;
    }
    else {
        return s2 + s1;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string a, b;
    cin >> a >> b;

    if (getCanonical(a) == getCanonical(b)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}