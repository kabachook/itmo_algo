#include<iostream>
#include <vector>

using namespace std;

struct Node {
    vector<int> v, v_t;
    bool used = false, used_t = false;
    int k = -1;
};

int n, k = 1;
vector<Node> g;
vector<int> order;


void dfs_visit(int v) {
    g[v].used = true;
    for (auto u: g[v].v) {
        if (!g[u].used) {
            dfs_visit(u);
        }
    }
    order.push_back(v);
}

void dfs_visit_t(int v) {
    g[v].used_t = true;
    g[v].k = k;
    for (auto u: g[v].v_t) {
        if (!g[u].used_t) {
            dfs_visit_t(u);
        }
    }
}

void condensate() {
    for (int i = 0; i < n; i++) {
        if (!g[i].used) dfs_visit(i);
    }

    for (int i = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (!g[v].used_t) {
            dfs_visit_t(v);
            k++;
        }
    }
}

int main() {
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);

    int m;
    cin >> n >> m;

    g.assign(n, Node());

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        g[from - 1].v.push_back(to - 1);
        g[to - 1].v_t.push_back(from - 1);
    }

    condensate();

    cout << k - 1 << endl;

    for (auto v: g) {
        cout << v.k << " ";
    }

    return 0;
}