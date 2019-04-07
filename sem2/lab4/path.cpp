#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <map>
#include <queue>
#include <set>
#include <vector>

#ifdef _WIN32
#define NULL_DEVICE "NUL:"
#else
#define NULL_DEVICE "/dev/null"
#endif

using namespace std;

typedef long long ll;

const long long LIM = 1e15;
const long long INF = INT64_MAX / 2;

struct Edge {
    size_t to;
    ll w;

    Edge(size_t to, ll w) : to(to), w(w) {}
};

#define __max(a, b) ((a) > (b) ? (a) : (b))

vector<vector<Edge>> g;
vector<ll> d;
vector<bool> cycle;

void relax(size_t u, Edge &e) {
    if (d[e.to] > d[u] + e.w && d[u] < INF) {
        // d[e.to] = __max(-INT64_MAX, d[u] + e.w);
        d[e.to] = d[u] + e.w;
    }
}

void dfs(int u) {
    cycle[u] = true;
    for (auto &e : g[u])
        if (!cycle[e.to])
            dfs(e.to);
}

int main() {
    // freopen("pathmgep.in", "r", stdin);
    // if (!getenv("DEBUG")) {
    //     freopen(NULL_DEVICE, "w", stderr);
    //     freopen("pathmgep.out", "w", stdout);
    // }

    ifstream in("path.in");
    ofstream out("path.out");

    size_t n, m, s;
    in >> n >> m >> s;
    s--;

    g.resize(n);
    d.assign(n, INF);
    cycle.assign(n, false);
    d[s] = 0;

    for (size_t i = 0; i < m; ++i) {
        size_t from, to;
        ll w;
        in >> from >> to >> w;
        g[from - 1].emplace_back(to - 1, w);
    }

    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (auto &e : g[j]) {
                relax(j, e);
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (auto &e : g[i]) {
            if (d[e.to] > d[i] + e.w && !cycle[e.to] && d[i] < INF) {
                dfs(e.to);
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (d[i] == INF) {
            out << "*\n";
        } else if (cycle[i] || d[i] < -INF) {
            out << "-\n";
        } else {
            out << d[i] << "\n";
        }
    }

    in.close();
    out.close();

    return 0;
}