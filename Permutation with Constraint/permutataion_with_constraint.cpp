#include <iostream>
#include <vector>

using namespace std;

int n,m;
vector<int> all_permutation;
vector<int> before;
vector<bool> used;

void permutation(int n , vector<int> &all_permutation , int step , vector<bool> &used) {
    if (step == n) {
        for (auto x : all_permutation) {
            cout << x << " ";
        }
        cout << endl;
    }

    else {
        for(int i = 0 ; i < n ; i++) {
            if(used[i] == false && (before[i] == -1 || used[before[i]])) {
                used[i] = true;
                all_permutation[step] = i;
                permutation(n, all_permutation, step + 1, used);
                used[i] = false;
            }
            else {
                continue;
            }
        }
    }
}
 

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    //set up
    before.resize(n , -1); //before[i] = x means x must comes before i
    used.resize(n, false);
    all_permutation.resize(n);

    for (int i = 0 ; i < m ; i++) {
    int a,b;
    cin >> a >> b;
    before[b] = a; //a must comes before b
    }

    permutation(n , all_permutation , 0 , used);
}