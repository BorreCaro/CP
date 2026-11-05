# Problema G: Nightmare

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Media (Div 2B / Teoría de Grafos + DSU)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución del Equipo: [G_Nightmare.cpp](../../inputs/solutions/G_Nightmare.cpp)

---

## 1. Insight Clave

💡 En un grafo simple con aristas bicoloreadas (rojo `c = 0` y azul `c = 1`), existe un ciclo simple con **exactamente una** arista de un color y todas las demás del color opuesto si y solo si existe alguna arista `(u, v)` de color `c` cuyos extremos `u` y `v` están conectados por un camino compuesto exclusivamente por aristas del color `1 - c`.

---

## 2. Análisis de la Solución en Vivo

La solución desarrollada en vivo (`Nightmare.cpp`) modeló la condición de forma óptima:
1. Instanció dos estructuras *Disjoint Set Union* independientes de tamaño `n`: `d1` para las aristas azules (`c == 1`) y `d2` para las aristas rojas (`c == 0`).
2. Unió los extremos de cada arista en su DSU correspondiente según su color.
3. Verificó para cada arista `e = (a, b, c)`:
   - Si `c == 1` y `d2.is_same_set(a, b)` es verdadero -> retorna `false` (`NO`).
   - Si `c == 0` y `d1.is_same_set(a, b)` es verdadero -> retorna `false` (`NO`).
4. Si ninguna arista cierra un camino monocromático del color opuesto, retorna `true` (`YES`).

**Demostración de Equivalencia:** Si `u` y `v` pertenecen a la misma componente conexa en el subgrafo rojo `d2`, entonces existe un **camino simple** puramente rojo entre `u` y `v`. Al concatenar dicho camino simple con la arista azul `(u, v)`, se forma un ciclo simple con exactamente una arista azul y el resto rojas. Recíprocamente, cualquier ciclo simple con una sola arista azul `(u, v)` provee un camino simple rojo entre `u` y `v`.

---

## 3. Patrón de Recurrencia / Sesgo Cognitivo

- **Trampa de Enumeración de Ciclos (*Cycle Enumeration Trap*):** Intentar buscar ciclos con DFS/backtracking fracasa porque un grafo puede tener exponencialmente muchos ciclos simples, y un árbol DFS arbitrario no garantiza encontrar el ciclo mixto. Invertir el problema preguntando *"¿qué arista sería la única de su color en el ciclo?"* colapsa una propiedad global de ciclos a una consulta de conectividad por componentes en `O((n + m) alpha(n))`.

---

## 4. Lógica Correcta & Código Limpio

- **Complejidad Temporal:** `O((n + m) alpha(n))`.
- **Complejidad Espacial:** `O(n + m)`.

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};

struct Edge {
    int u, v, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    DSU d0(n), d1(n);
    vector<Edge> edges(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].c;
        if (edges[i].c == 0) d0.unite(edges[i].u, edges[i].v);
        else d1.unite(edges[i].u, edges[i].v);
    }

    for (const auto& e : edges) {
        if (e.c == 0 && d1.same(e.u, e.v)) {
            cout << "NO\n";
            return 0;
        }
        if (e.c == 1 && d0.same(e.u, e.v)) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    return 0;
}
```
