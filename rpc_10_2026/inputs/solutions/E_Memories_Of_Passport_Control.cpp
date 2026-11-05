// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, s;
    cin >> k >> s;
    int a = s / k;
    cout << a + s % k << "\n";
    return 0;
}
