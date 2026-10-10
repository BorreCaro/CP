# Problema F: Heist

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Julián Badillo
- **Dificultad Estimada:** Alta (Div 1C / Div 2E)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [F_Heist.cpp](../../inputs/solutions/F_Heist.cpp)

---

## 1. Deconstrucción del Enunciado

Danny O'Shea planea el golpe de su vida en la galería de máxima seguridad *Extremely Securest Room*, un recinto rectangular de dimensiones `W x L` (`1 <= W, L <= 1000`).
La habitación está protegida por `Z` rayos láser (`1 <= Z <= 100`), cada uno definido como un segmento de recta entre un emisor `E = (ex, ey)` y un receptor `R = (rx, ry)` ubicados sobre las paredes del cuarto.

Los láseres dividen el cuarto en una serie de celdas poligonales convexas. Se busca el **punto más seguro** `(sx, sy)` para aterrizar desde el techo, definido como aquel punto que maximiza la distancia euclidiana `d` al láser o pared más cercano.
**Criterios de desempate estrictos en cascada:**
1. Mayor distancia `d` a cualquier láser o pared.
2. Si hay empate, elegir el punto ubicado en la celda poligonal de **mayor área**.
3. Si aún persiste el empate, elegir el punto **más cercano al origen** `(0, 0)`.

