# Problema C: Into the Onion

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Rafael García
- **Dificultad Estimada:** Media-Alta (Div 2D / Div 1B)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [C_Into_The_Onion.cpp](../../inputs/solutions/C_Into_The_Onion.cpp)

---

## 1. Deconstrucción del Enunciado

Un grupo de biólogos estudia la estructura concéntrica de una cebolla identificando `N` células (`1 <= N <= 3000`) en el plano `xy` con coordenadas enteras `(x_i, y_i)` (`-10^8 <= x_i, y_i <= 10^8`) y un valor medido `w_i` (`1 <= w_i <= 10^6`). No hay dos células en la misma posición.

La cebolla se organiza en capas concéntricas `L_1, L_2, ..., L_K`:
- La capa exterior `L_1` está formada por todas las células ubicadas sobre la frontera del casco convexo mínimo que contiene a las `N` células (tanto vértices extremos como puntos colineales sobre las aristas del polígono).
- Tras remover las células de `L_1`, la siguiente capa `L_2` se obtiene de la misma forma sobre las células restantes. El proceso de pelado se repite sucesivamente hasta agotar los puntos. La última capa obtenida `L_K` se denomina el corazón de la cebolla (*heart of the onion*).

Un marcador químico se introduce en alguna célula de la capa exterior `L_1` (recolectando su valor `w`) y puede propagarse paso a paso hacia capas interiores contiguas:
- Para pasar de una célula `u` en la capa `L_t` a una célula `v` en la capa `L_{t+1}`, la distancia euclidiana entre ambas debe satisfacer:
  `dist(u, v) <= (3 / 2) * d(L_t, L_{t+1})`
  donde `d(L_t, L_{t+1})` es la distancia mínima absoluta entre cualquier célula de `L_t` y cualquier célula de `L_{t+1}`.
- El valor del experimento es la suma total de los valores `w` de las células visitadas a lo largo del camino desde `L_1` hasta `L_K`.

