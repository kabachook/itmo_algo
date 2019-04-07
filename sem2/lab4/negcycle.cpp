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

const long long INF = 1000000000;

struct Edge {
    long long from;
    long long to;
    long long cost;

    Edge(long long from, long long to, long long cost)
        : from(from), to(to), cost(cost) {}
};

int main() {
    // freopen("pathmgep.in", "r", stdin);
    // if (!getenv("DEBUG")) {
    //     freopen(NULL_DEVICE, "w", stderr);
    //     freopen("pathmgep.out", "w", stdout);
    // }

    ifstream in("negcycle.in");
    ofstream out("negcycle.out");

    int n;
    in >> n;

    // from-weight-to
    vector<Edge> g;

    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            long long w;
            in >> w;
            if (w == INF)
                continue;

            g.emplace_back(i, j, w);
        }
    }

    vector<long long> d(n, 0), p(n, -1);

    long long last;
    for (long long i = 0; i < n; ++i) {
        last = -1;
        for (auto edge : g) {
            if (d[edge.to] > d[edge.from] + edge.cost) {
                d[edge.to] = max(-INF - 1, d[edge.from] + edge.cost);
                p[edge.to] = edge.from;
                last = edge.to;
            }
        }
    }

    if (last == -1) {
        out << "NO";
        return 0;
    }

    for (long long i = 0; i < n; ++i) {
        last = p[last];
    }

    vector<long long> path;

    for (auto curr = last;; curr = p[curr]) {
        path.push_back(curr);
        if (curr == last && path.size() > 1)
            break;
    }

    reverse(path.begin(), path.end());

    out << "YES\n" << path.size() << '\n';

    for (auto x : path) {
        out << x + 1 << ' ';
    }

    in.close();
    out.close();

    return 0;
}
