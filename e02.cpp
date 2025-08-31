#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int dataParaNumero(const string& data) {
    int dia = stoi(data.substr(0, 2));
    int mes = stoi(data.substr(3, 2));
    int ano = stoi(data.substr(6, 4));
    return ano * 10000 + mes * 100 + dia;
}

string numeroParaData(int numero) {
    int ano = numero / 10000;
    int mes = (numero % 10000) / 100;
    int dia = numero % 100;
    
    string s_dia = (dia < 10) ? "0" + to_string(dia) : to_string(dia);
    string s_mes = (mes < 10) ? "0" + to_string(mes) : to_string(mes);
    
    return s_dia + "/" + s_mes + "/" + to_string(ano);
}

void radixSort(pair<string, int> v[], int n) {
    int mx = v[0].second;
    for (int i = 1; i < n; i++) {
        if (v[i].second > mx)
            mx = v[i].second;
    }

    for (int exp = 1; mx / exp > 0; exp *= 10) {
        pair<string, int> output[n];
        int count[10] = { 0 };

        for (int i = 0; i < n; i++)
            count[(v[i].second / exp) % 10]++;

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(v[i].second / exp) % 10] - 1] = v[i];
            count[(v[i].second / exp) % 10]--;
        }

        for (int i = 0; i < n; i++)
            v[i] = output[i];
    }
}

void radixSortDatas(vector<int>& datas) {
    if (datas.empty()) return;
    
    int mx = datas[0];
    for (size_t i = 1; i < datas.size(); i++) {
        if (datas[i] > mx)
            mx = datas[i];
    }

    for (int exp = 1; mx / exp > 0; exp *= 10) {
        vector<int> output(datas.size());
        int count[10] = {0};

        for (size_t i = 0; i < datas.size(); i++)
            count[(datas[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = datas.size() - 1; i >= 0; i--) {
            output[count[(datas[i] / exp) % 10] - 1] = datas[i];
            count[(datas[i] / exp) % 10]--;
        }

        for (size_t i = 0; i < datas.size(); i++)
            datas[i] = output[i];
    }
}

int main(void) {
    cout << fixed << setprecision(2);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        pair<string, int> v[m];
        int total = 0;
        for (int j = 0; j < m; j++) {
            string d;
            double g;
            cin >> d >> g;
            v[j] = {d, round(g * 100)};
            total += g * 100;
        }

        radixSort(v, m);
        int soma = 0;
        vector<int> dias;
        for (int j = m - 1; j >= 0; j--) {
            if (soma > total - soma) break;
            soma += v[j].second;
            dias.push_back(dataParaNumero(v[j].first));
        }

        radixSortDatas(dias);
        cout << dias.size() << " dias " << "(";

        auto it = dias.begin();
        if (it != dias.end()) {
            cout << numeroParaData(*it);
            it++;
            for (; it != dias.end(); it++) {
                cout << ", " << numeroParaData(*it);
            }
        }

        cout << ") | soma=" << double(soma) / 100 << " | "  << double(dias.size()) / m * 100 << "% dos dias totais" << endl;
    }

    return 0;
}