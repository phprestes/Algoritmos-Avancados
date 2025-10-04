#include <bits/stdc++.h>
using namespace std;

using ll = long long;
pair<ll, ll> mid;

int quad(pair<ll, ll> p) {
    if (p.first >= 0 && p.second >= 0) return 1;
    if (p.first <= 0 && p.second >= 0) return 2;
    if (p.first <= 0 && p.second <= 0) return 3;
    return 4;
}

int orientation(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c) {
    __int128_t res = (__int128_t)(b.second-a.second)*(c.first-b.first) - (__int128_t)(c.second-b.second)*(b.first-a.first);

    if (res == 0)
        return 0;
    if (res > 0)
        return 1;
    return -1;
}

bool saoTodosColineares(const vector<pair<ll, ll>>& a) {
    if (a.size() <= 2) {
        return true;
    }
    
    for (size_t i = 2; i < a.size(); i++) {
        if (orientation(a[0], a[1], a[i]) != 0) {
            return false;
        }
    }

    return true;
}

// compare function for sorting
bool compare(pair<ll, ll> p1, pair<ll, ll> q1) {
    pair<ll, ll> p = make_pair(p1.first - mid.first,
                                p1.second - mid.second);
    pair<ll, ll> q = make_pair(q1.first - mid.first,
                                q1.second - mid.second);

    int one = quad(p);
    int two = quad(q);

    if (one != two) {
        return one < two;
    }

    __int128_t cross_product = (__int128_t)p.first * q.second - (__int128_t)p.second * q.first;
    if (cross_product != 0) {
        return cross_product > 0; // Ordenação anti-horária
    }

    ll dist_p_sq = p.first * p.first + p.second * p.second;
    ll dist_q_sq = q.first * q.first + q.second * q.second;
    return dist_p_sq < dist_q_sq;
}

vector<pair<ll, ll>> merger(vector<pair<ll, ll> > a,
                            vector<pair<ll, ll> > b) {
    if (a.empty()) return b;
    if (b.empty()) return a;

    int n1 = a.size(), n2 = b.size();

    int ia = 0, ib = 0;
    for (int i = 1; i < n1; i++)
        if (a[i].first > a[ia].first)
            ia = i;

    for (int i = 1; i < n2; i++)
        if (b[i].first < b[ib].first)
            ib = i;

    int inda = ia, indb = ib;
    bool done = 0;
    while (!done) {
        done = 1;
        while (orientation(b[indb], a[inda], a[(inda+1)%n1]) >= 0)
            inda = (inda + 1) % n1;

        while (orientation(a[inda], b[indb], b[(n2+indb-1)%n2]) <= 0) {
            indb = (n2 + indb-1) % n2;
            done = 0;
        }
    }

    int uppera = inda, upperb = indb;
    inda = ia, indb = ib;
    done = 0;
    while (!done) {
        done = 1;
        while (orientation(a[inda], b[indb], b[(indb + 1) % n2]) >= 0) indb = (indb + 1) % n2;
        while (orientation(b[indb], a[inda], a[(n1 + inda - 1) % n1]) <= 0) {
            inda = (n1 + inda - 1) % n1;
            done = 0;
        }
    }

    int lowera = inda, lowerb = indb;
    vector<pair<ll, ll>> ret;

    int ind = uppera;
    ret.push_back(a[uppera]);
    while (ind != lowera) {
        ind = (ind + 1) % n1;
        ret.push_back(a[ind]);
    }

    ind = lowerb;
    ret.push_back(b[lowerb]);
    while (ind != upperb) {
        ind = (ind+ 1 ) % n2;
        ret.push_back(b[ind]);
    }
    return ret;

}

vector<pair<ll, ll>> bruteHull(vector<pair<ll, ll>> a) {
    set<pair<ll, ll>> s;

    for (int i = 0; i < a.size(); i++) {
        for (int j = i+1; j < a.size(); j++) {
            ll x1 = a[i].first, x2 = a[j].first;
            ll y1 = a[i].second, y2 = a[j].second;

            __int128_t a1 = y1-y2;
            __int128_t b1 = x2-x1;
            __int128_t c1 = (__int128_t)x1*y2- (__int128_t)y1*x2;
            int pos = 0, neg = 0;

            for (int k=0; k < a.size(); k++) {
                __int128_t val = a1 * a[k].first + b1 * a[k].second + c1;
                if (val <= 0) neg++;
                if (val >= 0) pos++;
            }

            if (pos == a.size() || neg == a.size()) {
                s.insert(a[i]);
                s.insert(a[j]);
            }
        }
    }

    vector<pair<ll, ll>>ret;
    for (auto e:s)
        ret.push_back(e);

    int n = ret.size();
    if (n < 3) return ret;

    // Sorting the points in the anti-clockwise order
    mid = {0, 0};
    for (int i = 0; i < n; i++) {
        mid.first += ret[i].first;
        mid.second += ret[i].second;
    }
    mid.first /= n;
    mid.second /= n;

    sort(ret.begin(), ret.end(), compare);
    return ret;
}

vector<pair<ll, ll>> divide(vector<pair<ll, ll>> a) {
    if (saoTodosColineares(a)) {
        return a;
    }

    if (a.size() <= 5)
        return bruteHull(a);
    
    vector<pair<ll, ll>> left, right;
    for (int i = 0; i < a.size()/2; i++)
        left.push_back(a[i]);
    for (int i = a.size()/2; i < a.size(); i++)
        right.push_back(a[i]);

    vector<pair<ll, ll>> left_hull = divide(left);
    vector<pair<ll, ll>> right_hull = divide(right);

    return merger(left_hull, right_hull);
}

vector<pair<ll, ll>> obterVetorRotacionado(vector<pair<ll, ll>> v_original) {
    if (v_original.size() < 2) return v_original;
    vector<pair<ll, ll>> v_copia = v_original;
    auto it_menor_elemento = min_element(v_copia.begin(), v_copia.end());
    rotate(v_copia.begin(), it_menor_elemento, v_copia.end());
    return v_copia;
}

// Driver code
int main() {
    cout << fixed << setprecision(4);
    const long long scale = 10000;
    int x;
    cin >> x;
    for (int i = 0; i < x; i++) {
        int n;
        cin >> n;
        vector<pair<ll, ll> > a(n);

        for (int j = 0; j < n; j++) {
            double c1, c2;
            cin >> c1 >> c2;
            a[j] = {(ll)round(c1 * scale), (ll)round(c2 * scale)};
        }

        sort(a.begin(), a.end());
        vector<pair<ll, ll>> ans = obterVetorRotacionado(divide(a));

        cout << "Caso " << i + 1 << ":" << endl;
        cout << "Tamanho do colar: " << ans.size() << endl;
        cout << "Pedras ancestrais: ";
        for (int j = 0; j < ans.size(); j++) {
            if (j != 0) cout << ",";
            cout << "(" << (double)ans[j].first / scale << ","  << (double)ans[j].second / scale << ")";
        }
        cout << endl << endl;
    }

    return 0;
}