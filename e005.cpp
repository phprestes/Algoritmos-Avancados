#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <queue>
#include <iomanip>

#define R 6371

using namespace std;

double latc, lonc;

double toRad(double ang) {
    return ang * (M_PI / 180.0);
}

double haversine(double lat, double lon) {
    return 2 * R * asin(sqrt(pow(sin((toRad(lat) - toRad(latc))/2), 2) + cos(toRad(latc)) * cos(toRad(lat)) * pow(sin((toRad(lon) - toRad(lonc))/2), 2)));
}

int main(void) {
    int n;
    cout << fixed << setprecision(3);
    cin >> n;
    cin >> latc >> lonc;

    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

    string jogador;
    double lat, lon;
    for (int i = 0; i < n; i++) {
        cin >> jogador >> lat >> lon;
        pq.push({haversine(lat, lon), jogador});

        cout << "> [AVISO] MELHOR PALPITE: " << pq.top().first << "km" << endl;
    }

    pair<double, string> placar;
    cout << "\nRANKING\n-------" << endl;
    for (int i = 1; i <= n; i++) {
        placar = pq.top();
        cout << setw(2) << right << i << ". ";
        cout << setw(21) << left << placar.second << ": ";
        cout << setw(6) << right << placar.first << " km";

        if (placar.first < 0.05) {
            cout << " [FANTASTICO]";
        }

        cout << endl;
        pq.pop();
    }

    return 0;
}