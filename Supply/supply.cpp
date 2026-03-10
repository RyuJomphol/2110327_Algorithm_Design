#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Event {
    int day;
    int type;
    int label;
};

bool compareEvents(const Event& a, const Event& b) {
    return a.day < b.day;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;

    vector<Event> events(K);
    for (int i = 0; i < K; ++i) {
        cin >> events[i].day >> events[i].type >> events[i].label;
    }

    sort(events.begin(), events.end(), compareEvents);

    queue<int> stock_queue;
    queue<int> waiting_queue;

    for (int i = 0; i < K; ++i) {
        if (events[i].type == 0) { 
            if (!waiting_queue.empty()) {
                cout << waiting_queue.front() << "\n";
                waiting_queue.pop();
            } else {
                stock_queue.push(events[i].label);
                cout << "0\n";
            }
        } else { 
            if (!stock_queue.empty()) {
                cout << stock_queue.front() << "\n";
                stock_queue.pop();
            } else {
                waiting_queue.push(events[i].label);
                cout << "0\n";
            }
        }
    }
}