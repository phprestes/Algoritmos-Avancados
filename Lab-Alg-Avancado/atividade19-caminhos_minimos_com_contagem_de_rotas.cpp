/*
 * Problema: Caminhos Mínimos com Contagem de Rotas
 * Técnica/Algoritmo: Algoritmo de Dijkstra (Menor Caminho e Rastreamento)
 */
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    const int MOD = 1e9 + 7;
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> cities(n);
    while(m--) {
        int a, b, c;
        cin >> a >> b >> c;
        cities[a-1].push_back({c, b-1});
    }

    vector<long long> dist(n, LONG_LONG_MAX);
    vector<long long> path(n, 0);
    vector<int> min_path(n, INT_MAX);
    vector<int> max_path(n, 0);
    priority_queue<pair<long long, int>, vector<pair<long long,int>>, greater<pair<long long, int>>> pq;

    pq.emplace(0, 0);
    dist[0] = 0;
    path[0] = 1;
    min_path[0] = 0;
    max_path[0] = 0;
    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        long long d = top.first;
        int u = top.second;
        if (d > dist[u]) continue;
        for (auto p : cities[u]) {
            long long w = p.first;
            int v = p.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                path[v] = path[u];
                min_path[v] = min_path[u] + 1;
                max_path[v] = max_path[u] + 1;
                pq.emplace(dist[v], v);
            } else if (dist[v] == dist[u] + w) {
                path[v] = (path[u] + path[v]) % MOD;
                min_path[v] = min(min_path[v], min_path[u] + 1);
                max_path[v] = max(max_path[v], max_path[u] + 1);
            }
        }
    }

    cout << dist[n-1] << ' ' << path[n-1] << ' '  << min_path[n-1] << ' ' << max_path[n-1] << endl;
}