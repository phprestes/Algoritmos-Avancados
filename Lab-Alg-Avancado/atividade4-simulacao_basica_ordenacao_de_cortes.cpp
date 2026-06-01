/*
 * Problema: Simulação Básica / Ordenação de Cortes
 * Técnica/Algoritmo: Algoritmo Guloso com Ordenação
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int h;
    cin >> h;

    int n;
    vector<int> h_per_m;
    while(cin >> n) {
        h_per_m.push_back(n);
    }

    sort(h_per_m.begin(), h_per_m.end());
    int res = 0;
    int len =  h_per_m.size();
    for (res; res < len && h > 0; res++) {
        h -= h_per_m[len - res - 1];
    }

    if (h > 0)
        cout << "nao cresce" << endl;
    else
        cout << res << endl;

    return 0;
}