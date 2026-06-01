/*
 * Problema: Mínimo de Pulos (Jump Game)
 * Técnica/Algoritmo: Programação Dinâmica (1D)
 */
#include <iostream>
#include <iterator>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    int jump[n];
    for (int i = 0; i < n; i++) {
        cin >> jump[i];
    }

    int dp[n];
    fill_n(dp, n, n+1);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j <= i+jump[i]; j++) {
            dp[j] = min(dp[j], dp[i] + 1);
        }
    }

    if (dp[n-1] != n+1) {
        cout << dp[n-1] << endl;
    } else
        cout << "Salto impossivel" << endl;
    return 0;
}