# Problema H: Park

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Media - Alta (Div 2D / Centroid Decomposition en Árboles)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución: [H_Park.cpp](../../inputs/solutions/H_Park.cpp)

---

## 1. Deconstrucción del Enunciado

Se entrega un árbol de `N` vértices (`1 <= N <= 10^5`) donde cada vértice `v` tiene un valor de belleza único `b_v in {1, ..., N}`. La popularidad del camino simple entre dos vértices distintos `u` y `v` se define como:
`dist(u, v) * max_{w en camino(u, v)} b_w`,
donde `dist(u, v)` es el número de aristas en el camino. Se pide calcular la suma de las popularidades sobre todos los `N * (N - 1) / 2` pares no ordenados de vértices distintos, módulo `10^9 + 7`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **Producto acoplado de dos funciones de camino (`dist * max_val`):** A diferencia de sumar únicamente distancias (donde basta contar cuántas veces pasa un camino por cada arista) o sumar únicamente el máximo valor (donde basta ordenar vértices y usar DSU), aquí cada camino multiplica su **longitud total** por su **máximo en los vértices**.
- **Descomposición por Centroide (*Centroid Decomposition*):** Para cualquier centroide fijo `c`, todo camino `u <-> v` que pasa por `c` se descompone en dos semirrayos `c -> u` y `c -> v` caracterizados por el par `(m(x), d(x)) = (max_{w en camino(c, x)} b_w, dist(c, x))`. Entonces:
  `popularidad(u, v) = (d(u) + d(v)) * max(m(u), m(v))`.

---

## 3. Técnicas y Conceptos Teóricos

1. **Conteo de Pares Ordenados por `m(x)`:**
   Dada una lista de pares `(m_0, d_0), (m_1, d_1), ..., (m_{s-1}, d_{s-1})` ordenada de forma no decreciente por `m_j`, para cada elemento `j` sabemos que `max(m_i, m_j) = m_j` para todo `0 <= i < j`. Por tanto, la contribución de `j` con todos los `i < j` es:
   `sum_{i = 0}^{j - 1} (d_i + d_j) * m_j = m_j * (j * d_j + sum_{i = 0}^{j - 1} d_i)`.
   Esto se evalúa en tiempo lineal `O(s)` tras ordenar en `O(s log s)`.

2. **Inclusión-Exclusión en el Centroide `c`:**
   - Recolectamos `(m(x), d(x))` para todos los nodos `x` de la componente actual (incluyendo `c` con `(b_c, 0)`) y sumamos `calc_pairs(all_nodes)`.
   - Para eliminar los pares `(u, v)` cuyos dos extremos pertenecen al **mismo** subárbol hijo de `c` (cuyo camino simple no pasa realmente por `c` o dobla sobre la misma arista), restamos `calc_pairs(sub_nodes)` para cada vecino de `c`.

---

## 4. Estrategia de Implementación Limpia

- **Complejidad Temporal:** `O(N log^2 N)` (`log N` niveles en el árbol de centroides; en cada nivel se ordenan particiones disjuntas cuya suma de tamaños es `<= N`).
- **Complejidad Espacial:** `O(N)`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007LL;

int N;
vector<int> b;
vector<vector<int>> adj;
vector<int> sz;
vector<bool> removed;
long long total_ans = 0;

void dfs_size(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }
}

int find_centroid(int u, int p, int comp_size) {
    for (int v : adj[u]) {
        if (v != p && !removed[v] && sz[v] > comp_size / 2) {
            return find_centroid(v, u, comp_size);
        }
    }
    return u;
}

void dfs_collect(int u, int p, int dist, int cur_max, vector<pair<int, int>>& nodes) {
    cur_max = max(cur_max, b[u]);
    nodes.push_back({cur_max, dist});
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            dfs_collect(v, u, dist + 1, cur_max, nodes);
        }
    }
}

long long calc_pairs(vector<pair<int, int>>& nodes) {
    sort(nodes.begin(), nodes.end());
    long long res = 0;
    long long sum_d = 0;
    for (size_t j = 0; j < nodes.size(); ++j) {
        long long m_j = nodes[j].first;
        long long d_j = nodes[j].second;
        long long pair_dist_sum = ((long long)j * d_j + sum_d) % MOD;
        res = (res + m_j * pair_dist_sum) % MOD;
        sum_d = (sum_d + d_j) % MOD;
    }
    return res;
}

void decompose(int entry) {
    dfs_size(entry, 0);
    int c = find_centroid(entry, 0, sz[entry]);
    removed[c] = true;

    vector<pair<int, int>> all_nodes;
    all_nodes.reserve(sz[entry]);
    all_nodes.push_back({b[c], 0});

    for (int v : adj[c]) {
        if (!removed[v]) {
            vector<pair<int, int>> sub_nodes;
            dfs_collect(v, c, 1, b[c], sub_nodes);
            total_ans = (total_ans - calc_pairs(sub_nodes) + MOD) % MOD;
            all_nodes.insert(all_nodes.end(), sub_nodes.begin(), sub_nodes.end());
        }
    }

    total_ans = (total_ans + calc_pairs(all_nodes)) % MOD;

    for (int v : adj[c]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    b.resize(N + 1);
    for (int i = 1; i <= N; ++i) cin >> b[i];

    adj.resize(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    sz.resize(N + 1, 0);
    removed.resize(N + 1, false);

    decompose(1);
    cout << total_ans % MOD << "\n";
    return 0;
}
```
