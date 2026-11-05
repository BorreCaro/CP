#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007LL;

int N;
vector<int> b;
vector<vector<int>> adj;
vector<int> sz;
vector<bool> removed;
long long total_ans = 0;

void dfs_size(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }
}

int find_centroid(int u, int p, int comp_size) {
    for (int v : adj[u]) {
        if (v != p && !removed[v] && sz[v] > comp_size / 2) {
            return find_centroid(v, u, comp_size);
        }
    }
    return u;
}

void dfs_collect(int u, int p, int dist, int cur_max, vector<pair<int, int>>& nodes) {
    cur_max = max(cur_max, b[u]);
    nodes.push_back({cur_max, dist});
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            dfs_collect(v, u, dist + 1, cur_max, nodes);
        }
    }
}

// Calcula sum_{0 <= i < j < |nodes|} (d_i + d_j) * max(m_i, m_j) mod MOD
long long calc_pairs(vector<pair<int, int>>& nodes) {
    sort(nodes.begin(), nodes.end());
    long long res = 0;
    long long sum_d = 0;
    for (size_t j = 0; j < nodes.size(); ++j) {
        long long m_j = nodes[j].first;
        long long d_j = nodes[j].second;
        long long pair_dist_sum = ((long long)j * d_j + sum_d) % MOD;
        res = (res + m_j * pair_dist_sum) % MOD;
        sum_d = (sum_d + d_j) % MOD;
    }
    return res;
}

void decompose(int entry) {
    dfs_size(entry, 0);
    int c = find_centroid(entry, 0, sz[entry]);
    removed[c] = true;

    vector<pair<int, int>> all_nodes;
    all_nodes.reserve(sz[entry]);
    all_nodes.push_back({b[c], 0});

    for (int v : adj[c]) {
        if (!removed[v]) {
            vector<pair<int, int>> sub_nodes;
            dfs_collect(v, c, 1, b[c], sub_nodes);
            total_ans = (total_ans - calc_pairs(sub_nodes) + MOD) % MOD;
            all_nodes.insert(all_nodes.end(), sub_nodes.begin(), sub_nodes.end());
        }
    }

    total_ans = (total_ans + calc_pairs(all_nodes)) % MOD;

    for (int v : adj[c]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    b.resize(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> b[i];
    }

    adj.resize(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    sz.resize(N + 1, 0);
    removed.resize(N + 1, false);

    decompose(1);

    cout << total_ans % MOD << "\n";
    return 0;
}
