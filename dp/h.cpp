#include <bits/stdc++.h>
using namespace std;

const int M = 1e9+7;

int main() {
    int h, w;
    cin >> h >> w;

    set<pair<int, int>> walls;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            char c;
            cin >> c;
            if (c == '#') {
                walls.emplace(i, j);
            }
        }
    }

    vector<vector<int>> dp(h, vector<int>(w, 0));
    for (int i = 0; i < w; ++i) { if (walls.count({0, i}) != 0) break; dp[0][i] = 1; }
    for (int i = 0; i < h; ++i) { if (walls.count({i, 0}) != 0) break; dp[i][0] = 1; }

    for (int i = 1; i < h; ++i) {
        for (int j = 1; j < w; ++j) {
            // skip walls
            if (walls.count({i, j}) != 0) {
                continue;
            }

            // sum up the paths
            int n_paths = 0;
            if (walls.count({i-1, j}) == 0) {
                n_paths += dp[i-1][j] % M;
            }
            if (walls.count({i, j-1}) == 0) {
                n_paths += dp[i][j-1] % M;
            }
            dp[i][j] = n_paths;
        }
    }

    cout << dp[h-1][w-1] % M << "\n";

    return 0;
}
