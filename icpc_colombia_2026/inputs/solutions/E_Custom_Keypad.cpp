#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max() / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        int B = stoi(line);
        if (B == 0) break;
        string text;
        getline(cin, text);
        array<ll, 26> f{};
        for (char c : text)
            if (c >= 'a' && c <= 'z') f[c - 'a']++;

        // cost[l][r]: letras l..r en un mismo botón
        array<array<ll, 26>, 26> cost{};
        for (int l = 0; l < 26; l++) {
            ll s = 0;
            for (int r = l; r < 26; r++) {
                s += f[r] * (r - l + 1);
                cost[l][r] = s;
            }
        }
        // dp[j][p] = mínimo para las p primeras letras en j botones
        vector<vector<ll>> dp(B + 1, vector<ll>(27, INF));
        dp[0][0] = 0;
        for (int j = 1; j <= B; j++)
            for (int p = j; p <= 26; p++)
                for (int s = j - 1; s < p; s++)
                    if (dp[j - 1][s] < INF) dp[j][p] = min(dp[j][p], dp[j - 1][s] + cost[s][p - 1]);

        // Reconstrucción de derecha a izquierda: inicio del último botón lo más a la derecha posible
        set<int> sep;
        int p = 26;
        for (int j = B; j >= 2; j--)
            for (int s = p - 1; s >= j - 1; s--)
                if (dp[j - 1][s] < INF && dp[j - 1][s] + cost[s][p - 1] == dp[j][p]) {
                    sep.insert(s);
                    p = s;
                    break;
                }
        string out;
        for (int i = 0; i < 26; i++) {
            if (sep.count(i)) out += '|';
            out += static_cast<char>('a' + i);
        }
        cout << out << '\n';
    }
}
