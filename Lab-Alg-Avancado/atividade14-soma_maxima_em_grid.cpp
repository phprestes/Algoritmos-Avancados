/*
 * Problema: Soma Máxima em Grid (Esquerda, Direita, Baixo)
 * Técnica/Algoritmo: Programação Dinâmica (2D)
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<long long>> dp(n, vector<long long>(m, -1));

    for (int i = 0; i < n; i++) {
        // Vetores temporários para a linha atual
        vector<long long> left_to_right(m, -1);
        vector<long long> right_to_left(m, -1);

        // 1ª Passagem: Esquerda para Direita
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == -1) continue;

            if (i == 0 && j == 0) {
                left_to_right[j] = grid[i][j];
                continue;
            }

            long long from_top = (i > 0) ? dp[i-1][j] : -1;
            long long from_left = (j > 0) ? left_to_right[j-1] : -1;

            if (from_top != -1 || from_left != -1) {
                left_to_right[j] = max(from_top, from_left) + grid[i][j];
            }
        }

        // 2ª Passagem: Direita para Esquerda (só faz sentido se não for a primeira linha, 
        // ou se o ponto de partida pudesse ser em qualquer lugar)
        for (int j = m - 1; j >= 0; j--) {
            if (grid[i][j] == -1) continue;
            
            // Só podemos ir para a esquerda se viemos de cima ou da direita
            long long from_top = (i > 0) ? dp[i-1][j] : -1;
            long long from_right = (j < m - 1) ? right_to_left[j+1] : -1;

            if (from_top != -1 || from_right != -1) {
                right_to_left[j] = max(from_top, from_right) + grid[i][j];
            }
        }

        // 3º Passo: Atualizar o DP fundindo o melhor dos dois caminhos
        for (int j = 0; j < m; j++) {
            if (i == 0) {
                dp[i][j] = left_to_right[j]; // Na primeira linha só dá pra ir pra direita
            } else {
                dp[i][j] = max(left_to_right[j], right_to_left[j]);
            }
        }
    }

    cout << dp[n-1][m-1] << endl;

    return 0;
}