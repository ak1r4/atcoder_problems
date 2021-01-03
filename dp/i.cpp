#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<double> probs(n);
    for (auto& p : probs) { cin >> p; }

    // dp[i][j] - prob after tossed i coins with j heads
    vector<vector<double>> dp(n+1, vector<double>(n+1, 0.0));
    dp[0][0] = 1.0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <=i; ++j) {
            dp[i][j] = dp[i-1][j-1] * probs[i-1] + dp[i-1][j] * (1- probs[i-1]);
        }
    }

    double ans = 0.0;

    for (int i = 0; i <= n; ++i) {
        if (i > n-i) {
            ans += dp[n][i];
        }
    }


    // the problem asks for 1e-9 precision
    printf("%.10f\n", ans);

    return 0;
}
