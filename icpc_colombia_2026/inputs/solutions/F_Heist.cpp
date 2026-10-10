#include <bits/stdc++.h>
using namespace std;
using D = double;
const D EPS = 1e-9;

struct Pt { D x, y; };
Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
Pt operator+(Pt a, Pt b) { return {a.x + b.x, a.y + b.y}; }
Pt operator*(Pt a, D t) { return {a.x * t, a.y * t}; }
D cross(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
D dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
using Poly = vector<Pt>;

// Sutherland–Hodgman: conserva los puntos con val(p) >= 0 (val afín en p)
Poly clip(const Poly& pg, const function<D(Pt)>& val) {
    Poly out;
    int n = pg.size();
    for (int i = 0; i < n; i++) {
        Pt a = pg[i], b = pg[(i + 1) % n];
        D va = val(a), vb = val(b);
        bool ia = va >= -EPS, ib = vb >= -EPS;
        if (ia) out.push_back(a);
        if (ia != ib) out.push_back(a + (b - a) * (va / (va - vb)));
    }
    auto same = [](Pt p, Pt q) { return abs(p.x - q.x) + abs(p.y - q.y) <= 1e-12; };
    Poly res;                                   // quitar vértices repetidos
    for (Pt p : out)
        if (res.empty() || !same(p, res.back())) res.push_back(p);
    while (res.size() > 1 && same(res.front(), res.back())) res.pop_back();
    return res;
}

D area(const Poly& p) {
    D s = 0;
    for (size_t i = 0; i < p.size(); i++) s += cross(p[i], p[(i + 1) % p.size()]);
    return s / 2;
}

Pt closestToOrigin(const Poly& p) {
    Pt best = p[0];
    D bd = dot(p[0], p[0]);
    for (size_t i = 0; i < p.size(); i++) {
        Pt a = p[i], ab = p[(i + 1) % p.size()] - a;
        D L2 = dot(ab, ab);
        D t = L2 > 0 ? clamp(-dot(a, ab) / L2, 0.0, 1.0) : 0.0;
        Pt q = a + ab * t;
        if (dot(q, q) < bd) { bd = dot(q, q); best = q; }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);
    int W, L, Z;
    while (cin >> W >> L >> Z && (W != 0 || L != 0 || Z != 0)) {
        // 1) Partir el rectángulo con cada láser
        vector<Poly> cells = {{{0, 0}, {D(W), 0}, {D(W), D(L)}, {0, D(L)}}};
        for (int z = 0; z < Z; z++) {
            int ex, ey, rx, ry;
            cin >> ex >> ey >> rx >> ry;
            Pt E{D(ex), D(ey)}, d = Pt{D(rx), D(ry)} - E;
            auto side = [&](Pt p) { return cross(d, p - E); };
            vector<Poly> next;
            for (const auto& c : cells) {
                D mn = 1e18, mx = -1e18;
                for (Pt p : c) { mn = min(mn, side(p)); mx = max(mx, side(p)); }
                if (mx > 1e-7 && mn < -1e-7) {       // la recta atraviesa la celda
                    next.push_back(clip(c, side));
                    next.push_back(clip(c, [&](Pt p) { return -side(p); }));
                } else {
                    next.push_back(c);
                }
            }
            cells.swap(next);
        }
        // 2) Círculo inscrito máximo por celda (búsqueda binaria en r)
        D bestR = -1, bestA = -1, bestDist = 1e18;
        Pt bestP{0, 0};
        for (const auto& c : cells) {
            if (c.size() < 3 || area(c) < 1e-9) continue;
            auto shrink = [&](D r) {
                Poly q = c;
                for (size_t i = 0; i < c.size() && !q.empty(); i++) {
                    Pt a = c[i], ab = c[(i + 1) % c.size()] - a;
                    D len = sqrt(dot(ab, ab));
                    if (len < 1e-12) continue;
                    q = clip(q, [&](Pt p) { return cross(ab, p - a) / len - r; });
                }
                return q;
            };
            D lo = 0, hi = max(W, L);
            Poly region = c;
            for (int it = 0; it < 60; it++) {
                D mid = (lo + hi) / 2;
                Poly q = shrink(mid);
                if (!q.empty()) { lo = mid; region = q; }
                else hi = mid;
            }
            Pt p = closestToOrigin(region);
            D A = area(c), dist = sqrt(dot(p, p));
            bool better;
            if (abs(lo - bestR) > 1e-6) better = lo > bestR;        // 1º mayor distancia
            else if (abs(A - bestA) > 1e-6) better = A > bestA;      // 2º mayor área
            else better = dist < bestDist;                           // 3º más cerca de (0,0)
            if (better) { bestR = lo; bestA = A; bestDist = dist; bestP = p; }
        }
        cout << bestP.x + 1e-9 << ' ' << bestP.y + 1e-9 << ' ' << bestR + 1e-9 << '\n';
    }
}
