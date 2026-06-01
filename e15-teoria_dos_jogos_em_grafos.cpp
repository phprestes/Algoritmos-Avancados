/*
 * Problema: Teoria dos Jogos em Grafos (Estratégia Vencedora)
 * Técnica/Algoritmo: Memoization (Programação Dinâmica Top-Down / DFS)
 */
#include <iostream>
#include <vector>

using namespace std;

int solve(vector<int>& memo, vector<vector<int>>& grafo, int u) {
    if (memo[u] != -1) return memo[u];

    bool venco = false;

    for (int v : grafo[u]) {
        if (!solve(memo, grafo, v)) {
            venco = true;
            break;
        }
    }

    return memo[u] = venco;
}

int main(void) {
    int x;
    cin >> x;
    while (x--) {
        int n, m, s;
        cin >> n >> m >> s;
        vector<vector<int>> grafo(n);
        vector<int> memo(n, -1); 

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            grafo[a].push_back(b);
        }

        if (solve(memo, grafo, s)) cout << "Ash" << endl;
        else cout << "Noir" << endl;
    }
    return 0;
}