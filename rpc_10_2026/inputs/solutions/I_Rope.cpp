#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double INF = 1e18;

struct Pt {
    long long x, y;
};

long long cross(Pt a, Pt b, Pt c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist(Pt a, Pt b) {
    return hypot((double)(a.x - b.x), (double)(a.y - b.y));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    double r;
    if (!(cin >> n >> r)) return 0;

    vector<Pt> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    // Ordenar puntos de abajo hacia arriba y de izquierda a derecha
    sort(p.begin(), p.end(), [](const Pt& a, const Pt& b) {
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    });

    int ans = 1; // Siempre se puede capturar 1 vaca con longitud 0 <= r

    // Fijar el vértice más bajo (y más a la izquierda en caso de empate) p0 = p[s]
    for (int s = 0; s < n; ++s) {
        Pt p0 = p[s];
        vector<Pt> pts;
        for (int i = s + 1; i < n; ++i) {
            pts.push_back(p[i]);
        }

        int m = (int)pts.size();
        if (m == 0) continue;

        // Ordenar por ángulo polar en sentido antihorario alrededor de p0
        sort(pts.begin(), pts.end(), [&](const Pt& a, const Pt& b) {
            return cross(p0, a, b) > 0;
        });

        vector<double> d0(m);
        vector<vector<double>> d(m, vector<double>(m, 0.0));
        for (int i = 0; i < m; ++i) {
            d0[i] = dist(p0, pts[i]);
            for (int j = i + 1; j < m; ++j) {
                d[i][j] = dist(pts[i], pts[j]);
            }
        }

        // Precalcular cuántos puntos quedan estrictamente dentro del triángulo (p0, pts[i], pts[j])
        vector<vector<int>> inside(m, vector<int>(m, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                int cnt = 0;
                for (int k = i + 1; k < j; ++k) {
                    if (cross(pts[i], pts[j], pts[k]) > 0) {
                        cnt++;
                    }
                }
                inside[i][j] = cnt;
            }
        }

        // dp[i][c]: mínimo perímetro abierto desde p0 hasta pts[i] capturando c vacas
        vector<vector<double>> dp(m, vector<double>(m + 2, INF));
        for (int i = 0; i < m; ++i) {
            dp[i][2] = d0[i];
        }

        for (int i = 0; i < m; ++i) {
            for (int c = 2; c <= i + 2; ++c) {
                if (dp[i][c] >= INF / 2) continue;
                if (dp[i][c] + d0[i] <= r) {
                    ans = max(ans, c);
                }
                double cur = dp[i][c];
                for (int j = i + 1; j < m; ++j) {
                    int nc = c + 1 + inside[i][j];
                    double nd = cur + d[i][j];
                    if (nd < dp[j][nc]) {
                        dp[j][nc] = nd;
                    }
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
