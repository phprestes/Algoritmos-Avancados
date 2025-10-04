#include <iostream>
#include <algorithm>

using namespace std;

int countMerge(pair<int,int> v[], int l, int r) {
    int m = l + (r - l) / 2;
    int n1 = m - l + 1, n2 = r - m;
    pair<int,int> left[n1], right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = v[i + l];
    for (int i = 0; i < n2; i++)
        right[i] = v[m + i + 1];
    
    int res = 0, i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i].second <= right[j].second)
            v[k++] = left[i++];
        else {
            v[k++] = right[j++];
            res += n1 - i;
        }
    }

    while (i < n1)
        v[k++] = left[i++];
    while (j < n2)
        v[k++] = right[j++];

    return res;
}

int countInversions(pair<int,int> v[], int l, int r) {
    int res = 0;
    if (l < r) {
        int m = l + (r - l) / 2;

        res += countInversions(v, l, m);
        res += countInversions(v, m + 1, r);

        res += countMerge(v, l, r);
    }
    return res;
}

int main(void) {
    int n;
    cin >> n;
    pair<int, int> res[n];

    for (int x = 0; x < n; x++) {
        int j;
        cin >> j;
        pair<int, int> positions[j];
        for (int i = 0; i < j; i++) {
            cin >> positions[i].first >> positions[i].second;
        }

        sort(positions, positions + j);

        res[x] = make_pair(countInversions(positions, 0, j-1), x);
    }
    sort(res, res + n);
        
    for (int i = n - 1; i >= 0; i--) {
        cout << res[i].second << " " << res[i].first << endl;
    }

    return 0;
}