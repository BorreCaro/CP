# Problema M: Byte Flu

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Rafael García
- **Dificultad Estimada:** Alta (Div 1B / Div 2D)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [M_Byte_Flu.cpp](../../inputs/solutions/M_Byte_Flu.cpp)

---

## 1. Deconstrucción del Enunciado

Un virus informático conocido como *Byte Flu* amenaza una red corporativa de `N` dispositivos (`2 <= N <= 1000`).
Cada dispositivo `i` posee un identificador alfanumérico único `s_i` (`1 <= |s_i| <= 20`) y un costo de desconexión `c_i` (`1 <= c_i <= 10^6`).
- El virus puede transmitirse directamente entre dos dispositivos si y solo si la **distancia de edición** (*Levenshtein distance*) entre sus identificadores es menor o igual a un umbral `K` (`0 <= K <= 20`), permitiendo inserciones, eliminaciones o sustituciones de caracteres.
- Existen `I` dispositivos infectados inicialmente y `C` dispositivos críticos indispensables que nunca deben infectarse.
- **Restricción estricta:** Ni los dispositivos infectados ni los dispositivos críticos pueden ser desconectados de la red.
- Se busca desconectar un subconjunto de dispositivos normales (no infectados y no críticos) de modo que el virus no pueda alcanzar ningún dispositivo crítico desde ningún dispositivo infectado, minimizando la suma total de los costos de desconexión.

