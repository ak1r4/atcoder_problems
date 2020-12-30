#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> h(n), c(n);

    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    c[0] = 0;

    for (int i = 1; i < n; ++i) {
        int min_c = numeric_limits<int>::max();
        for (int j = 1; j <= k; ++j) {
            if (i - j >= 0) {
                min_c = min(min_c, c[i - j] + abs(h[i] - h[i - j]));
            }
        }
        c[i] = min_c;
    }

    cout << c[n-1] << "\n";

    return 0;
}
