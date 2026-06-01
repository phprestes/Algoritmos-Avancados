/*
 * Problema: Maximização de Lucro (Garimpo)
 * Técnica/Algoritmo: Programação Dinâmica com Máquina de Estados
 */
#include <iostream>

using namespace std;

int main(void) {
    int x;
    cin >> x;
    while(x--) {
        int dim_init, n;
        cin >> dim_init >> n;
        int val[n];
        for (int i = 0; i < n; i++) cin >> val[i];

        int dp[n+1][3]; // estado 0 tenho nada estado 1 tenho garimpo estado 2 to descansando
        dp[0][0] = dim_init;
        dp[0][1] = -100000;
        dp[0][2] = -100000;

        for (int i = 1; i <= n; i++) {
            // posso nn fazer nada ou comprar o troço
            dp[i][0] = max(dp[i-1][0], dp[i-1][2]);
            dp[i][1] = dp[i-1][0] - val[i-1];
            
            // posso nn fazer nada ou garimpar
            dp[i][1] = max(dp[i][1], dp[i-1][1]);
            dp[i][2] = dp[i-1][1] + val[i-1];
        }

        cout << max(max(dp[n][0], dp[n][1]), dp[n][2]) << endl;
    }
}