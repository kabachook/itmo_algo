#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Node {
    int k = -1;
    bool visited = false;
    set<int> v;
};

void dfs_visit(vector<Node> &vertices, int v, int k){
    vertices[v].visited = true;
    vertices[v].k = k;

    for (auto u: vertices[v].v){
        if (!vertices[u].visited){
            dfs_visit(vertices, u, k);
        }
    }
}

int dfs(vector<Node> &vertices, int k) {
    for (int v = 0; v < vertices.size(); v++){
        if (!vertices[v].visited){
            dfs_visit(vertices, v, k);
            k++;
        }
    }
    return k;
}

int main() {
    freopen("components.in", "r", stdin);
    freopen("components.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<Node> vertices(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        vertices[a - 1].v.insert(b - 1);
        vertices[b - 1].v.insert(a - 1);
    }

    int k = dfs(vertices,1) - 1;


    cout << k << endl;
    for (auto v: vertices){
        cout << v.k << " ";
    }

    return 0;
}