#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <queue>
#include <sstream>
#include <map>

using namespace std;

typedef struct _quest {
    int id;           // ID original da quest
    int time;
    double finish_time;
    vector<int> dependency;
    int degree;
} Quest;

typedef struct _hero {
    string name;
    double prod;
    double free_time;
    vector<int> atr_quests;  // armazena IDs das quests
} Hero;

int main(void) {
    int x;
    cin >> x;
    for (int i = 0; i < x; i++) {
        int n, m;
        double total = 0;
        cin >> n >> m;

        // lendo heróis
        vector<Hero> h(n);
        for (int j = 0; j < n; j++) {
            string level;
            cin >> h[j].name >> level;

            h[j].free_time = 0;

            if (!level.compare("Aprendiz")) h[j].prod = 0.75;
            else if (!level.compare("Aventureiro")) h[j].prod = 1.0;
            else if (!level.compare("Cavaleiro")) h[j].prod = 1.2;
            else if (!level.compare("Mestre")) h[j].prod = 1.5;
            else h[j].prod = 2.0;
        }
        
        // lendo quests
        vector<Quest> q(m);
        map<int, int> idToIndex; // Mapeia ID da quest para índice no vetor
        
        for (int j = 0; j < m; j++) {
            int id;
            cin >> id >> q[j].time;
            q[j].id = id;
            q[j].finish_time = q[j].time;
            q[j].degree = 0;
            
            idToIndex[id] = j; // Mapeia o ID para o índice
            
            string linha;
            getline(cin, linha);
            istringstream ss(linha);

            int num;
            while (ss >> num) {
                if(num != 0) q[j].dependency.push_back(num);
            }
        }

        // Construir grafo para topological sort
        vector<vector<int>> adj(m); // Lista de adjacência
        vector<int> indegree(m, 0);
        
        for (int j = 0; j < m; j++) {
            for (int depId : q[j].dependency) {
                if (idToIndex.find(depId) != idToIndex.end()) {
                    int depIndex = idToIndex[depId];
                    adj[depIndex].push_back(j);
                    indegree[j]++;
                }
            }
        }

        // Topological sort usando Kahn's algorithm
        vector<int> q_sorted;
        queue<int> qqueue;
        
        for (int j = 0; j < m; j++) {
            if (indegree[j] == 0) {
                qqueue.push(j);
            }
        }

        while (!qqueue.empty()) {
            int current = qqueue.front();
            qqueue.pop();
            q_sorted.push_back(current);

            for (int neighbor : adj[current]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    qqueue.push(neighbor);
                }
            }
        }

        // Processar quests em ordem topológica
        map<int, double> finishTimes; // Mapeia ID da quest para tempo de término
        
        for (int sortedIndex : q_sorted) {
            Quest& current_quest = q[sortedIndex];
            int bestHero = 0;
            double bestFinish = 1e18;

            // Encontrar o maior tempo de término das dependências
            double depFinish = 0;
            for (int depId : current_quest.dependency) {
                if (finishTimes.find(depId) != finishTimes.end()) {
                    depFinish = max(depFinish, finishTimes[depId]);
                }
            }

            // Encontrar o herói que termina mais cedo esta quest
            for (int k = 0; k < n; k++) {
                double startTime = max(depFinish, h[k].free_time);
                double finish = startTime + current_quest.time / h[k].prod;
                
                if (finish < bestFinish) {
                    bestFinish = finish;
                    bestHero = k;
                }
            }

            // Atribuir quest ao herói escolhido
            current_quest.finish_time = bestFinish;
            finishTimes[current_quest.id] = bestFinish;
            h[bestHero].free_time = bestFinish;
            h[bestHero].atr_quests.push_back(current_quest.id);
            total = max(total, bestFinish);
        }

        // Saída
        for (int j = 0; j < n; j++) {
            cout << h[j].name << " = {";
            if (!h[j].atr_quests.empty()) {
                for (int k = 0; k < h[j].atr_quests.size() - 1; k++) {
                    cout << h[j].atr_quests[k] << ",";
                }
                cout << h[j].atr_quests[h[j].atr_quests.size() - 1];
            }
            cout << "}" << endl;
        }

        cout << fixed << setprecision(2);
        cout << "Tempo mínimo: " << total << endl;

        if (i != x-1)
            cout << endl;
    }

    return 0;
}