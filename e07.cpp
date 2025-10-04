#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
    int n;
    cin >> n;

    long long r[n+1];
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }

    long long dp[n+1][2];
    dp[0][0] = 0;
    dp[0][1] = 1;
    for (int i = 1; i <= n; i++) {
        // debaixo nao quebrou
        dp[i][0] = min(dp[i-1][0], dp[i-1][1]) + r[i];

        // debaixo quebrou
        int sobra = max(r[i] - i + 1, 0LL);
        dp[i][1] = min(dp[i-1][0] + sobra, max(dp[i-1][1] + r[i] - 1LL, 0LL));
    }

    cout << min(dp[n][0], dp[n][1]) << endl;

    return 0;
}