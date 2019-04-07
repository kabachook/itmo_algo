#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream in("pathmgep.in");
ofstream out("pathmgep.out");

const long long INF = 1000000000000;
vector<long long> d;
vector<bool> used;
vector<bool> in_queue;
int q_size = 0;

int extract_min() {
    int u;
    long long dist = INF;
    for (int i = 0; i < d.size(); i++)
        if (!used[i] && d[i] < dist) {
            u = i;
            dist = d[i];
        }
    used[u] = true;
    in_queue[u] = false;
    q_size--;
    return u;
}

void relax(int u, pair<long long, int> e) {
    if (d[e.second] > d[u] + e.first) {
        d[e.second] = d[u] + e.first;
        if (!in_queue[e.second]) {
            in_queue[e.second] = true;
            q_size++;
        }
    }
}

int main() {
    int n, s, f;
    in >> n >> s >> f;
    s--;
    f--;

    vector<vector<pair<long long, int>>> g(n);

    long long w;
    pair<long long, int> temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> w;
            if (i != j && w != -1)
                g[i].emplace_back(w, j);
        }
    }

    d.assign(n, INF);
    used.assign(n, false);
    in_queue.assign(n, false);

    d[s] = 0;
    in_queue[s] = true;
    q_size++;

    while (q_size) {
        int u = extract_min();
        for (auto e : g[u])
            relax(u, e);
    }

    if (d[f] == INF)
        out << -1;
    else
        out << d[f];
    return 0;
}