# Problema J: Courage is Contagious

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** David Yepes
- **Dificultad Estimada:** Media (Div 2B / Div 2C)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [J_Courage_Is_Contagious.cpp](../../inputs/solutions/J_Courage_Is_Contagious.cpp)

---

## 1. Deconstrucción del Enunciado

En las llanuras de Tiě Shā, el general Wei Zhan comanda `N` soldados (`1 <= N <= 10^5`).
Cada soldado `i` posee un umbral de valentía `k_i` (`0 <= k_i <= N`):
- Al comienzo de cada ronda de combate, un soldado combate si y solo si el total de soldados que lucharon en la ronda anterior fue al menos su umbral `k_i`.
- Si `c` soldados combaten en una ronda, en la siguiente ronda combatirán todos aquellos con `k_i <= c`.
- El proceso se repite hasta que el número de combatientes se estabiliza (equilibrio dinámico).

El general recibe `Q` consultas (`1 <= Q <= 10^5`), cada una especificando un número inicial `c_0` (`0 <= c_0 <= N`) de soldados luchando al amanecer. Para cada consulta, se debe responder el número final de soldados combatiendo al alcanzar el equilibrio.
La suma de `N` y la suma de `Q` no exceden `10^6`. La entrada termina con `0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`sum N, sum Q <= 10^6`:** Las consultas deben responderse en tiempo amortizado `O(1)`. Simular la dinámica paso a paso por cada consulta causaría `TLE` si las trayectorias fueran largas.
- **Función de transición monótona no decreciente:**
  Sea `f(c) = count_{1 <= i <= N} (k_i <= c)`.
  Dado que los umbrales `k_i` son fijos, a mayor valor de `c`, mayor o igual es la cantidad de soldados que cumplen `k_i <= c`. Por tanto, `f(c)` es **monótona no decreciente** (`f(c_1) <= f(c_2)` para `c_1 <= c_2`).
- **Teoría de Sistemas Dinámicos Discretos Monótonos / Puntos Fijos:** La trayectoria de cualquier estado inicial converge monótonamente al punto fijo más cercano en la dirección del primer salto.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Dinámica de Puntos Fijos
Un estado `c` es un **punto de equilibrio o punto fijo** si y solo si:
`f(c) == c`

Analicemos la secuencia de iteraciones `c_0, c_1 = f(c_0), c_2 = f(c_1), ...`:
1. **Caso Creciente (`f(c_0) >= c_0`):**
   Por la monotonicidad de `f`:
   `c_0 <= f(c_0) <= f(f(c_0)) <= ... <= N`
   La sucesión es monótona no decreciente y acotada superiormente por `N`. Por el Teorema del Punto Fijo en retículos discretos, la secuencia converge necesariamente al **menor punto fijo mayor o igual a `c_0`**.
2. **Caso Decreciente (`f(c_0) < c_0`):**
   De forma análoga:
   `c_0 > f(c_0) >= f(f(c_0)) >= ... >= 0`
   La sucesión es monótona no creciente y converge necesariamente al **mayor punto fijo menor o igual a `c_0`**.

### Precomputación Lineal en `O(N)`
1. **Cálculo de `f(c)`:**
   Contamos frecuencias de umbrales `cnt[k]` y sumamos prefijos:
   `f[c] = cnt[c] + (c > 0 ? f[c - 1] : 0)`
2. **Propagación de Puntos Fijos Próximos:**
   - Arreglo `up[c]`: menor punto fijo `>= c`. Se calcula barriendo hacia atrás desde `c = n` hasta `0`:
     `up[c] = (f[c] == c) ? c : up[c + 1]` (con `up[n + 1] = n`).
   - Arreglo `down[c]`: mayor punto fijo `<= c`. Se calcula barriendo hacia adelante desde `c = 0` hasta `n`:
     `down[c] = (f[c] == c) ? c : (c > 0 ? down[c - 1] : 0)`.
3. **Respuesta en Tiempo Constante `O(1)` por Consulta:**
   Para un `c_0` dado:
   `respuesta = (f[c_0] >= c_0) ? up[c_0] : down[c_0]`

- **Complejidad Temporal:** `O(N + Q)` por caso de prueba.
- **Complejidad Espacial:** `O(N)`.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    while (cin >> n >> q && (n != 0 || q != 0)) {
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            cnt[k]++;
        }

        // f(c) = cantidad de soldados con umbral de valentía k_i <= c
        vector<int> f(n + 1);
        for (int c = 0; c <= n; c++) {
            f[c] = cnt[c] + (c > 0 ? f[c - 1] : 0);
        }

        // up[c]: menor punto fijo f(x) == x tal que x >= c
        // down[c]: mayor punto fijo f(x) == x tal que x <= c
        vector<int> up(n + 2), down(n + 1);
        up[n + 1] = n;
        for (int c = n; c >= 0; c--) {
            up[c] = (f[c] == c) ? c : up[c + 1];
        }
        for (int c = 0; c <= n; c++) {
            down[c] = (f[c] == c) ? c : (c > 0 ? down[c - 1] : 0);
        }

        // Consultas en O(1)
        while (q--) {
            int c0;
            cin >> c0;
            cout << (f[c0] >= c0 ? up[c0] : down[c0]) << '\n';
        }
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Simulación Iterativa Consulta por Consulta:**
   Ejecutar `while (c != f[c]) c = f[c];` para cada una de las `Q = 10^5` consultas. Si bien `f(c)` es monótona, trayectorias escalonadas que avanzan de 1 en 1 pueden dar `N` pasos, llevando la complejidad a `O(Q * N) = 10^{10}` y provocando *Time Limit Exceeded*.
2. **Confusión en la Dirección de Convergencia:**
   Consultar siempre `up[c_0]` sin verificar el signo de `f(c_0) - c_0`. Si `f(c_0) < c_0`, el sistema colapsa hacia abajo hacia `down[c_0]`. Asumir que la valentía siempre "contagia hacia arriba" ignora el caso en que soldados desmotivados desertan en masa.
3. **Indexación y Casos Borde con `c = 0`:**
   Los umbrales `k_i` pueden ser `0` (soldados temerarios que siempre luchan sin importar la compañía), y `c_0` puede ser `0`. Los arreglos deben dimensionarse holgadamente hasta `n + 1`.
