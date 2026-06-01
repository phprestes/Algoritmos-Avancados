/*
 * Problema: Contagem e Soma de Prefixos
 * Técnica/Algoritmo: Fenwick Tree (Binary Indexed Tree / BIT)
 */
#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class BIT {
    vector<int> bit;
    int n;
    const int MOD = 1e9 + 7;

public:
    BIT (int n) : n(n) {
        bit.assign(n + 1, 0);
    }
    
    void update (int index, int val) {
        while (index <= n) {
            bit[index] = (bit[index] + val) % MOD;
            index += index & (-index);
        }
    }

    long long getSum (int index) {
        long long sum = 0;
        while (index > 0) {
            sum = (sum + bit[index]) % MOD;
            index -= index & (-index);
        }

        return sum;
    }
};

int main(void) {
    int n;
    cin >> n;
    vector<int> livros(n);
    for (int i = 0; i < n; i++) {
        cin >> livros[i];
    }

    set<int> vals;
    for (int l : livros) {
        vals.insert(l);
    }

    map<int, int> mapa;
    int curr = 1;
    for (int v : vals) {
        mapa[v] = curr++;
    }

    for (int i = 0; i < n; i++) {
        livros[i] = mapa[livros[i]];
    }

    BIT fenwick(n);
    for (int i = 0; i < n; i++) {
        fenwick.update(livros[i], 1 + fenwick.getSum(livros[i] - 1));
    }

    cout << fenwick.getSum(n) << '\n';
}