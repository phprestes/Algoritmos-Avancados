#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int hourToInt(const string& h) {
    return stoi(h.substr(0, 2)) * 100 + stoi(h.substr(3, 2));
}

void radixSort(vector<tuple<int, int, int>>& v) {
    int n = v.size();
    int mx_get1 = get<1>(v[0]);
    for (int i = 1; i < n; i++) {
        mx_get1 = max(mx_get1, get<1>(v[i]));
    }
    
    for (int exp = 1; mx_get1 / exp > 0; exp *= 10) {
        vector<tuple<int, int, int>> output(n);
        int count[10] = {0};
        
        for (int i = 0; i < n; i++)
            count[(get<1>(v[i]) / exp) % 10]++;
            
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
            
        for (int i = n - 1; i >= 0; i--) {
            int digit = (get<1>(v[i]) / exp) % 10;
            output[count[digit] - 1] = v[i];
            count[digit]--;
        }
        
        v = output;
    }
    
    int mx_get2 = get<2>(v[0]);
    for (int i = 1; i < n; i++) {
        mx_get2 = max(mx_get2, get<2>(v[i]));
    }

    for (int exp = 1; mx_get2 / exp > 0; exp *= 10) {
        vector<tuple<int, int, int>> output(n);
        int count[10] = {0};

        for (int i = 0; i < n; i++)
            count[(get<2>(v[i]) / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int digit = (get<2>(v[i]) / exp) % 10;
            output[count[digit] - 1] = v[i];
            count[digit]--;
        }

        v = output;
    }
}

int main(void) {
    int x;
    cin >> x;
    for (int i = 0; i < x; i++) {
        int m, n;
        cin >> m >> n;
        vector<tuple<int, int, int>> c[m];
        for (int j = 0; j < n; j++) {
            int id, c_id;
            string h1, h2;
            cin >> id >> h1 >> h2 >> c_id;
            c[c_id - 1].push_back(make_tuple(id, hourToInt(h1), hourToInt(h2)));
        }
        for (int j = 0; j < m; j++) {
            if (!c[j].empty()) {
                radixSort(c[j]);
                vector <pair<int, int>> res;
                res.push_back({get<0>(c[j][0]), get<2>(c[j][0])});

                for (int k = 1; k < c[j].size(); k++) {
                    if (get<1>(c[j][k]) >= res.back().second)
                        res.push_back({get<0>(c[j][k]), get<2>(c[j][k])});
                }

                // Resultado
                cout << j + 1 << ": ";
                cout << res.size() << " = ";
                for (int k = 0; k < res.size(); k++) {
                    cout << res[k].first;
                    if (k < res.size() - 1) cout << ", ";
                }
            } else {
                cout << j + 1 << ": 0";
            }
            
            if (j != m - 1)
                cout << " | ";
        }
        cout << endl;
    }
    return 0;
}