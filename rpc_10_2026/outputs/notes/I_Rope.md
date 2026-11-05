# Problema I: Rope

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Difícil (Div 1B / Geometría Computacional + DP sobre Polígonos)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución: [I_Rope.cpp](../../inputs/solutions/I_Rope.cpp)

---

## 1. Deconstrucción del Enunciado

Dados `n` puntos en el plano (`3 <= n <= 100`, coordenadas enteras en `[-100, 100]`, sin dos puntos iguales ni tres colineales) y una cuerda de longitud `r` (`1 <= r <= 10000`), encontrar el máximo número de puntos que pueden quedar encerrados dentro o sobre el borde de una curva cerrada de longitud a lo sumo `r`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **Minimalidad de la Envolvente Convexa (Fórmula de Crofton):** La curva cerrada de menor longitud que encierra un subconjunto de puntos `S` es siempre el borde de su envolvente convexa `Conv(S)` (para `|S| = 2`, equivale al segmento recorrido de ida y vuelta con longitud `2 * d`).
- `n <= 100` **y no hay 3 puntos colineales:** Permite fijar el vértice más bajo `p_0` del polígono (`n` opciones), ordenar los puntos superiores por ángulo polar antihorario alrededor de `p_0`, y triangular el polígono desde `p_0` en triángulos disjuntos `Delta(p_0, pts[i], pts[j])`. Al no existir 3 puntos colineales, ningún punto de entrada cae sobre las diagonales internas `p_0 -> pts[i]`.

---

## 3. Técnicas y Conceptos Teóricos

Para cada punto pivote inferior `p_0`:

1. **Ordenamiento Polar Antihorario:**
   Filtramos los puntos con `y > p_0.y` (o `y == p_0.y && x > p_0.x`) y los ordenamos de modo que `cross(p_0, a, b) > 0`. Como todos están en un semiplano superior respecto a `p_0`, el barrido angular abarca menos de `180` grados y los sectores angulares `[theta(pts[i]), theta(pts[j])]` son estrictamente disjuntos.

2. **Precalculo de Puntos en Triángulos `inside[i][j]`:**
   Un punto `pts[k]` yace estrictamente dentro del triángulo `Delta(p_0, pts[i], pts[j])` (con `i < j`) si y solo si su ángulo polar está entre `i` y `j` (`i < k < j`) y queda del mismo lado del segmento dirigido `pts[i] -> pts[j]` que `p_0`, es decir:
   `cross(pts[i], pts[j], pts[k]) > 0`.

3. **Programación Dinámica por Cantidad de Vacas Capturadas:**
   Definimos `dp[i][c]` como la longitud mínima de la cadena poligonal abierta desde `p_0` hasta `pts[i]` que captura exactamente `c` puntos:
   - **Caso base:** `dp[i][2] = dist(p_0, pts[i])` (captura `p_0` y `pts[i]`).
   - **Transición (`i -> j` con `j > i`):**
     `nc = c + 1 + inside[i][j]`
     `dp[j][nc] = min(dp[j][nc], dp[i][c] + dist(pts[i], pts[j]))`.
   - **Cierre del ciclo (`pts[i] -> p_0`):** Si `dp[i][c] + dist(pts[i], p_0) <= r`, actualizamos `ans = max(ans, c)`.

---

## 4. Estrategia de Implementación Limpia

- **Complejidad Temporal:** `O(n^4)` con constante `1 / 24` (`~4 * 10^6` operaciones para `n = 100`, `< 0.01 s`).
- **Complejidad Espacial:** `O(n^2)`.

```cpp
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
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;

    sort(p.begin(), p.end(), [](const Pt& a, const Pt& b) {
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    });

    int ans = 1;

    for (int s = 0; s < n; ++s) {
        Pt p0 = p[s];
        vector<Pt> pts(p.begin() + s + 1, p.end());
        int m = (int)pts.size();
        if (m == 0) continue;

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

        vector<vector<int>> inside(m, vector<int>(m, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                int cnt = 0;
                for (int k = i + 1; k < j; ++k) {
                    if (cross(pts[i], pts[j], pts[k]) > 0) cnt++;
                }
                inside[i][j] = cnt;
            }
        }

        vector<vector<double>> dp(m, vector<double>(m + 2, INF));
        for (int i = 0; i < m; ++i) dp[i][2] = d0[i];

        for (int i = 0; i < m; ++i) {
            for (int c = 2; c <= i + 2; ++c) {
                if (dp[i][c] >= INF / 2) continue;
                if (dp[i][c] + d0[i] <= r) ans = max(ans, c);
                double cur = dp[i][c];
                for (int j = i + 1; j < m; ++j) {
                    int nc = c + 1 + inside[i][j];
                    double nd = cur + d[i][j];
                    if (nd < dp[j][nc]) dp[j][nc] = nd;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
```