Se deben imprimir las coordenadas `sx, sy` y la distancia `d` formateadas a dos cifras decimales. La entrada finaliza con la línea `0 0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`Z <= 100` y división por rectas:** Un conjunto de `Z` rectas que cruzan un rectángulo genera a lo sumo `(Z^2 + Z + 2) / 2 ~ 5000` celdas poligonales convexas (en la práctica muchas menos, ya que los segmentos van de pared a pared).
- **Distancia al borde de un polígono convexo:** Encontrar el punto más alejado de las paredes y láseres dentro de una celda convexa equivale a hallar el **centro del círculo inscrito máximo** (*Chebyshev Center* del polígono).
- **Monotonicidad de la región contraída (*Erosion / Shrink*):** Desplazar todas las aristas de un polígono convexo hacia el interior una distancia `r` produce un subpolígono convexo más pequeño que se encoge monótonamente hasta vaciarse. Esto dispara inmediatamente **Búsqueda Binaria de Respuesta + Recorte de Polígonos de Sutherland-Hodgman**.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Etapa 1: Partición Espacial mediante Sutherland-Hodgman
Iniciamos con una única celda convexa: el rectángulo `[0, W] x [0, L]`.
Para cada láser `(E, R)`, consideramos la recta orientada que pasa por `E` con vector director `d = R - E`.
Para un punto `p`, su posición relativa respecto a la recta viene dada por el signo de:
`side(p) = cross(d, p - E)`

Para cada celda poligonal existente:
- Si todos sus vértices caen a un solo lado de la recta, la celda no es dividida.
- Si la recta atraviesa la celda (existen vértices con `side > 0` y otros con `side < 0`), recortamos la celda usando el algoritmo clásico de **Sutherland-Hodgman** en dos semiceldas: una con `side >= 0` y otra con `-side >= 0`.

### Etapa 2: Radio Máximo del Círculo Inscrito (Búsqueda Binaria)
Para una celda convexa `c`:
- Para un radio candidato `r`, cada arista dirigida `a -> b` de longitud `len = hypot(b.x - a.x, b.y - a.y)` define un semiplano interior a distancia `r`:
  `cross(b - a, p - a) / len >= r`
- Recortamos sucesivamente el polígono contra cada una de estas cotas interiores.
- Si el polígono resultante `region(r)` es no vacío (área `> 0`), el radio `r` es factible.
- Realizamos 60 iteraciones de búsqueda binaria en el intervalo `[0, max(W, L)]`, garantizando un error absoluto inferior a `10^{-15}`.

### Etapa 3: Selección del Punto Óptimo y Criterios de Desempate
Dentro del polígono contraído final `region(r_max)`:
- Todos los puntos en esta región tienen distancia al menos `r_max` a los bordes.
- El punto más cercano al origen `(0, 0)` se obtiene proyectando `(0, 0)` ortogonalmente sobre cada segmento del polígono contraído `[a, b]` y recortando al intervalo `t in [0, 1]`.
- Comparamos cada celda candidata aplicando la jerarquía:
  1. `abs(r - bestR) > 1e-6`: mayor radio `r`.
  2. `abs(area - bestArea) > 1e-6`: mayor área de la celda original.
  3. menor distancia de `p` al origen: `dot(p, p) < dot(bestP, bestP)`.

- **Complejidad Temporal:** `O(Z * |cells| * 60)`. Con `Z <= 100`, ejecuta en aproximadamente `0.15 s`.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <functional>
#include <algorithm>

using namespace std;
using D = double;
const D EPS = 1e-9;

struct Pt {
    D x, y;
};

Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
Pt operator+(Pt a, Pt b) { return {a.x + b.x, a.y + b.y}; }
Pt operator*(Pt a, D t) { return {a.x * t, a.y * t}; }
D cross(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
D dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }

using Poly = vector<Pt>;

// Algoritmo de recorte de Sutherland-Hodgman con predicado afín val(p) >= 0
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
    Poly res;
    for (Pt p : out) {
        if (res.empty() || !same(p, res.back())) res.push_back(p);
    }
    while (res.size() > 1 && same(res.front(), res.back())) res.pop_back();
    return res;
}

D area(const Poly& p) {
    D s = 0;
    for (size_t i = 0; i < p.size(); i++) {
        s += cross(p[i], p[(i + 1) % p.size()]);
    }
    return s / 2.0;
}

// Halla el punto en el polígono convexo más cercano al origen (0, 0)
Pt closestToOrigin(const Poly& p) {
    Pt best = p[0];
    D bd = dot(p[0], p[0]);
    for (size_t i = 0; i < p.size(); i++) {
        Pt a = p[i], ab = p[(i + 1) % p.size()] - a;
        D L2 = dot(ab, ab);
        D t = L2 > 0 ? clamp(-dot(a, ab) / L2, 0.0, 1.0) : 0.0;
        Pt q = a + ab * t;
        if (dot(q, q) < bd) {
            bd = dot(q, q);
            best = q;
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);

    int W, L, Z;
    while (cin >> W >> L >> Z && (W != 0 || L != 0 || Z != 0)) {
        // Inicializar con el rectángulo de la habitación
        vector<Poly> cells = {{{0, 0}, {D(W), 0}, {D(W), D(L)}, {0, D(L)}}};

        for (int z = 0; z < Z; z++) {
            int ex, ey, rx, ry;
            cin >> ex >> ey >> rx >> ry;
            Pt E{D(ex), D(ey)}, d = Pt{D(rx), D(ry)} - E;
            auto side = [&](Pt p) { return cross(d, p - E); };

            vector<Poly> next;
            for (const auto& c : cells) {
                D mn = 1e18, mx = -1e18;
                for (Pt p : c) {
                    mn = min(mn, side(p));
                    mx = max(mx, side(p));
                }
                // Si la recta corta estrictamente el interior del polígono
                if (mx > 1e-7 && mn < -1e-7) {
                    next.push_back(clip(c, side));
                    next.push_back(clip(c, [&](Pt p) { return -side(p); }));
                } else {
                    next.push_back(c);
                }
            }
            cells.swap(next);
        }

        // Búsqueda del centro de Chebyshev en cada celda
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
                D mid = (lo + hi) / 2.0;
                Poly q = shrink(mid);
                if (!q.empty()) {
                    lo = mid;
                    region = q;
                } else {
                    hi = mid;
                }
            }

            Pt p = closestToOrigin(region);
            D A = area(c), dist = sqrt(dot(p, p));

            bool better = false;
            if (abs(lo - bestR) > 1e-6) better = lo > bestR;
            else if (abs(A - bestA) > 1e-6) better = A > bestA;
            else better = dist < bestDist;

            if (better) {
                bestR = lo;
                bestA = A;
                bestDist = dist;
                bestP = p;
            }
        }

        cout << bestP.x + 1e-9 << ' ' << bestP.y + 1e-9 << ' ' << bestR + 1e-9 << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Vértices Duplicados o Degenerados tras el Recorte:**
   En operaciones repetidas de Sutherland-Hodgman con aritmética de punto flotante, intersecciones en vértices producen puntos idénticos a distancia `< EPS`. No limpiar vértices consecutivos degrada el cálculo de longitudes de aristas a divisiones por cero (`len < 1e-12`).
2. **Ignorar Criterios Secundarios de Desempate:**
   En habitaciones simétricas o divididas en cuadrícula regular, múltiples celdas tendrán exactamente el mismo radio máximo `r`. Si no se compara el área y la cercanía al origen `(0, 0)`, la solución fallará en los casos de prueba del juez.
3. **Imprecisión de Formato en Punto Flotante (`-0.00`):**
   Valores como `-1e-11` formateados con `fixed << setprecision(2)` pueden imprimirse como `-0.00`. Sumar un pequeño sesgo infinitesimal (`+ 1e-9`) garantiza estabilidad en la salida.
