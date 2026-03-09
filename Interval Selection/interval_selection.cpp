#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Class
{
    int start;
    int end;
};

bool compare(Class a, Class b)
{
    return a.end < b.end;
}


int main() {
    int N;
    cin >> N;
    vector<Class> classes(N);
    for (int i = 0; i < N; i++) {
        cin >> classes[i].start;
    }

    for (int i = 0; i < N; i++) {
        cin >> classes[i].end;
    }

    sort(classes.begin(), classes.end(), compare);

    int count = 0;
    int last_end_time = -1;
    for (int i = 0; i < N; i++) {
        if (classes[i].start >= last_end_time) {
            count++;
            last_end_time = classes[i].end;
        }
    }
    cout << count << endl;
}