/*
 * Problema: Busca e Manipulação de Matrizes (Bounding Box)
 * Técnica/Algoritmo: Algoritmo Guloso / Varredura de Matriz
 */
#include <iostream>
#include <climits>
using namespace std;

int main(void) {
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        int h = 0, l_min = INT_MAX, l_max = 0;
        char parede[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> parede[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (parede[i][j] == 'B') {
                    if (h == 0)
                        h = n - i;
                    l_min = min(j, l_min);
                    l_max = max(j, l_max);
                }
            }
        }

        if (h == 0) {
            l_max = -1;
            l_min = 0;
        }

        // cout << l_max << ' ' << l_min << endl;
        cout << h << ' ' << l_max - l_min + 1 << endl;
    }
}