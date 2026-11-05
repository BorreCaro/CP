#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, p;
    if (!(cin >> k >> p)) return 0;

    vector<int> pow10(k + 1, 1 % p);
    for (int i = 1; i <= k; ++i) {
        pow10[i] = (pow10[i - 1] * 10) % p;
    }

    long long ans = 0;

    // dp_even[r]: cantidad de núcleos palindrómicos con ceros a la izquierda de longitud par actual con resto r mod p
    // dp_odd[r]: cantidad de núcleos palindrómicos con ceros a la izquierda de longitud impar actual con resto r mod p
    vector<int> dp_even(p, 0), dp_odd(p, 0);

    // Base par L = 0: núcleo vacío con valor 0
    dp_even[0] = 1;

    // Base impar L = 1: dígitos 0..9
    for (int d = 0; d <= 9; ++d) {
        int r = d % p;
        dp_odd[r] = (dp_odd[r] + 1) % MOD;
        if (r == 0) {
            ans = (ans + 1) % MOD;
        }
    }

    // Expandir longitudes L = 2 .. k desde adentro hacia afuera (L - 2 -> L)
    for (int L = 2; L <= k; ++L) {
        const vector<int>& prev_dp = (L % 2 == 0) ? dp_even : dp_odd;
        vector<int> next_dp(p, 0);
        int coeff = (pow10[L - 1] + 1) % p;

        for (int r = 0; r < p; ++r) {
            int ways = prev_dp[r];
            if (!ways) continue;
            int base_r = (r * 10) % p;

            for (int d = 0; d <= 9; ++d) {
                int nr = (base_r + d * coeff) % p;
                next_dp[nr] += ways;
                if (next_dp[nr] >= MOD) next_dp[nr] -= MOD;

                if (d >= 1 && nr == 0) {
                    ans += ways;
                    if (ans >= MOD) ans -= MOD;
                }
            }
        }

        if (L % 2 == 0) dp_even = move(next_dp);
        else dp_odd = move(next_dp);
    }

    cout << ans << "\n";
    return 0;
}
