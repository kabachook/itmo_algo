#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    bool good = false;
    char color = 'w';
    pair<int, int> parent = {-1, -1};
};

void bfs(vector<vector<Node>> &map, pair<int, int> start, int n, int m) {
    map[start.first][start.second].color = 'g';
    queue<pair<int, int>> q;
    q.push(start);

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        pair<int, int> v;

        // UP
        v = {u.first - 1, u.second};
        if (v.first != -1 && map[v.first][v.second].good) {
            if (map[v.first][v.second].color == 'w') {
                map[v.first][v.second].color = 'g';
                map[v.first][v.second].parent = u;
                q.push(v);
            }
        }

        // RIGHT
        v = {u.first, u.second + 1};
        if (v.second != m && map[v.first][v.second].good) {
            if (map[v.first][v.second].color == 'w') {
                map[v.first][v.second].color = 'g';
                map[v.first][v.second].parent = u;
                q.push(v);
            }
        }

        // DOWN
        v = {u.first + 1, u.second};
        if (v.first != n && map[v.first][v.second].good) {
            if (map[v.first][v.second].color == 'w') {
                map[v.first][v.second].color = 'g';
                map[v.first][v.second].parent = u;
                q.push(v);
            }
        }

        // LEFT
        v = {u.first, u.second - 1};
        if (v.second != -1 && map[v.first][v.second].good) {
            if (map[v.first][v.second].color == 'w') {
                map[v.first][v.second].color = 'g';
                map[v.first][v.second].parent = u;
                q.push(v);
            }
        }


        map[u.first][u.second].color = 'b';

    }

}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<vector<Node>> map(n, vector<Node>(m));

    pair<int, int> start, target;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char t;
            cin >> t;
            if (t == '.') {
                map[i][j].good = true;

            }
            if (t == 'S') {
                start = {i, j};
                map[i][j].good = true;
            }
            if (t == 'T') {
                target = {i, j};
                map[i][j].good = true;
            }

        }
    }

    bfs(map, start, n, m);

    if (map[target.first][target.second].color == 'w') {
        cout << -1 << endl;
        return 0;
    }

    string path;

    pair<int, int> curr = target;

    while (curr != start) {
        auto p = map[curr.first][curr.second].parent;
        if (p.first - curr.first == -1) {
            path += 'D';
        }
        if (p.first - curr.first == 1) {
            path += 'U';
        }
        if (p.second - curr.second == -1) {
            path += 'R';
        }
        if (p.second - curr.second == 1) {
            path += 'L';
        }
        curr = p;
    }

    reverse(path.begin(), path.end());

    cout << path.length() << endl << path << endl;


    return 0;
}