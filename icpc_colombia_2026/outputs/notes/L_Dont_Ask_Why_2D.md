# Problema L: Don't Ask Why 2D

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** David Yepes
- **Dificultad Estimada:** Alta (Div 1B / Div 2D)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [L_Dont_Ask_Why_2D.cpp](../../inputs/solutions/L_Dont_Ask_Why_2D.cpp)

---

## 1. Deconstrucción del Enunciado

En el año 2089, el simulador molecular *SynthCore-9* del Centro Intergaláctico de Creación de Proteínas (ICPC) ha quedado bloqueado en el modo bidimensional plano (*2D Planar Mode*).
Una cadena de proteína consta de `N` aminoácidos (`1 <= N <= 15`), donde cada monómero es hidrofóbico (`H`) o polar (`P`), con un presupuesto exacto de `B` aminoácidos hidrofóbicos (`0 <= B <= N`).
- La cadena se pliega en una retícula 2D infinita como un **camino autoevitante** (*Self-Avoiding Walk - SAW*): partiendo del origen `(0, 0)`, cada monómero se sitúa a 1 celda de distancia ortogonal del anterior mediante pasos `R` (derecha), `L` (izquierda), `U` (arriba) o `D` (abajo), sin autointersecciones.
- La estabilidad de la proteína se cuantifica mediante el número de **contactos hidrofóbicos**: pares de aminoácidos `H` que son vecinos ortogonales en la retícula pero que **no son consecutivos en la cadena** (`|i - j| > 1`).

Dada una orden `(N, B)`, se debe determinar:
1. El número máximo de contactos hidrofóbicos alcanzables.
2. Una secuencia de aminoácidos de longitud `N` con exactamente `B` letras `H`.
3. Una secuencia de plegado de `N - 1` direcciones en `{R, L, U, D}` que produzca dicho número de contactos (omitida si `N = 1`).

