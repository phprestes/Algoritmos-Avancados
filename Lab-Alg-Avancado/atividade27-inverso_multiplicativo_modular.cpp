/*
 * Problema: Inverso Multiplicativo Modular
 * Técnica/Algoritmo: Algoritmo de Euclides Estendido
 */
#include <iostream>

using namespace std;

long long gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x_c, y_c;
    long long mdc = gcd(b, a % b, x_c, y_c);

    x = y_c;
    y = x_c - y_c * (a/b);
    return mdc;
}

int main (void) {
    int t;
    cin >> t;
    while (t--) {
        long long a, m;
        cin >> a >> m;
        long long x = 0, y = 0;

        long long d = gcd(a, m, x, y);

        if (d != 1) {
            cout << -1 << '\n';
            continue;
        } else {
            cout << (x % m + m) % m << '\n';
            continue;
        }
    }

    return 0;
}
