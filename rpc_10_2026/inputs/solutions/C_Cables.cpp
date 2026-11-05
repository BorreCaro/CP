#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

const uint64_t MOD = 1000000007ULL;
const uint64_t MOD2 = 16ULL * MOD * MOD;

uint64_t power(uint64_t base, uint64_t exp) {
    uint64_t res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

uint64_t modInverse(uint64_t n) {
    return power(n, MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    int dim = n - 1; // La suma de grados netos es 0, por lo que las primeras n-1 coordenadas determinan la n-ésima
    vector<vector<uint64_t>> B(dim, vector<uint64_t>(dim, 0));
    vector<int> pos(dim, 0);

    int best_len = n + 5;
    vector<int> deg(n + 1, 0);
    vector<int> touched;
    touched.reserve(205);

    for (int j = 1; j <= k; ++j) {
        int m;
        cin >> m;
        touched.clear();
        for (int e = 0; e < m; ++e) {
            int u, v;
            cin >> u >> v;
            deg[u] -= 1;
            deg[v] += 1;
            touched.push_back(u);
            touched.push_back(v);
        }

        if (best_len == 1) {
            for (int x : touched) deg[x] = 0;
            continue;
        }

        vector<uint64_t> vec(dim, 0);
        bool all_zero = true;
        for (int x : touched) {
            int d = deg[x];
            deg[x] = 0;
            if (d != 0) {
                all_zero = false;
                if (x <= dim) {
                    vec[x - 1] = (d < 0) ? (MOD - (uint64_t)(-d) % MOD) % MOD : (uint64_t)d % MOD;
                }
            }
        }

        if (all_zero) {
            best_len = 1;
            continue;
        }

        int cur_pos = j;
        bool independent = false;

        for (int c = 0; c < dim; ++c) {
            if (vec[c] >= MOD) vec[c] %= MOD;
            if (vec[c] == 0) continue;

            if (cur_pos > pos[c]) {
                // Normalizar vec para que vec[c] == 1
                uint64_t inv = modInverse(vec[c]);
                vec[c] = 1;
                for (int col = c + 1; col < dim; ++col) {
                    if (vec[col] >= MOD) vec[col] %= MOD;
                    vec[col] = (vec[col] * inv) % MOD;
                }

                // Si el vector existente en B[c] es vacío o ya demasiado antiguo para mejorar best_len,
                // simplemente lo sobreescribimos y terminamos
                if (pos[c] == 0 || j - pos[c] + 1 >= best_len) {
                    B[c] = move(vec);
                    pos[c] = cur_pos;
                    independent = true;
                    break;
                }

                swap(vec, B[c]);
                swap(cur_pos, pos[c]);

                // Ambos vec[c] y B[c][c] son 1 tras el intercambio
                vec[c] = 0;
                for (int col = c + 1; col < dim; ++col) {
                    vec[col] += MOD - B[c][col];
                }
            } else {
                uint64_t factor = MOD - vec[c];
                vec[c] = 0;
                const auto& row = B[c];
                for (int col = c + 1; col < dim; ++col) {
                    vec[col] += factor * row[col];
                    if (vec[col] >= MOD2) vec[col] -= MOD2;
                }
            }
        }

        if (!independent) {
            best_len = min(best_len, j - cur_pos + 1);
        }
    }

    if (best_len > n) {
        cout << -1 << "\n";
    } else {
        cout << best_len << "\n";
    }

    return 0;
}
