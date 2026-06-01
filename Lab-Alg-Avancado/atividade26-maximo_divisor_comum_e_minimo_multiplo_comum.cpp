/*
 * Problema: Máximo Divisor Comum e Mínimo Múltiplo Comum
 * Técnica/Algoritmo: Algoritmo de Euclides (MDC / GCD) e Fórmula do MMC (LCM)
 */
#include <iostream>

using namespace std;

int main (void) {
    int t;
    cin >> t;
    while (t--) {
        long long a, b;
        cin >> a >> b;
        long long m = a * b;

        while (b) {
            a %= b;
            swap(a, b);
        }

        cout << a << ' ' << m/a << '\n';
    }

    return 0;
}
