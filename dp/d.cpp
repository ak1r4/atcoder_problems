#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, W;
    cin >> N >> W;

    array<vector<int64_t>, 2> dps {vector<int64_t>(W+1, 0), vector<int64_t>(W+1, 0)};
    bool new_dp_idx = 1;

    for (int i = 0; i < N; ++i) {
        int w;
        int64_t v;
        cin >> w >> v;

        for (int j = 0; j <=W; ++j) {
            dps[new_dp_idx][j] = max(
                dps[!new_dp_idx][j],  // do not take the new item
                w > j ? -1 : dps[!new_dp_idx][j-w] + v  // if current weight is bigger than the weight we are calc, return -1 value,
                                                        // which means we don't take this new item (max() will pick the previous one)
                                                        // otherwise, we add the current value to a previous vlaue with weight of j -w
            );
        }
        new_dp_idx = !new_dp_idx;
    }

    cout << dps[!new_dp_idx][W] << "\n";

    return 0;
}
