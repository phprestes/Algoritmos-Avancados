/*
 * Problema: Servidor DNS Simulado
 * Técnica/Algoritmo: Dicionário (std::map)
 */
#include <iostream>
#include <map>

using namespace std;

int main(void) {
    int n, m;
    cin >> n >> m;
    map<string, string> dns;
    pair<string, string> cmd;

    for (int i = 0; i < n; i++) {
        cin >> cmd.second >> cmd.first;
        dns[cmd.first + ";"] = cmd.second;
    }

    for (int i = 0; i < m; i++) {
        cin >> cmd.second >> cmd.first;
        cout << cmd.second << " " << cmd.first << " #" << dns[cmd.first] << endl;
    }

    return 0;
}