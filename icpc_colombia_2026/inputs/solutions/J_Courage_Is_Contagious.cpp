#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    while (cin >> n >> q && (n != 0 || q != 0)) {
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            cnt[k]++;
        }
        vector<int> f(n + 1);                          // f(c) = # soldados con k <= c
        for (int c = 0; c <= n; c++) f[c] = cnt[c] + (c > 0 ? f[c - 1] : 0);
        vector<int> up(n + 2), down(n + 1);
        up[n + 1] = n;
        for (int c = n; c >= 0; c--) up[c] = (f[c] == c) ? c : up[c + 1];                // menor punto fijo >= c
        for (int c = 0; c <= n; c++) down[c] = (f[c] == c) ? c : (c > 0 ? down[c - 1] : 0); // mayor punto fijo <= c
        while (q--) {
            int c0;
            cin >> c0;
            cout << (f[c0] >= c0 ? up[c0] : down[c0]) << '\n';
        }
    }
}
