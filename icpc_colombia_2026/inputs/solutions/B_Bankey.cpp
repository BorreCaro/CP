#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        string s;
        cin >> s;
        vector<long long> pre(n + 1, 0);    // pre[i] = d[i] + d[i-2] + d[i-4] + ...
        long long best = 0;
        for (int i = 1; i <= n; i++) {
            pre[i] = (s[i - 1] - '0') + (i >= 2 ? pre[i - 2] : 0);
            int j = i - 2 * m;                // ventana: d[i] + ... + d[i-2(M-1)]
            long long sum = pre[i] - (j >= 1 ? pre[j] : 0);
            best = max(best, sum);
        }
        cout << best << '\n';
    }
}
