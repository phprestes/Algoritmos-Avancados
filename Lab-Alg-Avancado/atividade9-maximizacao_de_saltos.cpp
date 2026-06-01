/*
 * Problema: Maximização de Saltos (Variante do Knapsack/Frog)
 * Técnica/Algoritmo: Programação Dinâmica (1D)
 */
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }
    vector<int> dp(n);
    dp[0] = prices[0];
    dp[1] = max(prices[1], 2*dp[0]);
    for (int i = 1; i < n; i++) {
        dp[i] = prices[i];
        for (int j = 0; j < i; j++)
            dp[i] = max(dp[i], dp[j] + dp[i - j - 1]);
    }
    cout << dp[n-1] << endl;
}