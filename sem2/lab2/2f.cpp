#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> v, v_t;
    int distance = 0;
    bool visited = false, leaf = false, freeze = false;
};

int n;
vector<Node> g;
vector<bool> used;
vector<int> order;


void bfs_leafs(vector<int> leafs) {
    queue<int> q;

    for (auto u: leafs) {
        g[u].visited = true;
        q.push(u);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v: g[u].v_t) {
            if (g[u].leaf) {
                g[v].distance = g[u].distance + 1;
                g[v].freeze = true;
            } else if (!g[v].freeze) g[v].distance = max(g[u].distance + 1, g[v].distance);

            if (!g[v].visited) {
                q.push(v);
            }
            g[v].visited = true;
        }
    }
}

void game(int s) {
    vector<int> leafs;

    for (int i = 0; i < n; ++i) {
        if (g[i].v.empty()) {
            g[i].leaf = true;
            leafs.push_back(i);
        }
    }

    bfs_leafs(leafs);

    if (g[s].distance % 2 == 1) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    int m, s;
    cin >> n >> m >> s;

    g = vector<Node>(n, Node());

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        g[from - 1].v.push_back(to - 1);
        g[to - 1].v_t.push_back(from - 1);
    }


    game(s - 1);

    return 0;
}