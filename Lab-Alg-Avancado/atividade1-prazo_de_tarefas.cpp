/*
 * Problema: Prazo de Tarefas
 * Técnica/Algoritmo: Dicionário (std::map) para buscas eficientes
 */
#include <iostream>
#include <map>

using namespace std;

int main(void) {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        string final_task;
        int n, d;
        cin >> n;
        map<string, int> tasks;
        pair<string, int> task;

        for (int j = 0; j < n; j++) {
            cin >> task.first >> task.second;
            tasks[task.first] = task.second;
        }
        
        cin >> d >> final_task;
        auto it = tasks.find(final_task);
        cout << "Case " << i+1 << ": ";
        if (it == tasks.end() || it->second > d+5) {
            cout << "Do your own homework!" << endl;
        } else if (it->second <= d) {
            cout << "Yessss" << endl;
        } else
            cout << "Late" << endl;
    }

    return 0;
}