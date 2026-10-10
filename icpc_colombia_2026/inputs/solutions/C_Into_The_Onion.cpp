#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Pt { ll x, y; };
ll cross(const Pt& o, const Pt& a, const Pt& b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); }

// Casco convexo estricto (sin colineales), monotone chain. Devuelve índices.
vector<int> hull(const vector<Pt>& pt, vector<int> id) {
    sort(id.begin(), id.end(), [&](int a, int b) {
        return pt[a].x < pt[b].x || (pt[a].x == pt[b].x && pt[a].y < pt[b].y);
    });
    if (id.size() <= 2) return id;
    vector<int> h(2 * id.size());
    int k = 0;
    for (int i : id) {
        while (k >= 2 && cross(pt[h[k - 2]], pt[h[k - 1]], pt[i]) <= 0) k--;
        h[k++] = i;
    }
    for (int t = static_cast<int>(id.size()) - 2, lo = k + 1; t >= 0; t--) {
        int i = id[t];
        while (k >= lo && cross(pt[h[k - 2]], pt[h[k - 1]], pt[i]) <= 0) k--;
        h[k++] = i;
    }
    h.resize(k - 1);
    return h;
}

bool onSegment(const Pt& a, const Pt& b, const Pt& q) {
    return cross(a, b, q) == 0 && min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x)
                               && min(a.y, b.y) <= q.y && q.y <= max(a.y, b.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != 0) {
        vector<Pt> pt(n);
        vector<ll> w(n);
        for (int i = 0; i < n; i++) cin >> pt[i].x >> pt[i].y >> w[i];

        // 1) Pelar capas: capa = puntos sobre la frontera del casco de los que quedan
        vector<vector<int>> layers;
        vector<int> rem(n);
        iota(rem.begin(), rem.end(), 0);
        while (!rem.empty()) {
            vector<int> h = hull(pt, rem), layer, rest;
            for (int i : rem) {
                bool on = (h.size() == 1);
                for (size_t e = 0; e < h.size() && !on; e++)
                    if (onSegment(pt[h[e]], pt[h[(e + 1) % h.size()]], pt[i])) on = true;
                (on ? layer : rest).push_back(i);
            }
            layers.push_back(layer);
            rem = rest;
        }

        // 2) DP capa por capa (best = -1 significa inalcanzable)
        int K = layers.size();
        vector<ll> best(n, -1);
        for (int i : layers[0]) best[i] = w[i];
        for (int t = 0; t + 1 < K; t++) {
            const auto& A = layers[t];
            const auto& B = layers[t + 1];
            ll d2 = numeric_limits<ll>::max();    // distancia mínima al cuadrado entre capas
            for (int u : A)
                for (int v : B) {
                    ll dx = pt[u].x - pt[v].x, dy = pt[u].y - pt[v].y;
                    d2 = min(d2, dx * dx + dy * dy);
                }
            for (int v : B) {
                ll bp = -1;
                for (int u : A) {
                    if (best[u] < 0) continue;
                    ll dx = pt[u].x - pt[v].x, dy = pt[u].y - pt[v].y;
                    if (4 * (dx * dx + dy * dy) <= 9 * d2) bp = max(bp, best[u]);   // dist <= 1.5 d
                }
                best[v] = (bp < 0) ? -1 : bp + w[v];
            }
        }
        ll ans = -1;
        for (int v : layers[K - 1]) ans = max(ans, best[v]);
        cout << ans << '\n';
    }
}
