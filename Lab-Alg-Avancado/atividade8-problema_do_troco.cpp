/*
 * Problema: Problema do Troco (Coin Change)
 * Técnica/Algoritmo: Programação Dinâmica (1D)
 */
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int t;
    cin >> t;
    while(t--) {
        int v, m;
        cin >> v >> m;
        vector<int> coin(m);
        for (int i = 0; i < m; i++)
            cin >> coin[i];
        vector<int> dp(v+1);
        for (int i = 0; i <= v; i++) {
            dp[i] = i;
            for (int j = 0; j < m && i >= coin[j]; j++) {
                dp[i] = min(dp[i], dp[i - coin[j]] + 1);
            }
        }
        cout << dp[v] << endl;
    }
}