Se debe calcular el valor máximo posible alcanzable al llegar al corazón `L_K`. Si ninguna propagación válida logra alcanzar `L_K`, imprimir `-1`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`N <= 3000`:** En problemas de geometría computacional, `N = 3000` descarta enfoques de `O(N^3)`, pero permite holgadamente algoritmos de complejidad cuadrática `O(N^2)`, con hasta `~9 * 10^6` operaciones elementales.
- **Capas concéntricas convexas (*Convex Layers / Onion Peeling*):** Algoritmo clásico de pelado de cascos convexos sucesivos (*Monotone Chain Convex Hull*).
- **Transición estrictamente de `L_t` a `L_{t+1}`:** La propagación es acíclica y unidireccional entre capas contiguas, lo que garantiza una formulación directa mediante **Programación Dinámica por Capas**.
- **Cálculo de distancias con factor `1.5`:** Para evitar imprecisiones de punto flotante en comparaciones geométricas, elevamos al cuadrado:
  `dist(u, v) <= 1.5 * d <=> dist^2(u, v) <= 2.25 * d^2 <=> 4 * dist^2(u, v) <= 9 * d^2`.
  Esto permite operar con aritmética entera exacta de 64 bits (`long long`).

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Fase 1: Pelado de Capas (*Onion Peeling*)
Para el conjunto de puntos restantes `rem`:
1. Calculamos el casco convexo estricto (vértices no colineales) usando el algoritmo de la cadena monótona (*Andrew's Monotone Chain*) en `O(|rem| log |rem|)`.
2. Para cada punto `p in rem`, verificamos si pertenece a la frontera del polígono:
   - Si el casco tiene 1 punto, ese punto es la capa entera.
   - Si tiene 2 o más vértices, un punto `p` pertenece a la frontera si existe alguna arista `(a, b)` del casco tal que `cross(a, b, p) == 0` y `p` se encuentra dentro de la caja delimitadora de `[a, b]`.
3. Los puntos sobre la frontera forman la capa actual `L_t`, y se eliminan de `rem`.
4. El proceso termina cuando `rem` queda vacío.

### Fase 2: Programación Dinámica entre Capas Contiguas
Sea `best[v]` el valor acumulado máximo para llegar a la célula `v`:
- **Caso base:** Para toda célula `u in L_0` (capa exterior), `best[u] = w_u`. Para las demás células, inicializamos `best[v] = -1` (inalcanzable).
- **Paso inductivo de `L_t` a `L_{t+1}`:**
  1. Hallamos la distancia mínima al cuadrado entre las capas:
     `d2 = min_{u in L_t, v in L_{t+1}} ((x_u - x_v)^2 + (y_u - y_v)^2)`
  2. Para cada célula `v in L_{t+1}`:
     Buscamos el predecesor `u in L_t` con `best[u] != -1` que maximice `best[u]` sujeto a:
     `4 * dist^2(u, v) <= 9 * d2`
  3. Si existe al menos un predecesor válido con valor `bp`, entonces `best[v] = bp + w_v`. De lo contrario, `best[v] = -1`.

### Resultado Final
Al alcanzar la última capa `L_{K-1}` (el corazón de la cebolla):
`ans = max_{v in L_{K-1}} best[v]`
Si todas las células de `L_{K-1}` tienen `best[v] == -1`, la respuesta es `-1`.

### Análisis de Complejidad
- En cada capa `t`, comparar todos los pares entre `L_t` y `L_{t+1}` toma `O(|L_t| * |L_{t+1}|)`.
- Sumando sobre todas las capas contiguas:
  `sum_{t=0}^{K-2} |L_t| * |L_{t+1}| <= (sum |L_t|)^2 = N^2`.
- Por tanto, la complejidad global es estrictamente `O(N^2)` en tiempo y `O(N)` en espacio.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>

using namespace std;
using ll = long long;

struct Pt {
    ll x, y;
};

// Producto cruz: (a - o) x (b - o)
ll cross(const Pt& o, const Pt& a, const Pt& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// Casco convexo estricto (Monotone Chain). Devuelve índices de vértices extremos.
vector<int> hull(const vector<Pt>& pt, vector<int> id) {
    sort(id.begin(), id.end(), [&](int a, int b) {
        return pt[a].x < pt[b].x || (pt[a].x == pt[b].x && pt[a].y < pt[b].y);
    });
    if (id.size() <= 2) return id;

    vector<int> h(2 * id.size());
    int k = 0;
    for (int i : id) {
        while (k >= 2 && cross(pt[h[k - 2]], pt[h[k - 1]], pt[i]) <= 0) k--;
        h[k++] = i;
    }
    for (int t = static_cast<int>(id.size()) - 2, lo = k + 1; t >= 0; t--) {
        int i = id[t];
        while (k >= lo && cross(pt[h[k - 2]], pt[h[k - 1]], pt[i]) <= 0) k--;
        h[k++] = i;
    }
    h.resize(k - 1);
    return h;
}

// Verifica si el punto q yace exactamente sobre el segmento ab
bool onSegment(const Pt& a, const Pt& b, const Pt& q) {
    return cross(a, b, q) == 0 &&
           min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= q.y && q.y <= max(a.y, b.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != 0) {
        vector<Pt> pt(n);
        vector<ll> w(n);
        for (int i = 0; i < n; i++) {
            cin >> pt[i].x >> pt[i].y >> w[i];
        }

        // 1) Extracción de capas concéntricas (Onion Peeling)
        vector<vector<int>> layers;
        vector<int> rem(n);
        iota(rem.begin(), rem.end(), 0);

        while (!rem.empty()) {
            vector<int> h = hull(pt, rem), layer, rest;
            for (int i : rem) {
                bool on = (h.size() == 1);
                for (size_t e = 0; e < h.size() && !on; e++) {
                    if (onSegment(pt[h[e]], pt[h[(e + 1) % h.size()]], pt[i])) {
                        on = true;
                    }
                }
                (on ? layer : rest).push_back(i);
            }
            layers.push_back(layer);
            rem = rest;
        }

        // 2) Programación Dinámica capa por capa
        int K = layers.size();
        vector<ll> best(n, -1);
        for (int i : layers[0]) best[i] = w[i];

        for (int t = 0; t + 1 < K; t++) {
            const auto& A = layers[t];
            const auto& B = layers[t + 1];

            // Distancia euclidiana mínima al cuadrado entre capas
            ll d2 = numeric_limits<ll>::max();
            for (int u : A) {
                for (int v : B) {
                    ll dx = pt[u].x - pt[v].x, dy = pt[u].y - pt[v].y;
                    d2 = min(d2, dx * dx + dy * dy);
                }
            }

            // Transición: dist <= 1.5 * d <=> 4 * dist^2 <= 9 * d2
            for (int v : B) {
                ll bp = -1;
                for (int u : A) {
                    if (best[u] < 0) continue;
                    ll dx = pt[u].x - pt[v].x, dy = pt[u].y - pt[v].y;
                    if (4 * (dx * dx + dy * dy) <= 9 * d2) {
                        bp = max(bp, best[u]);
                    }
                }
                best[v] = (bp < 0) ? -1 : bp + w[v];
            }
        }

        // 3) Máximo acumulado al corazón de la cebolla
        ll ans = -1;
        for (int v : layers[K - 1]) ans = max(ans, best[v]);
        cout << ans << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Exclusión de Puntos Colineales de la Frontera:**
   Un casco convexo estándar suele descartar puntos colineales intermedios. El enunciado especifica explícitamente que la capa contiene **todas** las células sobre la frontera, no solo los vértices del polígono. Omitir la prueba `onSegment()` altera la partición de capas y produce respuestas incorrectas.
2. **Pérdida de Precisión por `double` y `sqrt`:**
   Calcular `sqrt(dx*dx + dy*dy) <= 1.5 * sqrt(d2)` introduce errores de redondeo de punto flotante en bordes exactos. Multiplicar cruzado `4 * dist^2 <= 9 * d2` garantiza exactitud absoluta con enteros de 64 bits.
3. **Desbordamiento de 32 bits en Coordenadas:**
   Como `|x_i|, |y_i| <= 10^8`, las diferencias pueden alcanzar `2 * 10^8`, cuyo cuadrado es `4 * 10^{16}`. Esto desborda ampliamente un entero de 32 bits (`2 * 10^9`). Toda la geometría debe realizarse con `long long`.
