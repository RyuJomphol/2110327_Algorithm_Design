#include <iostream>
#include <vector>

using namespace std;

struct Command {
    int type;
    int x, y;
};

vector<Command> ans;

void place_block(int size, int x, int y, int hole_x, int hole_y) {
    if (size == 1) return;

    int mid = size / 2;
    int center_x = x + mid;
    int center_y = y + mid;

    int top_left_x = center_x - 1;
    int top_left_y = center_y - 1;

    // check hole

    if (hole_x < center_x && hole_y < center_y) {
        ans.push_back({0, top_left_x, top_left_y});

        place_block(mid, x, y, hole_x, hole_y);
        place_block(mid, center_x, y, center_x, center_y - 1);
        place_block(mid, x, center_y, center_x - 1, center_y);
        place_block(mid, center_x, center_y, center_x, center_y);
    }

    else if (hole_x >= center_x && hole_y < center_y) {
        ans.push_back({1, top_left_x, top_left_y});

        place_block(mid, x, y, center_x - 1, center_y - 1);
        place_block(mid, center_x, y, hole_x, hole_y);
        place_block(mid, x, center_y, center_x - 1, center_y);
        place_block(mid, center_x, center_y, center_x, center_y);
    }

    else if (hole_x < center_x && hole_y >= center_y) {
        ans.push_back({2, top_left_x, top_left_y});

        place_block(mid, x, y, center_x - 1, center_y - 1);
        place_block(mid, center_x, y, center_x, center_y - 1);
        place_block(mid, x, center_y, hole_x, hole_y);
        place_block(mid, center_x, center_y, center_x, center_y);
    }

    else {
        ans.push_back({3, top_left_x, top_left_y});

        place_block(mid, x, y, center_x - 1, center_y - 1);
        place_block(mid, center_x, y, center_x, center_y - 1);
        place_block(mid, x, center_y, center_x - 1, center_y);
        place_block(mid, center_x, center_y, hole_x, hole_y);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int L, X, Y;
    cin >> L >> X >> Y;
    place_block(L, 0, 0, X, Y);

    cout << ans.size() << "\n";
    for (auto& cmd : ans) {
        cout << cmd.type << " " << cmd.x << " " << cmd.y << "\n";
    }
}
