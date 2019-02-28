#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> g;
vector<char> color;
vector<int> part;
int cycle_start, cycle_end;

bool dfs_visit(int v) {
    color[v] = 'g';
    for (auto to: g[v]) {
        if (color[to] == 'w') {
            part[to] = v;
            if (dfs_visit(to)) return true;
        } else if (color[to] == 'g') {
            cycle_start = to;
            cycle_end = v;
            return true;
        }
    }
    color[v] = 'b';
    return false;
}

bool find_cycle() {
    for (int i = 0; i < n; i++) {
        if (dfs_visit(i)) {
            return true;
        }
    }
    return false;
}

int main() {
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);

    int m;
    cin >> n >> m;

    g = vector<vector<int>>(n, vector<int>());
    color = vector<char>(n, 'w');
    part = vector<int>(n, -1);

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        g[from - 1].push_back(to - 1);
    }


    bool cycle = find_cycle();

    if (cycle) {
        cout << "YES" << "\n";
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = part[v]) {
            cycle.push_back(v);
        }
        reverse(cycle.begin(), cycle.end());
        for (auto v: cycle) {
            cout << v + 1 << ' ';
        }
    } else {
        cout << "NO";
    }

    return 0;
}