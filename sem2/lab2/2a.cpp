#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> g;
vector<char> color;
vector<int> order;

bool dfs_visit(int v) {
//    cerr << "Visiting " << v + 1 << endl;
    color[v] = 'g';
    for (auto to: g[v]) {
        if (color[to] == 'w') {
            if (!dfs_visit(to)){
                return false;
            };
        }
        else if (color[to] == 'g'){
            return false;
        }
    }
    color[v] = 'b';
//    cerr << " Pushing " << v + 1 << endl;
    order.push_back(v);
    return true;
}

bool topsort() {
    bool success = true;
    for (int i = 0; i < n; i++) {
        if (!success) return false;
        if (color[i] == 'w')
            success = dfs_visit(i);
    }
    return success;
}


int main() {
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);

    int m;
    cin >> n >> m;

    g = vector<vector<int>>(n, vector<int>());
    color = vector<char>(n, 'w');

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        g[from - 1].push_back(to - 1);
    }


    bool success = topsort();

    if (success) {
        reverse(order.begin(), order.end());
        for (auto v: order) {
            cout << v + 1 << " ";
        }
    } else {
        cout << -1;
    }

    return 0;
}