#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct Node {
    bool visited = false;
    int distance = 0;
    set<int> v;
};

void bfs(vector<Node> &vertices, int s){
    vertices[s].visited = true;
    queue<int> q;
    q.push(s);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for (auto v: vertices[u].v){
            if (!vertices[v].visited){
                vertices[v].visited = true;
                vertices[v].distance = vertices[u].distance + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    freopen("pathbge1.in", "r", stdin);
    freopen("pathbge1.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<Node> vertices(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        vertices[a - 1].v.insert(b - 1);
        vertices[b - 1].v.insert(a - 1);
    }

    bfs(vertices, 0);

    for (auto v: vertices){
        cout << v.distance << " ";
    }

    return 0;
}