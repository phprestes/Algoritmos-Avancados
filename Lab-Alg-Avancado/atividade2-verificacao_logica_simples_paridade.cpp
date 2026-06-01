/*
 * Problema: Verificação Lógica Simples / Paridade
 * Técnica/Algoritmo: Estruturas Condicionais (Matemática Básica)
 */
#include <iostream>

using namespace std;

int main(void) {
    int t;
    cin >> t;
    while(t--) {
        int x, y;
        cin >> x >> y;
        if ((x == 0 && y % 2) || (x + 2*y) % 2)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }
    return 0;
}