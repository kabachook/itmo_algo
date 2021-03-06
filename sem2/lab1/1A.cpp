#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<vector<bool>> matrix(n, vector<bool>(n));

    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        matrix[a-1][b-1] = true;
     }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
             cout << matrix[i][j];
             if (j != n - 1){
                 cout << " ";
             }
        }
        cout << endl;
    }

    return 0;
}