#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <unordered_set>

#ifdef _WIN32
#define NULL_DEVICE "NUL:"
#else
#define NULL_DEVICE "/dev/null"
#endif

using namespace std;

const long double INF = 1000000000;
int n;
vector<pair<int, int>> coords;
vector<bool> used;
vector<long double> min_e;

long double dist(const pair<int, int> &c1, const pair<int, int> &c2) {
    return pow(pow(c1.first - c2.first, 2) + pow(c1.second - c2.second, 2), 0.5);
}

int extract_min() {
    auto m = INF;
    int u = -1;
    for (int i = 0; i < n; ++i) {
        if (!used[i] && (min_e[i] < m)) {
            m = min_e[i];
            u = i;
        }
    }
    used[u] = true;
    return u;
}

int main() {
    if (!getenv("DEBUG")) {
        freopen(NULL_DEVICE, "w", stderr);
    }

    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);

    cin >> n;
    coords.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> coords[i].first >> coords[i].second;
    }

    used.assign(n, false);
    min_e.assign(n, INF);
    min_e[0] = 0;

    long double ans = 0;

    for (int i = 0; i < n; ++i) { // O(n)
        auto v = extract_min(); // O(n)
        for (int u = 0; u < n; ++u) { // O(n)
            auto cost = dist(coords[v], coords[u]);
            if (!used[u] && cost < min_e[u]) min_e[u] = cost;
        }
    } // == O(n^2)

    for (auto &x:min_e) {
        ans += x;
    }

    cout << setprecision(20) << ans;
    return 0;
}