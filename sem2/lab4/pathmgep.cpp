#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>

#ifdef _WIN32
#define NULL_DEVICE "NUL:"
#else
#define NULL_DEVICE "/dev/null"
#endif
using namespace std;

const long long INF = 1000000000000L;

long long dj(vector<vector<long long>> g, long long source, long long dest) {
    long long n = g.size();

    vector<long long> d(n, INF);
    d[source] = 0;

    vector<bool> seen(n, false);

    for (long long i = 0; i < n; ++i) {
        long long u = -1;
        for (long long j = 0; j < n; ++j) {
            if (!seen[j] && (u == -1 || d[j] < d[u])) {
                u = j;
            }
        }

        if (d[u] == INT_MAX)
            break;

        seen[u] = true;
        for (long long to = 0; to < n; ++to) {
            if (g[u][to] == -1 || u == to) {
                continue;
            }

            d[to] = min(d[to], d[u] + g[u][to]);
        }
    }

    return d[dest];
}

signed main() {
    // freopen("pathmgep.in", "r", stdin);
    // if (!getenv("DEBUG")) {                         // ZLOOOO
    //     freopen(NULL_DEVICE, "w", stderr);
    //     freopen("pathmgep.out", "w", stdout);
    // }
    ifstream in("pathmgep.in");
    ofstream out("pathmgep.out");

    long long n, source, dest;
    in >> n >> source >> dest;
    source--;
    dest--;

    vector<vector<long long>> g(n, vector<long long>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> g[i][j];
        }
    }

    auto ans = dj(g, source, dest);

    out << ((ans == INF) ? -1 : ans);

    return 0;
}