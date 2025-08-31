#include <iostream>
#include <string>
#include <set>

using namespace std;

/// @brief Classe para definir a estrutura do nó da Trie
class NoTrie {
    public:
        // Contém 26 possíveis filhos correspondendo às letras do alfabeto
        NoTrie *filhos[26];

        // Inicializa todos como ponteiro nulo
        NoTrie() {
            for (int i = 0; i < 26; i++) {
                filhos[i] = nullptr;
            }
        }

        ~NoTrie() {
            for (int i = 0; i < 26; i++) {
                delete filhos[i]; // libera recursivamente
            }
        }
};

class Trie {
    private:
        NoTrie *raiz;
    public:
        // Inicializa a Trie com o nó raiz que não assume valor
        Trie() {
            raiz = new NoTrie();
        }

        ~Trie() {
            delete raiz;
        }

        /// @brief Insere uma palavra na Trie
        /// @param palavra - Palavra a ser inserida
        void insert(string palavra) {
            // A partir da raiz, verifica se a letra já existe e se não existir, adiciona um nó daquela letra
            NoTrie *no = raiz;
            for (char c : palavra) {
                int index = c - 'A';
                if (!no->filhos[index]) {
                    no->filhos[index] = new NoTrie();
                }
                no = no->filhos[index];
            }
        }

        /// @brief Procura uma palavra (prefixo) na Trie
        /// @param palavra - Palavra a ser procurada
        bool search(string palavra) {
            NoTrie *no = raiz;
            for (char c: palavra) {
                int index = c - 'A';
                if (!no->filhos[index]) {
                    return false; // Caso não tenha o nó respectivo da letra, retorna false
                }
                no = no->filhos[index];
            }
            return true; // Se chegou até aqui, a palavra toda está na Trie
        }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Trie trie;
    char caca_palavras[n][m];

    // Direções para auxiliar a percorrer o caça palavras
    const int dir[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    // Lê o caça palavras
    for (int i = 0; i < n * m; i++) {
        cin >> caca_palavras[i % n][i / m];
    }

    // Coloca todas as possibilidades de palavras na Trie, começando de todas as letras
    // e indo para cima, baixo, esquerda, direita e diagonais
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int d = 0; d < 8; d++) {
                int di = dir[d][0];
                int dj = dir[d][1];

                string palavra;
                int x = i, y = j;
                
                while (x >= 0 && x < n && y >= 0 && y < m) {
                    palavra += caca_palavras[x][y];
                    x += di;
                    y += dj;
                }

                trie.insert(palavra);
            }
        }
    }

    // Lê quantas palavras vão ser procuradas
    int dic_tam;
    cin >> dic_tam;

    set<string> palavras_encontradas;

    // Guarda todas as palavras encontradas em um set
    for (int i = 0; i < dic_tam; i++) {
        string palavra;
        cin >> palavra;
        if (trie.search(palavra)) {
            palavras_encontradas.insert(palavra);
        }
    }

    // Printa as palavras do set  
    cout << palavras_encontradas.size() << endl;
    for (string palavra : palavras_encontradas) {
        cout << palavra << endl;
    }

    return 0;
}