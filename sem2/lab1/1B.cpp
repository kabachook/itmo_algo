#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;

    vector<vector<bool>> matrix(n, vector<bool>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            if (a == 1) matrix[i][j] = true;
        }
    }

    bool undirected = true;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if ((matrix[i][j] != matrix[j][i]) || (i == j && matrix[i][j] == 1)){
                undirected = false;
                break;
            }
        }
    }

    cout << (undirected ? "YES" : "NO") << endl;

    return 0;
}