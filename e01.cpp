#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

int main(void) {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        vector<tuple<bool, int, int>> v(m);

        for (int j = 0; j < m; j++) {
            int id, pai, mae;
            string diab;
            cin >> id >> diab >> pai >> mae;
            v[id - 1] = make_tuple(diab == "sim", pai, mae);
        }

        int total = 0;
        for (auto j: v) {
            int pai = get<1>(j);
            int mae = get<2>(j);
            if (get<0>(j) && ((pai != -1 && get<0>(v[pai - 1])) || (mae != -1 && get<0>(v[mae - 1])))) {
                total += 1;
            }
        }

        cout << total << endl;
    }
}