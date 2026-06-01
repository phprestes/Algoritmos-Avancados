/*
 * Problema: Árvore Geradora Mínima (MST) com Restrições
 * Técnica/Algoritmo: Algoritmo de Kruskal (com Union-Find)
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

#define dist(a, b) (double)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y))

class DSU {
    vector<int> parent, rank;

public:
    DSU (int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int find (int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    void unite (int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else parent[s2] = s1, rank[s1]++;
        }
    }
};

typedef struct _predio {
    int x;
    int y;
} PREDIO;

typedef struct _aresta {
    int a;
    int b;
    double d;
} ARESTA;

int main(void) {
    int n;
    cin >> n;
    vector<PREDIO> predios(n);

    for (int i = 0; i < n; i++) {
        cin >> predios[i].x >> predios[i].y;
    }

    int m;
    cin >> m;

    vector<vector<bool>> gratis(n, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        gratis[u][v] = gratis[v][u] = true;
    }

    DSU dsu(n);
    vector<ARESTA> ligacoes;
    int arestas_na_mst = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!gratis[i][j]) {
                double d = dist(predios[i], predios[j]);
                ligacoes.push_back({i, j, d});
            } else {
                dsu.unite(i, j);
                arestas_na_mst++;
            }
        }
    }

    sort(ligacoes.begin(), ligacoes.end(), [](ARESTA a, ARESTA b) {
        return a.d < b.d;
    });

    double custo = 0;
    for (int i = 0; i < ligacoes.size(); i++) {
        int a = ligacoes[i].a, b = ligacoes[i].b, d = ligacoes[i].d;
        if (dsu.find(a) != dsu.find(b)) {
            dsu.unite(a, b);
            custo += sqrt(d);
            arestas_na_mst++;

            if (arestas_na_mst == n - 1) break;
        }
    }

    cout << fixed << setprecision(3) << custo << endl;
    return 0;
}