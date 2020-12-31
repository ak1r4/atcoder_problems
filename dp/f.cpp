#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;

    vector<vector<tuple<int, int, int, char>>> dp(a.size() + 1);
    for (auto& v : dp) v.resize(b.size() + 1);

    for (int i = 0; i <= a.size(); ++i) dp[i][0] = {0, -1, -1, 0};
    for (int i = 0; i <= b.size(); ++i) dp[0][i] = {0, -1, -1, 0};

    for (int i = 1; i <= a.size(); ++i) {
        for (int j = 1; j <= b.size(); ++j) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = {get<0>(dp[i-1][j-1]) + 1, i-1, j-1, a[i-1]};
            } else {
                if (get<0>(dp[i-1][j]) > get<0>(dp[i][j-1])) {
                    dp[i][j] = {get<0>(dp[i-1][j]), i-1, j, 0};
                } else {
                    dp[i][j] = {get<0>(dp[i][j-1]), i, j-1, 0};
                }
            }
        }
    }

    int i = a.size(), j = b.size();
    string ans = "";
    while (i >= 0 && j >= 0) {
        if (auto c = get<3>(dp[i][j]); c) {
            ans.insert(0, 1, get<3>(dp[i][j]));
        }
        int i_ = get<1>(dp[i][j]);
        j = get<2>(dp[i][j]);
        i = i_;
    }
    cout << ans << "\n";

    return 0;
}
