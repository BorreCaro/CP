#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ¿distancia de edición(a, b) <= K?  DP en banda |i-j| <= K con corte temprano.
bool within(const string& a, const string& b, int K) {
    int n = a.size(), m = b.size();
    if (abs(n - m) > K) return false;
    if (K >= max(n, m)) return true;
    const int BIG = 1000;
    vector<int> prev(m + 1), cur(m + 1);
    iota(prev.begin(), prev.end(), 0);
    for (int i = 1; i <= n; i++) {
        fill(cur.begin(), cur.end(), BIG);
        int lo = max(0, i - K), hi = min(m, i + K), rowMin = BIG;
        if (lo == 0) cur[0] = i;
        for (int j = max(1, lo); j <= hi; j++)
            cur[j] = min({prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + (a[i - 1] != b[j - 1] ? 1 : 0)});
        for (int j = lo; j <= hi; j++) rowMin = min(rowMin, cur[j]);
        if (rowMin > K) return false;
        swap(prev, cur);
    }
    return prev[m] <= K;
}

struct Dinic {
    struct Edge { int to; ll cap; };
    vector<Edge> es;
    vector<vector<int>> g;
    vector<int> level, it;
    explicit Dinic(int n) : g(n), level(n), it(n) {}
    void add(int u, int v, ll c) {
        g[u].push_back(es.size()); es.push_back({v, c});
        g[v].push_back(es.size()); es.push_back({u, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u])
                if (es[id].cap > 0 && level[es[id].to] < 0) { level[es[id].to] = level[u] + 1; q.push(es[id].to); }
        }
        return level[t] >= 0;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = it[u]; i < static_cast<int>(g[u].size()); i++) {
            int id = g[u][i], v = es[id].to;
            if (es[id].cap > 0 && level[v] == level[u] + 1) {
                ll d = dfs(v, t, min(f, es[id].cap));
                if (d > 0) { es[id].cap -= d; es[id ^ 1].cap += d; return d; }
            }
        }
        return 0;
    }
    ll maxflow(int s, int t) {
        ll r = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (ll f = dfs(s, t, numeric_limits<ll>::max())) r += f;
        }
        return r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K, I, C;
    while (cin >> N >> K >> I >> C && (N != 0 || K != 0 || I != 0 || C != 0)) {
        vector<string> s(N);
        vector<ll> c(N);
        for (int i = 0; i < N; i++) cin >> s[i] >> c[i];
        vector<int> type(N, 0);                   // 0 normal, 1 infectado, 2 crítico
        for (int i = 0; i < I; i++) { int p; cin >> p; type[p - 1] = 1; }
        for (int i = 0; i < C; i++) { int q; cin >> q; type[q - 1] = 2; }

        const ll INF = 1'000'000'000'000'000'000LL;
        int S = 2 * N, T = 2 * N + 1;             // i_in = 2i, i_out = 2i+1
        Dinic din(2 * N + 2);
        for (int i = 0; i < N; i++) din.add(2 * i, 2 * i + 1, type[i] == 0 ? c[i] : INF);
        for (int i = 0; i < N; i++) {
            if (type[i] == 1) din.add(S, 2 * i, INF);
            if (type[i] == 2) din.add(2 * i + 1, T, INF);
        }
        bool impossible = false;
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++) {
                if (type[i] == type[j] && type[i] != 0) continue;
                if (!within(s[i], s[j], K)) continue;
                if (type[i] + type[j] == 3) impossible = true;   // infectado junto a crítico
                din.add(2 * i + 1, 2 * j, INF);
                din.add(2 * j + 1, 2 * i, INF);
            }
        cout << (impossible ? -1 : din.maxflow(S, T)) << '\n';
    }
}
