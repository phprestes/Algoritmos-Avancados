#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

int main(void) {
    int n;
    cin >> n;

    // Cadastro de itens
    map<int, double> mapa;
    char hashtag;
    int codigo;
    double preco;

    for (int i = 0; i < n; i++) {
        cin >> hashtag >> codigo >> preco;

        if (mapa.find(codigo) != mapa.end()) {
            cout << "Produto com código #" << codigo << " já cadastrado.\n";
            continue;
        }

        mapa[codigo] = preco;
    }

    // Vendas
    double total;
    while (true) {
        cin >> n;
        total = 0;

        if (n == -1)
            break;
            
        for (int i = 0; i < n; i++) {
            cin >> hashtag >> codigo >> preco;

            if (mapa.find(codigo) == mapa.end()) {
                cout << "Produto com código #" << codigo << " não cadastrado.\n";
                continue;
            }

            total += mapa[codigo] * preco;
        }
        cout << fixed << setprecision(2);
        cout << "R$" << total << '\n';
    }

    return 0;
}