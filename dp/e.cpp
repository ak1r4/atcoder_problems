#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    int64_t W;
    cin >> N >> W;

    // if we keep the same dp as problem d. dp[w] is going to be 1 billion items long, with each item occupy 4 bytes (32 bit)
    // it would be 4GB memory just to store 1 row of dp.
    // we also need a temporary 1-d dp array to store new row. So we would need at least 8GB of memory for the arrays.
    // so we cannot construct dp slots on weight. In the case of this problem, value is at most 1k. Because N is at most 100,
    // we are dealing with dp array of 100k in size (100k would be the highest value we can achieve)
    // so dp[v] would be 100k items long, each item would be the minimal weight in total to achieve this value.
    // since a single weight can be 1e9 big, if we use int32_t, we could only store the sum of 4 such weights,
    // hence we need to use int64_t to track the weights in dp[v].

    vector<pair<int64_t, int>> wv(N);
    for (auto& [w, v] : wv) {
        cin >> w >> v;
    }

    int max_value = 0;
    for (const auto& [w, v] : wv) max_value += v;

    // when we have 0 item, it is impossible to achive any value, so all the required weights to achive value v is infinity.
    array<vector<int64_t>, 2> dps {
        vector<int64_t>(max_value + 1, numeric_limits<int64_t>::max()),
        vector<int64_t>(max_value + 1, numeric_limits<int64_t>::max())
    };
    bool new_dp_idx = 1;
    dps[!new_dp_idx][0] = 0;
    dps[new_dp_idx][0] = 0;

    for (const auto& [w, v] : wv) {
        for (int i = 1; i <= max_value; ++i) {
            // this is a bit tricky here because of overflow
            // when the target value is bigger than the new item's value, for the new weight, we can find the previous (i - v) weight and add it
            // to the new item's weight
            // but if the previous (i - v) is already numeric_limits<int64_t>::max(), the addition will produce a negative value
            // if this is the case, we need to make sure it's still the infinity value we hope for
            int64_t new_weight = numeric_limits<int64_t>::max();
            if (i >= v) {
                new_weight = dps[!new_dp_idx][i - v] + w;
            }
            if (new_weight < 0) {  // previous weight at (i - v) must be infinity
                new_weight = numeric_limits<int64_t>::max();
            }

            dps[new_dp_idx][i] = min(
                dps[!new_dp_idx][i],  // not taking a new item
                new_weight
            );
        }
        new_dp_idx = !new_dp_idx;
    }

    int i = max_value;
    for (;i>=0; --i) {
        if (dps[!new_dp_idx][i] <= W && dps[!new_dp_idx][i] >= 0) break;
    }
    cout << i << "\n";

    return 0;
}
