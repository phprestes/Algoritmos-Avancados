/*
 * Problema: Conexão de Sistemas Estelares (Túneis e Ressonância)
 * Técnica/Algoritmo: Árvore Geradora Mínima (Kruskal) e Algoritmo de Par de Pontos Mais Próximos (Divisão e Conquista)
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define dist(a,b) sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2))

// Definição de SISTEMA
typedef struct _sistema {
    string nome;
    double x;
    double y;
    int id;
} SISTEMA;

bool compareByX(SISTEMA a, SISTEMA b) {
    return a.x < b.x;
}

bool compareByY(SISTEMA a, SISTEMA b) {
    return a.y < b.y;
}

// Definião de TUNEL
typedef struct _tunel {
    int id_a;
    int id_b;
    double tensao;
} TUNEL;

bool compareTunel(TUNEL a, TUNEL b) {
    if (a.tensao != b.tensao) return a.tensao < b.tensao;
    if (a.id_a != b.id_a) return a.id_a < b.id_a;
    return a.id_b < b.id_b;
}

class UnionFind {
private:
    vector<int> pais, peso;

public:
    UnionFind(int n) {
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
            return true;
        }
        return false;
    }
};

vector<TUNEL> kruskal(vector<SISTEMA> sistemas, int n, double tensao_max) {
    // Calcula todas as arestas possíveis
    int total_possiveis = (n * (n-1)) / 2;
    vector<TUNEL> tuneis_possiveis;
    tuneis_possiveis.reserve(total_possiveis);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            tuneis_possiveis.push_back({sistemas[i].id, sistemas[j].id, dist(sistemas[i], sistemas[j])});
        }
    }
    sort(tuneis_possiveis.begin(), tuneis_possiveis.end(), compareTunel);

    // Mescla os conjuntos
    UnionFind uf(sistemas.size());
    vector<TUNEL> tuneis_legais;
    for (auto tunel : tuneis_possiveis) {
        if (tunel.tensao > tensao_max)
            continue;
        int x = tunel.id_a, y = tunel.id_b;
        if (uf.join(x, y)) {
            tuneis_legais.push_back(tunel);
            if (tuneis_legais.size() == n - 1) break;
        }
    }

    return tuneis_legais;
}

TUNEL closest(vector<SISTEMA> sistemas, int inicio, int fim, int valor_brute = 2) {
    // Caso base
    if (fim - inicio <= valor_brute) {
        TUNEL minimo = {-1, -1, INFINITY};
        for (int i = inicio; i < fim; i++) {
            for (int j = i+1; j < fim; j++) {
                double distancia_atual = dist(sistemas[i], sistemas[j]);
                int id1 = sistemas[i].id;
                int id2 = sistemas[j].id;

                if (id1 > id2) {
                    swap(id1, id2);
                }
                
                if (distancia_atual < minimo.tensao || 
                   (distancia_atual == minimo.tensao && id1 < minimo.id_a)) {
                    minimo = {id1, id2, distancia_atual};
                }
            }
        }
        return minimo;
    }

    int meio = (inicio + fim) / 2;
    double meio_x = sistemas[meio].x;

    TUNEL d = closest(sistemas, inicio, meio);
    TUNEL d_e = closest(sistemas, meio, fim);

    // Escolhe o menor entre os dois lados
    if (d_e.tensao < d.tensao || 
        (d_e.tensao == d.tensao && d.id_a > d_e.id_a)) {
        d = d_e;
    }
    
    // Constrói a strip com índices globais
    vector<SISTEMA> strip;
    for (int i = inicio; i < fim; i++) {
        if (abs(meio_x - sistemas[i].x) < d.tensao) {
            strip.push_back(sistemas[i]);
        }
    }

    // Ordena por Y
    sort(strip.begin(), strip.end(), compareByY);
    
    // Verifica pontos na strip
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i+1; j < strip.size() && (abs(strip[j].y - strip[i].y) < d.tensao); j++) {
            double dist_strip = dist(strip[j], strip[i]);
            int id1 = strip[i].id;
            int id2 = strip[j].id;

            if (id1 > id2) {
                swap(id1, id2);
            }

            if (dist_strip < d.tensao || 
                (dist_strip == d.tensao && d.id_a > id1)) {
                d = {id1, id2, dist_strip};
            }
        }
    }

    return d;
}

int main(void) {
    cout << fixed << setprecision(2);
    int casos;
    cin >> casos;
    while(casos--) {
        int total_sist, important_sist;
        double tensao_max;
        cin >> total_sist >> important_sist >> tensao_max;

        // Leitura de todos os sistemas
        vector<SISTEMA> sistemas(total_sist);
        for (int i = 0; i < total_sist; i++) {
            cin >> sistemas[i].nome >> sistemas[i].x >> sistemas[i].y;
            sistemas[i].id = i;
        }

        // Parte 1 - MST
        vector<TUNEL> tuneis_legais = kruskal(sistemas, important_sist, tensao_max);
        for (auto tunel : tuneis_legais) {
            cout << sistemas[tunel.id_a].nome << ", " << sistemas[tunel.id_b].nome << ", " << tunel.tensao << endl;
        }

        // Parte 2 - Closest Pair of Points Problem
        vector<SISTEMA> sistemas_original = sistemas;
        sort(sistemas.begin(), sistemas.end(), compareByX);
        TUNEL pertinho = closest(sistemas, 0, sistemas.size());
    
        cout << "Ponto de Ressonância: " << sistemas_original[pertinho.id_a].nome << ", " << sistemas_original[pertinho.id_b].nome << ", " << pertinho.tensao << endl;
        cout << '\n';
    }

    return 0;
}