Si es imposible prevenir que el virus alcance a los dispositivos críticos (por ejemplo, si un infectado ya es vecino directo de un crítico), imprimir `-1`. En caso de que no se requiera desconectar ningún dispositivo, imprimir `0`. La entrada finaliza con la línea `0 0 0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`N <= 1000`, `|s_i| <= 20`, `K <= 20`:** El número de pares posibles es `N * (N - 1) / 2 ~ 5 * 10^5`. Comparar cadenas de longitud `<= 20` con DP estándar de Levenshtein `O(|s|^2)` tomaría `~2 * 10^8` operaciones. Sin embargo, como solo nos interesa saber si la distancia es `<= K`, una **DP en Banda** (*Banded Levenshtein DP*) con poda temprana evalúa cada par en tiempo `O(K * |s|)`.
- **Corte de vértices con pesos (*Minimum Vertex Cut*):** Desconectar dispositivos equivale a eliminar vértices del grafo de comunicación pagando su costo `c_i` para separar un conjunto de fuentes `I` de un conjunto de sumideros `C`.
- **Teorema de Flujo Máximo / Corte Mínimo:** Reducción canónica a **Flujo Máximo con Duplicación de Vértices** (*Vertex Splitting*) resuelto mediante el algoritmo de **Dinic**.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Etapa 1: Filtro Rápido de Distancia de Edición en Banda
Para determinar si `dist(a, b) <= K`:
1. Si `abs(|a| - |b|) > K`, es imposible que la distancia sea `<= K` (retornar `false` en `O(1)`).
2. Si `K >= max(|a|, |b|)`, la condición se cumple trivialmente.
3. En la matriz de DP de edición, la diferencia de índices satisface `|i - j| <= K`. Solo calculamos la franja de ancho `2K + 1`.
4. Si el valor mínimo en alguna fila completa excede `K`, abortamos inmediatamente (*early exit*).

### Etapa 2: Construcción de la Red de Flujo (Duplicación de Nodos)
Dado un grafo no dirigido donde cada vértice normal `i` tiene un costo de remoción `c_i`:
1. **Duplicación de Vértices:**
   Cada dispositivo `i` se desdobla en un nodo de entrada `i_in = 2*i` y un nodo de salida `i_out = 2*i + 1`.
   - Si `i` es un dispositivo normal: agregamos una arista dirigida `i_in -> i_out` con capacidad `c_i`. Cortar esta arista equivale a desconectar el dispositivo de la red.
   - Si `i` es infectado o crítico: agregamos `i_in -> i_out` con capacidad `INF = 10^{18}` (no puede desconectarse).
2. **Superfuente `S` y Supersumidero `T`:**
   - Para cada dispositivo infectado `p`: arista `S -> p_in` con capacidad `INF`.
   - Para cada dispositivo crítico `q`: arista `q_out -> T` con capacidad `INF`.
3. **Aristas de Comunicación Bidireccionales:**
   Si dos dispositivos `i` y `j` pueden comunicarse (`dist(s_i, s_j) <= K`):
   - Si uno es infectado y el otro es crítico, **es imposible evitar el contagio**; marcamos bandera de imposibilidad y la respuesta será `-1`.
   - De lo contrario, agregamos aristas dirigidas entre las salidas y entradas correspondientes:
     `i_out -> j_in` con capacidad `INF`
     `j_out -> i_in` con capacidad `INF`

### Etapa 3: Corte Mínimo vía Dinic
Por el Teorema de Menger y el Teorema de Flujo Máximo / Corte Mínimo, el costo mínimo para separar todos los infectados de los críticos es exactamente igual al flujo máximo de `S` a `T` en la red construida.

- **Complejidad Temporal:**
  - Construcción del grafo: `O(N^2 * K * |S|)`.
  - Algoritmo de Dinic sobre red de corte de vértices unitarios: `O(V^2 * E) = O(N * E)` en redes de este tipo, tardando menos de `0.05 s`.
- **Complejidad Espacial:** `O(N + E)` para la estructura de Dinic.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <numeric>
#include <limits>
#include <algorithm>

using namespace std;
using ll = long long;

// Evaluación de distancia de edición <= K mediante DP en banda |i - j| <= K
bool within(const string& a, const string& b, int K) {
    int n = a.size(), m = b.size();
    if (abs(n - m) > K) return false;
    if (K >= max(n, m)) return true;

    const int BIG = 1000;
    vector<int> prev(m + 1), cur(m + 1);
    iota(prev.begin(), prev.end(), 0);

    for (int i = 1; i <= n; i++) {
        fill(cur.begin(), cur.end(), BIG);
        int lo = max(0, i - K), hi = min(m, i + K);
        int rowMin = BIG;

        if (lo == 0) cur[0] = i;
        for (int j = max(1, lo); j <= hi; j++) {
            cur[j] = min({
                prev[j] + 1,
                cur[j - 1] + 1,
                prev[j - 1] + (a[i - 1] != b[j - 1] ? 1 : 0)
            });
        }
        for (int j = lo; j <= hi; j++) {
            rowMin = min(rowMin, cur[j]);
        }
        if (rowMin > K) return false; // Poda temprana: ninguna distancia podrá ser <= K
        swap(prev, cur);
    }
    return prev[m] <= K;
}

// Implementación estándar de Dinic para Flujo Máximo
struct Dinic {
    struct Edge {
        int to;
        ll cap;
    };
    vector<Edge> es;
    vector<vector<int>> g;
    vector<int> level, it;

    explicit Dinic(int n) : g(n), level(n), it(n) {}

    void add(int u, int v, ll c) {
        g[u].push_back(es.size()); es.push_back({v, c});
        g[v].push_back(es.size()); es.push_back({u, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u]) {
                if (es[id].cap > 0 && level[es[id].to] < 0) {
                    level[es[id].to] = level[u] + 1;
                    q.push(es[id].to);
                }
            }
        }
        return level[t] >= 0;
    }

    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = it[u]; i < static_cast<int>(g[u].size()); i++) {
            int id = g[u][i], v = es[id].to;
            if (es[id].cap > 0 && level[v] == level[u] + 1) {
                ll d = dfs(v, t, min(f, es[id].cap));
                if (d > 0) {
                    es[id].cap -= d;
                    es[id ^ 1].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll r = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (ll f = dfs(s, t, numeric_limits<ll>::max())) {
                r += f;
            }
        }
        return r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, I, C;
    while (cin >> N >> K >> I >> C && (N != 0 || K != 0 || I != 0 || C != 0)) {
        vector<string> s(N);
        vector<ll> c(N);
        for (int i = 0; i < N; i++) {
            cin >> s[i] >> c[i];
        }

        // type: 0 normal, 1 infectado inicial, 2 crítico
        vector<int> type(N, 0);
        for (int i = 0; i < I; i++) { int p; cin >> p; type[p - 1] = 1; }
        for (int i = 0; i < C; i++) { int q; cin >> q; type[q - 1] = 2; }

        const ll INF = 1'000'000'000'000'000'000LL;
        int S = 2 * N, T = 2 * N + 1;
        Dinic din(2 * N + 2);

        // Duplicación de nodos: i_in = 2*i, i_out = 2*i + 1
        for (int i = 0; i < N; i++) {
            din.add(2 * i, 2 * i + 1, type[i] == 0 ? c[i] : INF);
        }
        for (int i = 0; i < N; i++) {
            if (type[i] == 1) din.add(S, 2 * i, INF);
            if (type[i] == 2) din.add(2 * i + 1, T, INF);
        }

        bool impossible = false;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                // Si ambos son de la misma categoría fija, no necesitamos conectar arista
                if (type[i] == type[j] && type[i] != 0) continue;
                if (!within(s[i], s[j], K)) continue;

                // Si un dispositivo infectado se conecta directamente con uno crítico
                if (type[i] + type[j] == 3) {
                    impossible = true;
                }

                din.add(2 * i + 1, 2 * j, INF);
                din.add(2 * j + 1, 2 * i, INF);
            }
        }

        cout << (impossible ? -1 : din.maxflow(S, T)) << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Corte de Aristas en vez de Corte de Vértices:**
   Olvidar duplicar los nodos normales (`i_in` e `i_out`) y asignar el costo `c_i` a las aristas de comunicación. El enunciado dice que se desconectan *dispositivos* (vértices), no cables o canales individuales.
2. **Ignorar la Imposibilidad por Adyacencia Directa:**
   Si un nodo infectado y un nodo crítico tienen distancia `<= K`, ninguna desconexión de dispositivos normales puede impedir la propagación, ya que ambos nodos no son desconectables. No verificar esto antes del cálculo de flujo produce una respuesta falsa de costo `INF` o desbordamientos.
3. **Cálculo Completo de Distancia de Edición en `O(|s|^2)`:**
   Con `5 * 10^5` pares y `K <= 20`, calcular la matriz de 400 celdas sin banda de ancho `K` ni corte temprano puede provocar `TLE` en límites de tiempo estrictos.
