/*
 * Problema: Pareamento Máximo
 * Técnica/Algoritmo: Algoritmo Guloso (Two Pointers)
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int t;
    cin >> t;
    while(t--) {
        int n, x;
        cin >> n >> x;
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }

        sort(p.begin(), p.end());

        int res = 0;
        int start = 0;
        int end = n - 1;
        while (start <= end) {
            if (p[end] + p[start] <= x)
                start++;
            end--;
            res++;
        }

        cout << res << endl;
    }
    return 0;
}