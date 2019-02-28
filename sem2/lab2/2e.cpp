#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> g;
vector<bool> used;
vector<int> order;

void dfs_visit(int v) {
    used[v] = true;
    for (auto to: g[v]) {
        if (!used[to]) {
            dfs_visit(to);
        }
    }
    order.push_back(v);
}

void topsort() {
    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs_visit(i);
    }
    reverse(order.begin(), order.end());
}


bool is_edge(int from, int to) {
    for (auto u: g[from]) {
        if (u == to) return true;
    }
    return false;
}

int main() {
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);

    int m;
    cin >> n >> m;

    g = vector<vector<int>>(n, vector<int>());
    used = vector<bool>(n, false);

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        g[from - 1].push_back(to - 1);
    }


    topsort();

    // Check path
    bool path_exists = true;

    for (int i = 1; i < n; i++) {
        if (!is_edge(order[i - 1], order[i])) {
            path_exists = false;
            break;
        }
    }

    cout << (path_exists ? "YES" : "NO");

    return 0;
}