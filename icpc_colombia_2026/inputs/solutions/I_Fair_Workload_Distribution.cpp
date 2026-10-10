#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N;
    int D, Q;
    while (cin >> N >> D >> Q && (N != 0 || D != 0 || Q != 0)) {
        vector<ll> k(D + 1), M(D + 1);
        for (int i = 1; i <= D; i++) cin >> k[i] >> M[i];
        vector<int> qd(Q);
        vector<ll> qw(Q);
        for (int i = 0; i < Q; i++) cin >> qd[i] >> qw[i];

        vector<ll> xs = qw;                              // trabajadores consultados, comprimidos
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int S = xs.size();
        vector<ll> bit(S + 2, 0);                        // BIT: suma en rango, consulta en punto
        auto add = [&](int i, ll v) { for (i++; i <= S + 1; i += i & -i) bit[i] += v; };
        auto get = [&](int i) { ll r = 0; for (i++; i > 0; i -= i & -i) r += bit[i]; return r; };
        auto rangeAdd = [&](ll l, ll r) {                // +1 a todo w en [l, r]
            int li = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
            int ri = upper_bound(xs.begin(), xs.end(), r) - xs.begin();
            if (li < ri) { add(li, 1); add(ri, -1); }
        };

        vector<int> order(Q);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) { return qd[a] < qd[b]; });
        vector<ll> ans(Q);
        ll base = 0;                                     // suma de floor(M/N)
        int day = 0;
        for (int id : order) {
            while (day < qd[id]) {
                day++;
                base += M[day] / N;
                ll r = M[day] % N;
                if (r > 0) {
                    ll l = k[day], e = k[day] + r - 1;
                    if (e <= N) rangeAdd(l, e);
                    else { rangeAdd(l, N); rangeAdd(1, e - N); }
                }
            }
            int pos = lower_bound(xs.begin(), xs.end(), qw[id]) - xs.begin();
            ans[id] = base + get(pos);
        }
        for (ll x : ans) cout << x << '\n';
    }
}
