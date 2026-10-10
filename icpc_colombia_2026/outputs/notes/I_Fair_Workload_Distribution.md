# Problema I: Fair Workload Distribution

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Edwin Niño
- **Dificultad Estimada:** Media-Alta (Div 2D / Div 1B)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [I_Fair_Workload_Distribution.cpp](../../inputs/solutions/I_Fair_Workload_Distribution.cpp)

---

## 1. Deconstrucción del Enunciado

El departamento de logística de ByteCorp cuenta con `N` repartidores numerados del 1 al `N` (`1 <= N <= 10^9`).
A lo largo de `D` días consecutivos (`1 <= D <= 100000`), se reciben solicitudes de entrega:
- En el día `i`, hay un total de `M_i` tareas (`0 <= M_i <= 10^9`) que se asignan equitativamente mediante una ronda cíclica (*round-robin*) comenzando en el trabajador `k_i` (`1 <= k_i <= N`).
- La primera tarea se asigna al trabajador `k_i`, y cada tarea subsiguiente pasa al siguiente trabajador `(x mod N) + 1` de forma secuencial.

La gerencia realiza `Q` consultas de rendimiento (`1 <= Q <= 100000`):
- Cada consulta `(d, w)` pregunta: *"¿Cuántas tareas en total completó el repartidor `w` entre el día 1 y el día `d` inclusive?"*

