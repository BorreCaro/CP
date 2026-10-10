#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long B;
    int P;
    while (cin >> B >> P && (B != 0 || P != 0)) {
        priority_queue<long long> hired;            // costos de los prospectos contratados
        for (int i = 0; i < P; i++) {
            long long v;
            cin >> v;
            if (v > 0) { B += v; continue; }        // comercial: siempre conviene
            B += v;                                 // prospecto: contratación tentativa
            hired.push(-v);
            if (B < 0) {                            // nos pasamos: devolvemos al más caro
                B += hired.top();
                hired.pop();
            }
        }
        cout << hired.size() << '\n';
    }
}
