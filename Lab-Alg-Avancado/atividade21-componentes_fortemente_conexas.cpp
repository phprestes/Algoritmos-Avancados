/*
 * Problema: Componentes Fortemente Conexas (SCCs)
 * Técnica/Algoritmo: Algoritmo de Tarjan
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <climits>

using namespace std;

void find_sccs(int u, vector<vector<int>>& adj, vector<int>& ids, vector<int>& low, 
               vector<bool>& on_stack, stack<int>& st, vector<vector<int>>& sccs, int& timer) {
    
    ids[u] = low[u] = ++timer;
    st.push(u);
    on_stack[u] = true;

    for (int v : adj[u]) {
        if (ids[v] == -1) {
            find_sccs(v, adj, ids, low, on_stack, st, sccs, timer);
            low[u] = min(low[u], low[v]);
        } else if (on_stack[v]) {
            low[u] = min(low[u], ids[v]);
        }
    }

    if (ids[u] == low[u]) {
        vector<int> current_scc;
        while (true) {
            int node = st.top();
            st.pop();
            on_stack[node] = false;
            current_scc.push_back(node);
            if (node == u) break;
        }
        sccs.push_back(current_scc);
    }
}

vector<vector<int>> tarjan(vector<vector<int>>& adj, int n) {
    vector<int> ids(n, -1);
    vector<int> low(n, 0);
    vector<bool> on_stack(n, false);
    stack<int> st;
    vector<vector<int>> sccs;
    int timer = 0;

    for (int i = 0; i < n; i++) {
        if (ids[i] == -1) {
            find_sccs(i, adj, ids, low, on_stack, st, sccs, timer);
        }
    }
    return sccs;
}

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> users(n);
    vector<vector<int>> users_rev(n);
    while(m--) {
        int a, b;
        cin >> a >> b;
        users[a-1].push_back(b-1);
    }

    vector<vector<int>> sccs = tarjan(users, n);

    for (auto& scc : sccs) sort(scc.begin(), scc.end());
    sort(sccs.begin(), sccs.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });

    for (int i = 0; i < sccs.size(); i++) {
        cout << '[' << sccs[i][0] + 1;
        for (int j = 1; j < sccs[i].size(); j++) {
            cout << ',' << sccs[i][j] + 1;
        }
        cout << ']' << '\n';
    }

    return 0;
}