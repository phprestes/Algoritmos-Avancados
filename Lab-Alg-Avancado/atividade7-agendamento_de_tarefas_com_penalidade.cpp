/*
 * Problema: Agendamento de Tarefas com Penalidade (Job Scheduling)
 * Técnica/Algoritmo: Algoritmo Guloso (Ordenação por tempo)
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }

    sort(p.begin(), p.end());

    long long current_time = 0;
    long long res = 0;
    for (auto x : p) {
        current_time += x.first;
        res += x.second - current_time;
    }
    cout << res << endl;
    return 0;
}