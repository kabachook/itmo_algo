#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const long double INF = 100000000;

long double dist(const pair<int, int>& c1, const pair<int, int>& c2) {
    return pow(pow(c1.first - c2.first, 2) + pow(c1.second - c2.second, 2), 0.5);
}

int main() {
    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);

    int n;
    vector<pair<int, int>> v;

    cin >> n;
    v.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    vector<bool> used(n, false);
    vector<long double> min_e(n, INF);
    vector<int> sel_e(n, -1);
    min_e[0] = 0;

    long double ans = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (u == -1 || min_e[j] < min_e[u])) {
                u = j;
            }
        }

        used[u] = true;
        if (sel_e[u] != -1) ans += dist(v[u], v[sel_e[u]]);

        for (int to = 0; to < n; ++to) {
            long double cost = dist(v[u], v[to]);
            if (!used[to] && (cost < min_e[to])) {
                min_e[to] = cost;
                sel_e[to] = u;
            }
        }
    }

    cout << setprecision(20) << ans;
}