Se procesan a lo sumo `T <= 60` órdenes. La entrada finaliza con la línea `0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`N <= 15`:** Un valor de `N` tan pequeño es la firma universal de **Búsqueda Exhaustiva con Poda / Backtracking + Programación Dinámica con Máscaras de Bits (Bitmask DP)**.
- **Caminos Autoevitantes (SAW) de longitud 14:** El número total de caminos autoevitantes de longitud 14 en una retícula 2D no dirigida es moderado. Además, las rotaciones y reflexiones (8 simetrías ortogonales del plano) permiten podar drásticamente el espacio de exploración.
- **Grado Máximo del Grafo de Contactos:** En una retícula 2D regular, cada celda tiene exactamente 4 vecinos. Dado que 2 de ellos corresponden a los enlaces covalentes consecutivos de la cadena (`i - 1` e `i + 1`), **cada aminoácido puede tener a lo sumo 2 contactos topológicos** en el grafo de contactos. Por ende, el grafo de contactos inducido es una unión disjunta de caminos simples y ciclos.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Fase 1: Generación de Caminos Autoevitantes con Ruptura de Simetrías
Exploramos los plegados válidos recursivamente mediante `dfs(n, turned)`:
- **Simetría 1:** El primer paso siempre se fija como `'R'` (`dx = 1, dy = 0`).
- **Simetría 2:** El primer giro que abandone el eje horizontal debe ser hacia arriba (`'U'`).
Cualquier celda visitada se marca en un mapa de coordenadas `who[{x, y}] = id`.

Para cada celda añadida en posición `n`:
Revisamos sus 4 vecinos ortogonales. Si encontramos un índice `j <= n - 2`, agregamos la arista bidireccional `(n, j)` al grafo de adyacencia `adj`.
Almacenamos los grafos de contacto únicos encontrados en `seen[n][adj] = path`. Debido a que muchos plegados distintos producen exactamente la misma estructura de contactos, memorizar únicamente el primer plegado por grafo colapsa el espacio a unos pocos miles de estados.

### Fase 2: Optimización de Subconjuntos mediante Bitmask DP
Para cada grafo de contacto `g` asociado a un largo `n`:
1. Identificamos los vértices con grado `> 0`: `vs = {v : g[v] != 0}`. Su tamaño `m = |vs|` satisface `m <= 10`.
2. Mapeamos estos `m` vértices a índices de bit `0..m-1`.
3. Para cada máscara `S in [0, 2^m - 1]`:
   - Calculamos el número de aristas internas `e[S]` de forma incremental:
     `e[S] = e[S \ {low(S)}] + aristas(low(S), S \ {low(S)})`
   - Actualizamos el mejor valor para cada tamaño de máscara:
     `bk[popcount(S)] = max(bk[popcount(S)], e[S])`
4. Para cada presupuesto de aminoácidos `B in [0, n]`:
   - El máximo de contactos con a lo sumo `B` hidrófobos es:
     `c = max_{k <= min(B, m)} bk[k]`
   - Si `c > bestC[n][B]`, actualizamos la mejor marca, reconstruimos la secuencia con `'H'` en los bits activos de la máscara óptima y rellenamos el remanente de `'H'` necesarios hasta completar `B` en posiciones inactivas (ya que agregar más `'H'` en nodos sin contacto nunca reduce el total).

### Fase 3: Respuestas en Tiempo `O(1)`
Con la matriz `bestC[N][B]`, `bestSeq[N][B]` y `bestFold[N][B]` precomputada al inicio del programa, cada consulta de prueba se responde de inmediato en tiempo `O(1)`.

- **Complejidad Temporal:** Precomputación en `< 0.20 s`; consultas en `O(1)`.
- **Complejidad Espacial:** `O(MAXN^2)` para almacenar las soluciones óptimas.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <map>
#include <bitset>
#include <algorithm>

using namespace std;

const int MAXN = 15;
using Graph = array<uint16_t, MAXN>; // adj[i]: contactos no consecutivos del nodo i

int bestC[MAXN + 1][MAXN + 1];
string bestSeq[MAXN + 1][MAXN + 1], bestFold[MAXN + 1][MAXN + 1];
array<map<Graph, string>, MAXN + 1> seen;

Graph adj{};
array<int, MAXN> px{}, py{};
map<pair<int, int>, int> who;
string path;

const array<int, 4> DX = {1, -1, 0, 0}, DY = {0, 0, 1, -1};
const string DC = "RLUD";

// Backtracking generador de caminos autoevitantes (SAW) con poda por simetrías
void dfs(int n, bool turned) {
    seen[n].emplace(adj, path);
    if (n == MAXN) return;

    for (int d = 0; d < 4; d++) {
        if (n == 1 && d != 0) continue;            // Simetría: primer paso siempre 'R'
        if (!turned && d != 0 && d != 2) continue; // Simetría: primer desvío siempre 'U'

        int nx = px[n - 1] + DX[d], ny = py[n - 1] + DY[d];
        if (who.count({nx, ny})) continue;         // Evitar auto-intersección

        px[n] = nx; py[n] = ny;
        path.push_back(DC[d]);

        vector<int> added;
        for (int e = 0; e < 4; e++) {
            auto it = who.find({nx + DX[e], ny + DY[e]});
            if (it != who.end() && it->second <= n - 2) {
                int j = it->second;
                adj[n] |= 1 << j;
                adj[j] |= 1 << n;
                added.push_back(j);
            }
        }

        who[{nx, ny}] = n;
        dfs(n + 1, turned || d == 2);
        who.erase({nx, ny});

        for (int j : added) {
            adj[n] &= ~(1 << j);
            adj[j] &= ~(1 << n);
        }
        path.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (auto& row : bestC) fill(begin(row), end(row), -1);
    who[{0, 0}] = 0;
    dfs(1, false);

    // Evaluación offline de subconjuntos de contactos mediante Bitmasks
    for (int n = 1; n <= MAXN; n++) {
        for (const auto& [g, fold] : seen[n]) {
            vector<int> vs;
            for (int i = 0; i < n; i++) if (g[i]) vs.push_back(i);
            int m = vs.size(), full = 1 << m;

            vector<int> pos(n, -1);
            for (int t = 0; t < m; t++) pos[vs[t]] = t;

            vector<int> ca(m, 0);
            for (int t = 0; t < m; t++) {
                for (int i = 0; i < n; i++) {
                    if ((g[vs[t]] >> i) & 1) ca[t] |= 1 << pos[i];
                }
            }

            vector<int> e(full, 0), low(full, 0), pc(full, 0), bk(m + 1, -1), bm(m + 1, 0);
            for (int S = 1; S < full; S++) {
                low[S] = (S & 1) ? 0 : low[S >> 1] + 1;
                pc[S] = pc[S >> 1] + (S & 1);
                int R = S & (S - 1);
                e[S] = e[R] + static_cast<int>(bitset<16>(ca[low[S]] & R).count());
            }

            for (int S = 0; S < full; S++) {
                if (e[S] > bk[pc[S]]) {
                    bk[pc[S]] = e[S];
                    bm[pc[S]] = S;
                }
            }

            for (int B = 0; B <= n; B++) {
                int c = -1, S = 0;
                for (int k = 0; k <= min(B, m); k++) {
                    if (bk[k] > c) { c = bk[k]; S = bm[k]; }
                }
                if (c > bestC[n][B]) {
                    string seq(n, 'P');
                    int used = 0;
                    for (int t = 0; t < m; t++) {
                        if ((S >> t) & 1) { seq[vs[t]] = 'H'; used++; }
                    }
                    for (int i = 0; i < n && used < B; i++) {
                        if (seq[i] == 'P') { seq[i] = 'H'; used++; }
                    }
                    bestC[n][B] = c;
                    bestSeq[n][B] = seq;
                    bestFold[n][B] = fold;
                }
            }
        }
    }

    int N, B;
    while (cin >> N >> B && (N != 0 || B != 0)) {
        cout << bestC[N][B] << ' ' << bestSeq[N][B];
        if (N > 1) cout << ' ' << bestFold[N][B];
        cout << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Exploración Exhaustiva Sin Reducción de Simetrías:**
   Generar todas las rotaciones y reflexiones multiplica el árbol de búsqueda por un factor de 8, lo que puede causar *Time Limit Exceeded* al inicializar las estructuras. Fijar el primer paso a `'R'` y el primer desvío a `'U'` elimina la redundancia isomórfica.
2. **Caso Borde `N = 1`:**
   Para una molécula de un solo aminoácido (`N = 1`), no existen movimientos de plegado. El enunciado especifica expresamente: *"If N = 1, print only the contact count and the sequence (there is no folding)"*. Omitir esta condición e imprimir un espacio sobrante causa presentación errónea (*Wrong Answer*).
3. **Restricción de No Consecutividad (`|i - j| > 1`):**
   Contar los enlaces covalentes directos entre aminoácidos adyacentes en la cadena (`i` con `i - 1`). La definición biológica de contacto hidrofóbico solo aplica a monómeros distantes en la secuencia que quedan juntos espacialmente tras el plegado.
