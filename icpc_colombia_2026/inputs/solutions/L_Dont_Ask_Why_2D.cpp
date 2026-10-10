#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
using Graph = array<uint16_t, MAXN>;            // adj[i]: contactos del aminoácido i

int bestC[MAXN + 1][MAXN + 1];
string bestSeq[MAXN + 1][MAXN + 1], bestFold[MAXN + 1][MAXN + 1];
array<map<Graph, string>, MAXN + 1> seen;        // grafo de contactos -> un plegado que lo produce
Graph adj{};
array<int, MAXN> px{}, py{};
map<pair<int, int>, int> who;                    // celda ocupada -> índice
string path;

const array<int, 4> DX = {1, -1, 0, 0}, DY = {0, 0, 1, -1};
const string DC = "RLUD";

void dfs(int n, bool turned) {                   // n aminoácidos colocados
    seen[n].emplace(adj, path);                  // guarda sólo el primero de cada grafo
    if (n == MAXN) return;
    for (int d = 0; d < 4; d++) {
        if (n == 1 && d != 0) continue;              // simetría: primer paso R
        if (!turned && d != 0 && d != 2) continue;   // simetría: primer giro U
        int nx = px[n - 1] + DX[d], ny = py[n - 1] + DY[d];
        if (who.count({nx, ny})) continue;
        px[n] = nx; py[n] = ny;
        path.push_back(DC[d]);
        vector<int> added;
        for (int e = 0; e < 4; e++) {
            auto it = who.find({nx + DX[e], ny + DY[e]});
            if (it != who.end() && it->second <= n - 2) {   // vecino en la rejilla, no consecutivo
                int j = it->second;
                adj[n] |= 1 << j; adj[j] |= 1 << n;
                added.push_back(j);
            }
        }
        who[{nx, ny}] = n;
        dfs(n + 1, turned || d == 2);
        who.erase({nx, ny});
        for (int j : added) { adj[n] &= ~(1 << j); adj[j] &= ~(1 << n); }
        path.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (auto& row : bestC) fill(begin(row), end(row), -1);
    who[{0, 0}] = 0;
    dfs(1, false);

    for (int n = 1; n <= MAXN; n++) {
        for (const auto& [g, fold] : seen[n]) {
            vector<int> vs;                              // aminoácidos con al menos un contacto
            for (int i = 0; i < n; i++) if (g[i]) vs.push_back(i);
            int m = vs.size(), full = 1 << m;
            vector<int> pos(n, -1);
            for (int t = 0; t < m; t++) pos[vs[t]] = t;
            vector<int> ca(m, 0);                        // adyacencia reindexada a 0..m-1
            for (int t = 0; t < m; t++)
                for (int i = 0; i < n; i++)
                    if ((g[vs[t]] >> i) & 1) ca[t] |= 1 << pos[i];
            // e[S] = aristas dentro de S; low[S] = índice del bit más bajo; pc[S] = |S|
            vector<int> e(full, 0), low(full, 0), pc(full, 0), bk(m + 1, -1), bm(m + 1, 0);
            for (int S = 1; S < full; S++) {
                low[S] = (S & 1) ? 0 : low[S >> 1] + 1;
                pc[S] = pc[S >> 1] + (S & 1);
                int R = S & (S - 1);
                e[S] = e[R] + static_cast<int>(bitset<16>(ca[low[S]] & R).count());
            }
            for (int S = 0; S < full; S++)
                if (e[S] > bk[pc[S]]) { bk[pc[S]] = e[S]; bm[pc[S]] = S; }
            for (int B = 0; B <= n; B++) {
                int c = -1, S = 0;
                for (int k = 0; k <= min(B, m); k++) if (bk[k] > c) { c = bk[k]; S = bm[k]; }
                if (c > bestC[n][B]) {
                    string seq(n, 'P');
                    int used = 0;
                    for (int t = 0; t < m; t++) if ((S >> t) & 1) { seq[vs[t]] = 'H'; used++; }
                    for (int i = 0; i < n && used < B; i++)       // relleno: más H nunca quita contactos
                        if (seq[i] == 'P') { seq[i] = 'H'; used++; }
                    bestC[n][B] = c; bestSeq[n][B] = seq; bestFold[n][B] = fold;
                }
            }
        }
    }
    int N, B;
    while (cin >> N >> B && (N != 0 || B != 0)) {
        cout << bestC[N][B] << ' ' << bestSeq[N][B];
        if (N > 1) cout << ' ' << bestFold[N][B];
        cout << '\n';
    }
}