La suma de `D` y `Q` sobre todos los casos de prueba no excede `500000`. La entrada termina con la línea `0 0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`N <= 10^9`:** El número de trabajadores es masivo; es imposible instanciar arreglos de tamaño `N` en memoria. Sin embargo, solo se realizan `Q <= 100000` consultas puntuales de trabajadores específicos `w`.
- **`D, Q <= 100000`:** Sugiere un algoritmo en tiempo `O((D + Q) log Q)` o `O((D + Q) log N)`.
- **Estructura de Ronda Cíclica:**
  En el día `i`, con `M_i` tareas:
  1. Cada uno de los `N` trabajadores recibe exactamente `floor(M_i / N)` tareas completas (rondas completas).
  2. El remanente `r = M_i mod N` tareas se reparte asignando 1 tarea adicional a los trabajadores en el intervalo continuo `[k_i, k_i + r - 1]` (que puede dividirse en dos intervalos si se desborda `N`: `[k_i, N]` y `[1, (k_i + r - 1) - N]`).
- **Consultas acumuladas por umbral temporal `d`:** Las consultas piden el estado en el día `d`. Procesar las consultas **fuera de línea (*offline*) ordenadas por día** permite mantener el estado acumulativo mediante una única pasada de barrido.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Descomposición de la Carga Diaria
Para cada día `i`:
- **Componente Base Global:**
  `base_dia = floor(M_i / N)`
  Este valor incrementa la carga de **todos** los `N` trabajadores por igual. Por tanto, podemos mantener una variable escalar acumulada `base`:
  `base = sum_{i=1}^d floor(M_i / N)`
- **Componente Residual por Intervalos:**
  El residuo `r = M_i mod N` reparte `+1` a un rango circular de longitud `r` comenzando en `k_i`:
  - Si `k_i + r - 1 <= N`, sumamos `+1` al intervalo `[k_i, k_i + r - 1]`.
  - Si `k_i + r - 1 > N`, sumamos `+1` a `[k_i, N]` y `+1` a `[1, k_i + r - 1 - N]`.

### Procesamiento Fuera de Línea con Árbol de Fenwick (BIT)
Dado que solo nos interesan los trabajadores consultados `w in {qw_1, qw_2, ..., qw_Q}`:
1. **Compresión de Coordenadas:**
   Extraemos todos los valores únicos de `w` presentes en las `Q` consultas y los ordenamos en un vector `xs` de tamaño `S <= Q`.
2. **Fenwick Tree de Diferencias:**
   Un Árbol de Fenwick sobre los `S` puntos comprimidos permite realizar:
   - Actualización de rango `[l, r]` con `+1`: localizando mediante búsqueda binaria (`lower_bound` y `upper_bound`) los extremos en `xs`, aplicamos `add(li, 1)` y `add(ri, -1)`.
   - Consulta puntual en `w`: `get(pos)` en tiempo `O(log S)`.
3. **Barrido Temporal (*Swepline Offline*):**
   - Ordenamos las consultas por el día `qd`.
   - Avanzamos un puntero `day` desde 1 hasta `D`. Para cada día, sumamos `floor(M_i / N)` a `base` y agregamos los intervalos residuales al Fenwick Tree.
   - Cuando el día alcanza `qd`, la respuesta para esa consulta es simplemente `base + get(pos)`.

- **Complejidad Temporal:** `O((D + Q) log Q)` por caso de prueba.
- **Complejidad Espacial:** `O(D + Q)` para almacenar las asignaciones, consultas y el BIT comprimido.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    int D, Q;
    while (cin >> N >> D >> Q && (N != 0 || D != 0 || Q != 0)) {
        vector<ll> k(D + 1), M(D + 1);
        for (int i = 1; i <= D; i++) {
            cin >> k[i] >> M[i];
        }

        vector<int> qd(Q);
        vector<ll> qw(Q);
        for (int i = 0; i < Q; i++) {
            cin >> qd[i] >> qw[i];
        }

        // 1) Compresión de coordenadas sobre los trabajadores consultados
        vector<ll> xs = qw;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int S = xs.size();

        // 2) Árbol de Fenwick (BIT): suma en rango, consulta en punto
        vector<ll> bit(S + 2, 0);
        auto add = [&](int i, ll v) {
            for (i++; i <= S + 1; i += i & -i) bit[i] += v;
        };
        auto get = [&](int i) {
            ll r = 0;
            for (i++; i > 0; i -= i & -i) r += bit[i];
            return r;
        };
        auto rangeAdd = [&](ll l, ll r) {
            int li = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
            int ri = upper_bound(xs.begin(), xs.end(), r) - xs.begin();
            if (li < ri) {
                add(li, 1);
                add(ri, -1);
            }
        };

        // 3) Ordenamiento offline de consultas por día
        vector<int> order(Q);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return qd[a] < qd[b];
        });

        vector<ll> ans(Q);
        ll base = 0; // Acumulador de rondas completas
        int day = 0;

        for (int id : order) {
            while (day < qd[id]) {
                day++;
                base += M[day] / N;
                ll r = M[day] % N;
                if (r > 0) {
                    ll l = k[day], e = k[day] + r - 1;
                    if (e <= N) {
                        rangeAdd(l, e);
                    } else {
                        rangeAdd(l, N);
                        rangeAdd(1, e - N); // Envoltura circular
                    }
                }
            }
            int pos = lower_bound(xs.begin(), xs.end(), qw[id]) - xs.begin();
            ans[id] = base + get(pos);
        }

        // 4) Impresión de respuestas en orden original de consulta
        for (ll x : ans) {
            cout << x << '\n';
        }
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Intento de Segment Tree Dinámico o Arreglo Directo de Tamaño `N`:**
   Dado que `N <= 10^9`, instanciar cualquier estructura de datos proporcional a `N` genera instantáneamente *Memory Limit Exceeded*. La compresión sobre las consultas `qw` es estrictamente obligatoria.
2. **Consultas En Línea (*Online Queries*) sin Persistencia:**
   Intentar responder cada consulta recalculando el historial desde el día 1 costaría `O(Q * D) = 10^{10}` operaciones. Ordenar las consultas por día (*offline sweep*) amortiza las inserciones a una única pasada sobre los `D` días.
3. **Desbordamiento de 64 bits (*Integer Overflow*):**
   Las tareas acumuladas por un trabajador pueden superar `D * M_i = 10^5 * 10^9 = 10^{14}`. Todos los acumuladores, respuestas y arreglos de tareas deben ser `long long`.
