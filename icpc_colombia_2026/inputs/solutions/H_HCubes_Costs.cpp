#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long a, b;
    while (cin >> n >> a >> b && (n != 0 || a != 0 || b != 0)) {
        long long x = a ^ b, cost = 0;
        for (int i = 0; i < n; i++)
            if ((x >> i) & 1) cost += i + 1;     // cambiar el bit i cuesta i+1
        cout << cost << '\n';
    }
}
