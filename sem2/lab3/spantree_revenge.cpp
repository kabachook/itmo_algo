#include <iostream>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#define NULL_DEVICE "NUL:"
#else
#define NULL_DEVICE "/dev/null"
#endif

using namespace std;


struct DSU {
    vector<size_t> parent;

    DSU(size_t v) {
        this->parent.resize(v);
        for (size_t i = 0; i < v; ++i) {
            this->parent[i] = i;
        }
    }

    size_t find_set(size_t v) {
        if (v == this->parent[v]) return v;
        return this->parent[v] = find_set(this->parent[v]);
    }

    void union_sets(size_t a, size_t b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            this->parent[b] = a;
    }
};


size_t n, m;
vector<pair<size_t, pair<size_t, size_t >>> g; // w - b - e

int main() {
    if (!getenv("DEBUG")) {
        freopen(NULL_DEVICE, "w", stderr);
    }

    freopen("spantree2.in", "r", stdin);
    freopen("spantree2.out", "w", stdout);

    cin >> n >> m;
    g.resize(m);

    for (size_t i = 0; i < m; ++i) {
        cin >> g[i].second.first >> g[i].second.second >> g[i].first;
        g[i].second.first--;
        g[i].second.second--;
    }

    sort(g.begin(), g.end());

    vector<pair<size_t, size_t >> mst;
    size_t ans = 0;
    auto dsu = DSU(n);

    for (auto &e: g) {
        auto beg = e.second.first, end = e.second.second, cost = e.first;
        if (dsu.find_set(beg) != dsu.find_set(end)) {
            mst.push_back(e.second);
            ans += cost;
            cerr << "Added " << cost << endl;
            dsu.union_sets(beg, end);
        }
    }


    cout << ans;

    return 0;
}