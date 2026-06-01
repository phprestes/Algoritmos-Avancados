/*
 * Problema: Soma Máxima em Grid
 * Técnica/Algoritmo: Programação Dinâmica (2D)
 */
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<long long>> dp(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != -1) {
                if (i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                    continue;
                }
                int a = -1, b = -1;
                if (i > 0) a = dp[i-1][j];
                if (j > 0) b = dp[i][j-1];
                dp[i][j] = max(a, b);
                if (dp[i][j] != -1) dp[i][j] += grid[i][j];
            } else
                dp[i][j] = -1;
        }
    }

    // for (int i = 0; i < n; i++) {
    //     cout << endl;
    //     for (int j = 0; j < m; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    // }

    cout << dp[n-1][m-1] << endl;

    return 0;
}