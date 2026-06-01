/*
 * Problema: Maximização de Pontos com Intervalos Adjacentes
 * Técnica/Algoritmo: Programação Dinâmica em Intervalos (2D)
 */
#include <iostream>

using namespace std;

int main(void) {
    int x;
    cin >> x;
    while(x--) {
        int n;
        cin >> n;

        int points[n];
        int dp[n][n];
        int total = 0;

        for (int i = 0; i < n; i++) {
            int a, b;
            scanf(" (%d, %d)", &a, &b);
            points[i] = a + b;
            dp[i][i] = points[i];
            total += points[i];
        }

        for (int length = 1; length < n; length++) {
            for (int i = 0; i + length < n; i++) {
                int j = i + length;
                dp[i][j] = max(points[i] - dp[i+1][j], points[j] - dp[i][j-1]);
                dp[j][i] = dp[i][j];
            }
        }

        cout << (total + dp[0][n-1]) / 2 << endl;
    }

    return 0;
}