#include<iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> g;
vector<int> part;


bool bipartite() {
    bool bipart = true;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (part[i] == -1) {
            q.push(i);
            part[i] = 0;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int j = 0; j < g[v].size(); ++j) {
                    int to = g[v][j];
                    if (part[to] == -1) {
                        part[to] = !part[v];
                        q.push(to);
                    } else {
                        bipart &= part[to] != part[v];
                    }
                }
            }
        }
    }
    return bipart;
}

int main() {
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);

    int m;
    cin >> n >> m;

    g = vector<vector<int>>(n, vector<int>());
    part = vector<int>(n, -1);

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        g[from - 1].push_back(to - 1);
        g[to - 1].push_back(from - 1);
    }


    cout << (bipartite() ? "YES" : "NO");

    return 0;
}