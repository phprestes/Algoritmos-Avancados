/*
 * Problema: Componentes Fortemente Conexas (Conectividade Forte)
 * Técnica/Algoritmo: Algoritmo de Kosaraju (DFS Dupla)
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool dfs(vector<vector<int>>& cities) {
    stack<int> q;
    vector<bool> visitas(cities.size(), false);
    q.push(0);
    visitas[0] = true;
    while(!q.empty()) {
        int u = q.top();
        q.pop();
        for (int v : cities[u]) {
            if(!visitas[v]) {
                q.push(v);
                visitas[v] = true;
            }
        }
    }

    for (bool v : visitas) {
        if (!v) return false;
    }

    return true;
}

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> cities(n);
    vector<vector<int>> cities_rev(n);
    while(m--) {
        int a, b;
        cin >> a >> b;
        cities[a-1].push_back(b-1);
        cities_rev[b-1].push_back(a-1);
    }

    if (dfs(cities) && dfs(cities_rev))
        cout << "SIM" << endl;
    else
        cout << "NAO" << endl;

    return 0;
}