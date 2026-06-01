/*
 * Problema: Inverso Multiplicativo Modular
 * Técnica/Algoritmo: Pequeno Teorema de Fermat e Exponenciação Modular Rápida
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool eh_primo(long long m) {
    if (m <= 1) return false;
    if (m <= 3) return true;
    if (m % 2 == 0 || m % 3 == 0) return false;

    for (long long i = 5; i*i <= m; i+=6)
        if (m % i == 0 || m % (i+2) == 0) return false;
    
    return true;
}

long long mul_m(long long a, long long b, long long p) {
    long long res = 0;
    a %= p;
    b %= p;

    while (b > 0) {
        if (b % 2) res = (res + a) % p;
        a = (a + a) % p;
        b /= 2;
    }
    return res;
}

long long pow_m(long long n, long long e, long long p) {
    if (e == 0)
        return 1;
    long long m = pow_m(n, e / 2, p);
    long long res = mul_m(m, m, p);
    return e % 2 ? mul_m(res, n, p) : res;
}

int main(void) {
    long long n, t;
    cin >> n >> t;
    long long p = n+1;
    for (p; ; p++) {
        if (eh_primo(p)) break;
    }
    // cout << p << endl;
    cout << pow_m(t, p-2, p) << endl;
    return 0;
}