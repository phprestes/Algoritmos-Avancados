/*
 * Problema: Contagem e Divisibilidade (Múltiplos de 3, 5 e 15)
 * Técnica/Algoritmo: Princípio da Inclusão-Exclusão
 */
#include <iostream>

using namespace std;

int main (void) {
    int n;
    cin >> n;
    cout << n/3 << ' ' << n/5 << ' ' << n/15 << '\n';
    return 0;
}