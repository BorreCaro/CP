#include <bits/stdc++.h>
using namespace std;
// Buscamos 2 <= a <= b <= c con  a*b*c - (a+b+c) = m,  m = n-3.
// Para (a,b) fijos: c*(ab-1) = m + a + b  ->  c queda determinado.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    while (cin >> n && n != 0) {
        long long m = n - 3;
        bool found = false;
        for (long long a = 2; !found && a * a * a - 3 * a <= m; a++) {
            for (long long b = a; ; b++) {
                if (m + a + b < b * (a * b - 1)) break;      // c >= b ya no es posible
                long long num = m + a + b, den = a * b - 1;
                if (num % den == 0 && num / den >= b) {
                    cout << a << ' ' << b << ' ' << num / den << '\n';
                    found = true;
                    break;
                }
            }
        }
        if (!found) cout << "IMPOSSIBLE\n";
    }
}
