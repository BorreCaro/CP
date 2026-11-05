# Problema C: Cables

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Difícil (Div 1B / Álgebra Lineal Online)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución: [C_Cables.cpp](../../inputs/solutions/C_Cables.cpp)

---

## 1. Deconstrucción del Enunciado

Se tienen `n` computadoras (`2 <= n <= 100`) y una secuencia de `k` tipos de cables (`1 <= k <= 2 * 10^5`). Cada tipo `q` es un conjunto de aristas dirigidas `E_q`. Si se envía un flujo real `x_q` por todos los cables del tipo `q` (donde `x_q < 0` equivale a invertir la dirección de todas las aristas de `E_q`), el balance neto (flujo entrante menos flujo saliente) en cada computadora `v` aportado por el tipo `q` es:
`d^(q)_v * x_q`, donde `d^(q)_v = indeg_{E_q}(v) - outdeg_{E_q}(v)`.

Un bloque contiguo `[i, j]` de tipos de cables es balanceado si existen reales `x_i, ..., x_j` no todos nulos tales que:
`sum_{q = i}^j x_q * d^(q) = 0` en `R^n`.
Se pide hallar la longitud mínima `j - i + 1` de un bloque contiguo balanceado, o `-1` si no existe.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **Reducción de Flujo a Dependencia Lineal:** La condición `sum_{q = i}^j x_q * d^(q) = 0` con `x != 0` significa exactamente que los vectores de grado neto `d^(i), d^(i+1), ..., d^(j)` son **linealmente dependientes** en `R^n`.
- **Dimensión pequeña (`n <= 100`):** Como la suma de las coordenadas de cada vector `d^(q)` es cero (`sum_{v=1}^n d^(q)_v = 0`), todos los vectores habitan en un subespacio de dimensión `dim = n - 1 <= 99`. Por lo tanto, cualquier conjunto de `n` vectores es garantizadamente dependiente, y la respuesta (si existe) es siempre `<= n`.
- `k <= 2 * 10^5`: Para encontrar para cada extremo derecho `j` el mayor extremo izquierdo `i <= j` tal que `d^(i) .. d^(j)` sean linealmente dependientes, necesitamos mantener una **Base Lineal Online con Timestamps (Eliminación Gaussiana con reemplazo del más reciente)** módulo un primo grande `MOD = 10^9 + 7`.

---

## 3. Técnicas y Conceptos Teóricos

Mantenemos una base escalonada `B[0 .. dim - 1]` donde cada fila `c` tiene pivote `B[c][c] = 1` y almacena el índice temporal `pos[c]` del vector que ocupa ese pivote:

1. **Invariante de Sufijos Independientes:** Al insertar `v = d^(j)` con timestamp `cur_pos = j`, recorremos las columnas `c = 0 .. dim - 1`:
   - Si `v[c] == 0`, continuamos.
   - Si `cur_pos > pos[c]`, normalizamos `v` para que `v[c] = 1` e intercambiamos `(v, cur_pos)` con `(B[c], pos[c])`. Así la base conserva siempre los vectores **más recientes** linealmente independientes.
   - Luego eliminamos la coordenada `c` del vector `v` (que ahora tiene el timestamp más antiguo) restando un múltiplo de `B[c]`.
2. **Detección de Dependencia Mínima:** Si el vector se reduce al vector nulo `0` con timestamp final `cur_pos > 0`, entonces `cur_pos` es exactamente el máximo `i <= j` tal que `d^(i), ..., d^(j)` son linealmente dependientes, produciendo un bloque balanceado de longitud `j - cur_pos + 1`.
3. **Poda por Expiración Temporal:** Si en cualquier pivote `pos[c] == 0` o `j - pos[c] + 1 >= best_len`, el vector desplazado ya es demasiado antiguo para mejorar `best_len` en el paso actual o en cualquier paso futuro `j' > j`, por lo que sobreescribimos `B[c]` y cortamos la reducción de inmediato.

---

## 4. Estrategia de Implementación Limpia

- **Complejidad Temporal:** `O(sum |E_q| + k * n^2)` con constante ultrabaja (acumulación en `uint64_t` con reducción diferida `MOD2 = 16 * MOD^2` sin divisiones en el bucle interno).
- **Complejidad Espacial:** `O(n^2)` para almacenar la base de `99 x 99`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

const uint64_t MOD = 1000000007ULL;
const uint64_t MOD2 = 16ULL * MOD * MOD;

uint64_t power(uint64_t base, uint64_t exp) {
    uint64_t res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

uint64_t modInverse(uint64_t n) {
    return power(n, MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    int dim = n - 1;
    vector<vector<uint64_t>> B(dim, vector<uint64_t>(dim, 0));
    vector<int> pos(dim, 0);

    int best_len = n + 5;
    vector<int> deg(n + 1, 0);
    vector<int> touched;
    touched.reserve(205);

    for (int j = 1; j <= k; ++j) {
        int m;
        cin >> m;
        touched.clear();
        for (int e = 0; e < m; ++e) {
            int u, v;
            cin >> u >> v;
            deg[u] -= 1;
            deg[v] += 1;
            touched.push_back(u);
            touched.push_back(v);
        }

        if (best_len == 1) {
            for (int x : touched) deg[x] = 0;
            continue;
        }

        vector<uint64_t> vec(dim, 0);
        bool all_zero = true;
        for (int x : touched) {
            int d = deg[x];
            deg[x] = 0;
            if (d != 0) {
                all_zero = false;
                if (x <= dim) {
                    vec[x - 1] = (d < 0) ? (MOD - (uint64_t)(-d) % MOD) % MOD : (uint64_t)d % MOD;
                }
            }
        }

        if (all_zero) {
            best_len = 1;
            continue;
        }

        int cur_pos = j;
        bool independent = false;

        for (int c = 0; c < dim; ++c) {
            if (vec[c] >= MOD) vec[c] %= MOD;
            if (vec[c] == 0) continue;

            if (cur_pos > pos[c]) {
                uint64_t inv = modInverse(vec[c]);
                vec[c] = 1;
                for (int col = c + 1; col < dim; ++col) {
                    if (vec[col] >= MOD) vec[col] %= MOD;
                    vec[col] = (vec[col] * inv) % MOD;
                }

                if (pos[c] == 0 || j - pos[c] + 1 >= best_len) {
                    B[c] = move(vec);
                    pos[c] = cur_pos;
                    independent = true;
                    break;
                }

                swap(vec, B[c]);
                swap(cur_pos, pos[c]);

                vec[c] = 0;
                for (int col = c + 1; col < dim; ++col) {
                    vec[col] += MOD - B[c][col];
                }
            } else {
                uint64_t factor = MOD - vec[c];
                vec[c] = 0;
                const auto& row = B[c];
                for (int col = c + 1; col < dim; ++col) {
                    vec[col] += factor * row[col];
                    if (vec[col] >= MOD2) vec[col] -= MOD2;
                }
            }
        }

        if (!independent) {
            best_len = min(best_len, j - cur_pos + 1);
        }
    }

    cout << (best_len > n ? -1 : best_len) << "\n";
    return 0;
}
```
