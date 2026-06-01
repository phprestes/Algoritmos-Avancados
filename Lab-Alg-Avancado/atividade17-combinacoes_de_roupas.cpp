/*
 * Problema: Combinações de Roupas
 * Técnica/Algoritmo: Programação Dinâmica com Bitmask
 */
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    const int MOD = 1e9 + 7;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> roupas(101);

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int blusa;
            cin >> blusa;
            roupas[blusa].push_back(i);
        }
    }

    int mask = 1 << n;
    vector<long long> dp(1 << n, 0);  
    dp[0] = 1;  
    for (int i = 0; i < 101; i++) {
        if (!roupas[i].empty()) {
            for (int j = mask - 1; j >= 0; j--) {
                if (dp[j] == 0) continue;
                for (int pessoa : roupas[i]) {
                    if (!(j & 1 << pessoa)) {
                        int next_mask = j | 1 << pessoa;
                        dp[next_mask] = (dp[j] + dp[next_mask]) % MOD;
                    }
                }
            }
        }
    }

    cout << dp[mask - 1] << endl;
}