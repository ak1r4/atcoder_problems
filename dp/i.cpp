#include <bits/stdc++.h>
using namespace std;

//
//    H       T
//  H   T   H   T
// H T H T H T H T
// 3 2 2 1 2 1 1 0


void bt(vector<long double>& ans, long double prev_probs, int n_heads, int cur, const vector<long double>& probs, const int& min_n_heads) {
    if (cur >= probs.size()) {
        if (n_heads >= min_n_heads) {
            ans.push_back(prev_probs);
        }
        return;
    }

    bt(ans, prev_probs * probs[cur], n_heads + 1, cur + 1, probs, min_n_heads);
    bt(ans, prev_probs * (1 - probs[cur]), n_heads, cur + 1, probs, min_n_heads);
}

int main() {
    int n;
    cin >> n;
    vector<long double> probs(n);
    for (auto& p : probs) { cin >> p; }

    vector<long double> ans;
    bt(ans, 1.0, 0, 0, probs, probs.size() / 2 + 1);

    long double result = 0.0;
    for (const auto& a : ans) {
        result += a;
    }

    cout << result << "\n";

    return 0;
}
