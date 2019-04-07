#include <algorithm>
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

// from -> (to,w)
vector<vector<pair<long long, long long>>> edges;

void dfs_visit(vector<vector<pair<long long, long long>>> &graph,
               vector<bool> &visited, long long v) {
    visited[v] = true;
    for (auto &to : graph[v]) {
        if (!visited[to.first]) {
            dfs_visit(graph, visited, to.first);
        }
    }
}

bool dfs(vector<vector<pair<long long, long long>>> &graph, long long root) {
    vector<bool> visited(graph.size(), false);
    dfs_visit(graph, visited, root);

    for (const auto &t : visited) {
        if (t == false)
            return false;
    }
    return true;
}

void dfs_visit_order(vector<vector<pair<long long, long long>>> &graph,
                     vector<bool> &visited, long long v,
                     vector<long long> &order) {
    visited[v] = true;
    for (auto &to : graph[v]) {
        if (!visited[to.first]) {
            dfs_visit_order(graph, visited, to.first, order);
        }
    }
    order.push_back(v);
}

void dfs_order(vector<vector<pair<long long, long long>>> &graph,
               vector<bool> &visited, long long v, vector<long long> &order) {
    for (long long i = 0; i < graph.size(); ++i) {
        if (!visited[i])
            dfs_visit_order(graph, visited, i, order);
    }
}

void dfs_visit_component(vector<vector<pair<long long, long long>>> &graph,
                         vector<bool> &visited, long long v,
                         vector<long long> &component) {
    visited[v] = true;
    component.push_back(v);
    for (auto &to : graph[v]) {
        if (!visited[to.first]) {
            dfs_visit_component(graph, visited, to.first, component);
        }
    }
}

void dfs_component(vector<vector<pair<long long, long long>>> &graph,
                   vector<bool> &visited, long long v,
                   vector<long long> &result) {
    vector<long long> component;
    long long k = 0;

    for (long long i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            dfs_visit_component(graph, visited, i, component);
            for (const auto v : component) {
                result[v] = k;
            }
            component.clear();
            ++k;
        }
    }
}

pair<vector<long long>, long long>
condensate(vector<vector<pair<long long, long long>>> graph) {
    long long n = graph.size();
    vector<bool> visited(n, false);
    vector<long long> order;

    for (long long v = 0; v < n; ++v) {
        if (!visited[v])
            dfs_visit_order(graph, visited, v, order);
    }
    visited.assign(n, false);

    vector<vector<pair<long long, long long>>> graph_t(n);
    for (long long from = 0; from < n; ++from) {
        for (auto &edge : graph[from]) {
            graph_t[edge.first].emplace_back(from, edge.second);
        }
    }

    vector<long long> component(n), temp;
    long long k = 0;

    for (long long i = 0; i < n; ++i) {
        long long v = order[n - i - 1];
        if (!visited[v]) {
            dfs_visit_component(graph_t, visited, v, temp);

            for (const auto v : temp) {
                component[v] = k;
            }
            temp.clear();
            ++k;
        }
    }

    return {component, k};
};

long long findDMST(vector<vector<pair<long long, long long>>> &g, long long n_v,
                   long long root) {
    long long res = 0;
    vector<long long> min_edge(n_v, INT64_MAX);

    for (long long from = 0; from < n_v; ++from) {
        for (auto &edge : g[from]) {
            min_edge[edge.first] = min(edge.second, min_edge[edge.first]);
        }
    }

    for (long long v = 0; v < n_v; ++v) {
        if (v == root)
            continue;
        res += min_edge[v];
    }

    vector<vector<pair<long long, long long>>> zero_edges(n_v);

    for (long long from = 0; from < n_v; ++from) {
        for (auto &edge : g[from]) {
            if (edge.second == min_edge[edge.first])
                zero_edges[from].emplace_back(edge.first, edge.second);
        }
    }

    if (dfs(zero_edges, root))
        return res;

    auto cond_res = condensate(zero_edges);
    auto new_components = cond_res.first;
    auto k = cond_res.second;

    vector<vector<pair<long long, long long>>> new_edges(k);
    for (long long from = 0; from < n_v; ++from) {
        for (auto &edge : g[from]) {
            if (new_components[from] != new_components[edge.first]) {
                // Make new graph with comp == vertex
                new_edges[new_components[from]].emplace_back(
                    new_components[edge.first],
                    edge.second - min_edge[edge.first]);
            }
        }
    }

    res += findDMST(new_edges, new_edges.size(), new_components[root]);
    return res;
}

signed main() {
    freopen("chinese.in", "r", stdin);
    if (!getenv("DEBUG")) {
        freopen(NULL_DEVICE, "w", stderr);
        freopen("chinese.out", "w", stdout);
    }

    long long n, m;
    cin >> n >> m;

    edges.assign(n, vector<pair<long long, long long>>());

    for (long long i = 0; i < m; ++i) {
        long long beg, end, w;
        cin >> beg >> end >> w;
        beg--;
        end--;
        edges[beg].emplace_back(end, w);
    }

    bool connected = dfs(edges, 0);

    if (!connected) {
        cout << "NO";
        return 0;
    }

    auto ans = findDMST(edges, n, 0);
    if (ans == INT64_MAX) {
        cout << "NO";
    } else {
        cout << "YES\n" << ans;
    }

    return 0;
}