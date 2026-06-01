/*
 * Problema: Problema da Mochila 0-1 (Knapsack 0-1)
 * Técnica/Algoritmo: Programação Dinâmica (1D)
 */
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int n, x;
    cin >> n >> x;
    vector<pair<int, int>> books(n);
    for (int i = 0; i < n; i++)
        cin >> books[i].first;
    for (int i = 0; i < n; i++)
        cin >> books[i].second;

    vector<int> dp(x+1, 0);
    for (int i = 0; i <= n; i++) {
        for (int j = x; j >= books[i].first; j--) {
            dp[j] = max(dp[j], dp[j - books[i].first] + books[i].second);
        }
    }

    cout << dp[x] << endl;
}