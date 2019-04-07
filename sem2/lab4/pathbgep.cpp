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

const long long INF = 1000000000000L;

int main() {
    // freopen("pathmgep.in", "r", stdin);
    // if (!getenv("DEBUG")) {
    //     freopen(NULL_DEVICE, "w", stderr);
    //     freopen("pathmgep.out", "w", stdout);
    // }

    ifstream in("pathbgep.in");
    ofstream out("pathbgep.out");

    int n, m;
    in >> n >> m;

    // from-weight-to
    vector<vector<pair<long long, int>>> g(n);

    for (int i = 0; i < m; ++i) {
        int from, to;
        long long w;
        in >> from >> to >> w;

        if (from == to)
            continue;

        g[from - 1].emplace_back(w, to - 1);
        g[to - 1].emplace_back(w, from - 1);
    }

    vector<long long> d(n, INF);
    d[0] = 0;

    set<pair<long long, int>> q;
    q.emplace(0, 0);

    while (!q.empty()) {
        int from = q.begin()->second;
        q.erase(q.begin());

        for (auto &edge : g[from]) {
            long long w = edge.first;
            int to = edge.second;

            if (d[from] + w < d[to]) {
                q.erase({d[to], to});
                d[to] = d[from] + w;
                q.emplace(d[to], to);
            }
        }
    }

    for (int i = 0; i < n; i++)
        out << d[i] << ' ';

    in.close();
    out.close();

    return 0;
}
