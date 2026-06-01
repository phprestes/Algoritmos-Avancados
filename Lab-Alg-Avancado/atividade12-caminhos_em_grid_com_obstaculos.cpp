/*
 * Problema: Caminhos em Grid com Obstáculos
 * Técnica/Algoritmo: Programação Dinâmica (2D)
 */
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int MOD = 1e9 + 7;

int main(void) {
    int n;
    cin >> n;
    vector<vector<char>> m(n, vector<char>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }

    if (m[0][0] == '*' || m[n-1][n-1] == '*') {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] != '*') {
                if (i > 0) dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
                if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
            }
        }
    }
    cout << dp[n-1][n-1] % MOD << endl;

    return 0;
}