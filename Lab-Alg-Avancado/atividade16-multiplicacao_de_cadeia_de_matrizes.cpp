/*
 * Problema: Multiplicação de Cadeia de Matrizes (Variante Burst Balloons)
 * Técnica/Algoritmo: Programação Dinâmica em Intervalos (2D)
 */
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    vector<int> balloons(n+2, 1);
    balloons[0] = 1;
    balloons[n+1] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> balloons[i];
    }

    vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            for (int k = i; k <= j; k++) {
                int current = dp[i][k-1] + dp[k+1][j] + (balloons[i-1] * balloons[k] * balloons[j+1]);
                dp[i][j] = max(current, dp[i][j]);
            }
        }
    } 

    cout << dp[1][n] << endl;

    return 0;
}