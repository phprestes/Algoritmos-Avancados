/*
 * Problema: Correspondência de Substrings (Pattern Matching)
 * Técnica/Algoritmo: Algoritmo KMP (Knuth-Morris-Pratt)
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s, ss;
    cin >> s >> ss;

    // Construir lps
    vector<int> lps(ss.size());
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < ss.size()) {
        if (ss[i] == ss[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    // Encontrar substrings
    i = 0;
    int j = 0;
    int res = 0;
    while (i < s.size()) {
        if (s[i] == ss[j]) {
            i++;
            j++;
            if (j == ss.size()) {
                res++;
                j = lps[j - 1];
            }
        } else {
            if (j != 0) {
                j = lps[j  - 1];
            } else {
                i++;
            }
        }
    }

    cout << res << '\n';

    return 0;
}