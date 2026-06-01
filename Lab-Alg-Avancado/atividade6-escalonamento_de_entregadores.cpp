/*
 * Problema: Escalonamento de Entregadores (Activity Selection Modificado)
 * Técnica/Algoritmo: Algoritmo Guloso com Árvore de Busca Balanceada (std::multiset)
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> delivery;
        for (int i = 0; i < n; i++) {
            pair<int, int> d;
            cin >> d.first >> d.second;
            delivery.push_back(d);
        }

        auto comp = [](pair<int, int> a, pair<int,int> b) {
      	    return a.second < b.second;
        };

        sort(delivery.begin(), delivery.end(), comp);
        multiset<int> motoboys;
        for (int i = 0; i < k; i++) {
            motoboys.insert(0);
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            pair<int, int> current = delivery[i];
            auto it = motoboys.upper_bound(current.first);
            if (it != motoboys.begin()) {
                it--;
                res++;
                motoboys.erase(it);
                motoboys.insert(current.second);
            }
        }

        cout << res << endl;
    }
    return 0;
}

