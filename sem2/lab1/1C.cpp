#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<vector<bool>> matrix(n, vector<bool>(n));

    bool parallel = false;

    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        if (matrix[a-1][b-1] || matrix[b-1][a-1]) {
            parallel = true;
            break;
        }
        matrix[a-1][b-1] = true;
    }


    cout << (parallel ? "YES" : "NO") << endl;

    return 0;
}