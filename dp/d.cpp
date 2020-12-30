#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, W;
    cin >> N >> W;

    // dp[n][w] stores the maximum value of all subset of n items, with total weight up to w
    vector<vector<int64_t>> dp(N + 1);
    for (auto& v : dp) { v.resize(W + 1); }

    // when we have 0 item, value for all weight levels should be 0
    for (int i = 0; i < W; ++i) { dp[0][i] = 0; }
    // when we have up to i item, total weight 0 can only mean we have empty set, which means 0 value
    for (int i = 0; i < N; ++i) { dp[i][0] = 0; }

    for (int i = 0; i < N; ++i) {
        int w;
        int64_t v;
        cin >> w >> v;
        for (int j = 1; j <= W; ++j) {
            // we calculate dp[up to i+1 item][up to j weight]
            // it would be the bigger one between
            // - not adding the new item
            // - adding the new item
            dp[i + 1][j] = max(
                dp[i][j],  // not adding the new item, the weight does not change
                j >= w ? dp[i][j - w] + v : -1  // adding new item, when the new items weight do not exceeds limit, otherwise -1
            );
        }
    }

    // print dp[N][W], up to N item with up to W total weight
    cout << dp[N][W] << "\n";

    return 0;
}
