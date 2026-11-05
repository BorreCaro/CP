#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Pt {
    double x, y;
};

double dist(Pt a, Pt b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Pt p[3];
    if (!(cin >> p[0].x >> p[0].y)) return 0;
    cin >> p[1].x >> p[1].y;
    cin >> p[2].x >> p[2].y;

    double ans = 1e18;

    for (int i = 0; i < 3; ++i) {
        Pt R = p[i];
        Pt P = p[(i + 1) % 3];
        Pt Q = p[(i + 2) % 3];

        double pq = dist(P, Q);

        // 1. Ángulo recto en P: proyectar R sobre la recta por P perpendicular a PQ
        // La distancia a esa recta es la proyección escalar de PR sobre PQ
        double dotP = (R.x - P.x) * (Q.x - P.x) + (R.y - P.y) * (Q.y - P.y);
        ans = min(ans, abs(dotP) / pq);

        // 2. Ángulo recto en Q: proyectar R sobre la recta por Q perpendicular a PQ
        double dotQ = (R.x - Q.x) * (P.x - Q.x) + (R.y - Q.y) * (P.y - Q.y);
        ans = min(ans, abs(dotQ) / pq);

        // 3. Ángulo recto en R': circunferencia de Thales con diámetro PQ
        Pt M = {(P.x + Q.x) / 2.0, (P.y + Q.y) / 2.0};
        double rad = pq / 2.0;
        ans = min(ans, abs(dist(R, M) - rad));
    }

    cout << fixed << setprecision(9) << ans << "\n";
    return 0;
}
