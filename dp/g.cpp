#include <bits/stdc++.h>
using namespace std;

void topsort(vector<int>& sorted_vs, vector<bool>& visited, int current_v, const vector<vector<int>>& parents_list) {
    if (visited[current_v]) {
        return;
    }
    for (const auto& parent_v : parents_list[current_v]) {
        topsort(sorted_vs, visited, parent_v, parents_list);
    }
    sorted_vs.push_back(current_v);
    visited[current_v] = true;
}

int main() {
    int n, m;
    cin >> n >> m;

    // populate parents and children map
    vector<vector<int>> children_list(n+1);
    vector<vector<int>> parents_list(n+1);

    for (int i = 0; i < m; ++i) {
        int v0, v1;
        cin >> v0 >> v1;
        children_list[v0].push_back(v1);
        parents_list[v1].push_back(v0);
    }

    // topological sort to determine evaluation order
    vector<int> sorted_vs;
    vector<bool> visited(n+1, false);
    for (int i = 0; i < parents_list.size(); ++i) {
        if (!parents_list[i].empty() && children_list[i].empty()) {
            topsort(sorted_vs, visited, i, parents_list);
        }
    }

    // run the dp
    vector<int> dp(n+1, 0);

    int max_path_nodes = 0;
    for (const auto& v : sorted_vs) {
        int prev_max_len = 0;
        for (const auto& pv : parents_list[v]) {
            prev_max_len = max(prev_max_len, dp[pv]);
        }
        dp[v] = prev_max_len + 1;
        max_path_nodes = max(max_path_nodes, dp[v]);
    }

    cout << max_path_nodes - 1 << "\n";

    return 0;
}
