/*
 * Problema: Contagem de Componentes Conexas (Átomos/Moléculas)
 * Técnica/Algoritmo: Busca em Profundidade (DFS) com Pilha (Stack) em Grafo Não Direcionado
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(void) {
    int x;
    cin >> x;
    while(x--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> atomos(n);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            atomos[a].push_back(b);
            atomos[b].push_back(a);
        }

        vector<bool> visitado(n, false);
        int comp = 0;
        for (int i = 0; i < n; i++) {
            if (!visitado[i]) {
                comp++;
                stack<int> s;
                s.push(i);
                while(!s.empty()) {
                    int atual = s.top();
                    s.pop();
                    if(!visitado[atual]) {
                        visitado[atual] = true;
                        for (int v : atomos[atual]) {
                            if(!visitado[v]) s.push(v);
                        }
                    }
                }
            }
        }
        cout << comp << endl;;
    }
}