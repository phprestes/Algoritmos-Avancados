/*
 * Problema: Fluxo Máximo em Redes
 * Técnica/Algoritmo: Algoritmo de Ford-Fulkerson (com Edmonds-Karp/BFS)
 */
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

bool bfs(vector<vector<int>>& grafo, int n, int s, int t, vector<int>& pai) {
    vector<bool> visitado(n, false);
    queue<int> q;
    q.push(s);
    visitado[s] = true;
    pai[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (!visitado[v] && grafo[u][v] > 0) {
                if (v == t) {
                    pai[v] = u;
                    return true;
                }
                q.push(v);
                pai[v] = u;
                visitado[v] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>>& grafo, int n, int s, int t) {
    vector<vector<int>> residuo = grafo;
    vector<int> pai(n);
    int fluxo = 0;
    
    while (bfs(residuo, n, s, t, pai)) {
        int fluxo_temp = INT_MAX;
        
        // Encontra o fluxo mínimo no caminho
        for (int v = t; v != s; v = pai[v]) {
            int u = pai[v];
            fluxo_temp = min(fluxo_temp, residuo[u][v]);
        }

        // Atualiza as capacidades residuais
        for (int v = t; v != s; v = pai[v]) {
            int u = pai[v];
            residuo[u][v] -= fluxo_temp;
            residuo[v][u] += fluxo_temp;
        }

        fluxo += fluxo_temp;
    }
    return fluxo;
}

int main(void) {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grafo(n, vector<int>(n, 0));
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        grafo[a-1][b-1] = c;
    }
    
    int fonte = 0;
    int sorvedouro = n-1;
    
    int fluxo_maximo = fordFulkerson(grafo, n, fonte, sorvedouro);
    cout << fluxo_maximo << endl;
    
    return 0;
}