#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1'000'000'007LL;
const int MX = 1'000'005;
vector<ll> fact(MX), invFact(MX);

ll power(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    for (; e > 0; e >>= 1) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
    }
    return r;
}
ll C(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}
// Formas de elegir K con AL MENOS t de un grupo de tamaño g (los otros N-g son "resto")
ll atLeast(int N, int K, int g, int t) {
    ll s = 0;
    for (int a = t; a <= min(g, K); a++) s = (s + C(g, a) * C(N - g, K - a)) % MOD;
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fact[0] = 1;
    for (int i = 1; i < MX; i++) fact[i] = fact[i - 1] * i % MOD;
    invFact[MX - 1] = power(fact[MX - 1], MOD - 2);
    for (int i = MX - 1; i > 0; i--) invFact[i - 1] = invFact[i] * i % MOD;

    int N, K;
    while (cin >> N >> K && (N != 0 || K != 0)) {
        vector<int> A(N);
        for (int& x : A) cin >> x;
        sort(A.begin(), A.end());
        int med = A[(N - 1) / 2];
        int L = lower_bound(A.begin(), A.end(), med) - A.begin();   // menores
        int G = A.end() - upper_bound(A.begin(), A.end(), med);     // mayores
        int h = (K - 1) / 2;
        ll total = C(N, K);
        ll bad = (atLeast(N, K, L, h + 1) + atLeast(N, K, G, h + 1)) % MOD;
        ll good = ((total - bad) % MOD + MOD) % MOD;
        cout << good * power(total, MOD - 2) % MOD << '\n';
    }
}
