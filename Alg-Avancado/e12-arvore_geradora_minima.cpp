/*
 * Problema: Árvore Geradora Mínima (Reconstrução de Pontes)
 * Técnica/Algoritmo: Algoritmo de Kruskal com Union-Find
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef struct aresta_ {
    int a;
    int b;
    int c;

    bool operator<(const aresta_& other) const {
        return c < other.c;
    }
} ARESTA;

class UnionFind {
private:
    vector<int> pais, peso;
public:
    int componentes;

    UnionFind(int n) {
        componentes = n;
        pais.resize(n);
        peso.resize(n);
        for (int i = 0; i < n; i++) {
            pais[i] = i;
            peso[i] = 1;
        }
    }

    int find(int x) {
        if (pais[x] != x)
            pais[x] = find(pais[x]);
        return pais[x];
    }

    bool join(int x, int y) {
        x = find(x);
        y = find(y);

        if (x != y) {
            if (peso[x] < peso[y]) pais[x] = y;
            else if (peso[x] > peso[y]) pais[y] = x;
            else {
                pais[x] = y;
                peso[y]++;
            }
            componentes--;
            return true;
        }
        return false;
    }
};

int main(void) {
    int x;
    cin >> x;
    while (x--) {
        int n, m;
        cin >> n >> m;
        vector<ARESTA> pontes;
        set<int> custos;
        bool duplicado = false;
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            a--;
            b--;

            if (custos.count(c)) duplicado = true;
            custos.insert(c);
            pontes.push_back({a,b,c});
        }

        if (duplicado) {
            cout << "Esse nao e o caminho correto para a Cidade Perdida de Z.\n" << endl;
            continue;
        }

        sort(pontes.begin(), pontes.end());
        UnionFind uf(n);
        long long custofinal = 0;
        vector<ARESTA> pontes_final;
        for (auto p : pontes) {
            if (uf.join(p.a, p.b)) {
                custofinal += p.c;
                pontes_final.push_back(p);
            }
        }

        if (n > 0 && uf.componentes > 1) {
            cout << "O vale nao pode ser completamente atravessado." << endl;
        } else {
            cout << "Custo minimo: " << custofinal << endl;
            cout << "Pontes reconstruidas:" << endl;
            for (auto p : pontes_final) {
                int a = p.a;
                int b = p.b;
                if (a > b) swap(a,b);
                cout << a+1 << " - " << b+1 << endl;
            }
        }
        cout << endl;
    }
    return 0;
}