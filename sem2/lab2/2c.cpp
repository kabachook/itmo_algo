#include<iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> g;
vector<int> color;

bool dfs_visit(int v, int v_color) {
//    cerr << "Visiting " << v + 1 << " Color " << v_color << endl;
    color[v] = v_color;

    for (auto to: g[v]) {
        if (color[to] == -1) {
            if (!dfs_visit(to, !v_color)) return false;
        } else if (color[to] == v_color) return false;
    }
    return true;
}


bool bipartite() {
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            if (!dfs_visit(i, 0)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);

    int m;
    cin >> n >> m;

    g = vector<vector<int>>(n, vector<int>());
    color = vector<int>(n, -1);

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        g[from - 1].push_back(to - 1);
        g[to - 1].push_back(from-1);
    }


    cout << (bipartite() ? "YES" : "NO");

    return 0;
}