# Problema H: HCubes Costs

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Rodrigo Cardoso
- **Dificultad Estimada:** Muy Fácil (Div 3A)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [H_HCubes_Costs.cpp](../../inputs/solutions/H_HCubes_Costs.cpp)

---

## 1. Deconstrucción del Enunciado

Un hipercubo de dimensión `n` (`H_n`, con `0 < n <= 20`) se define recursivamente: sus vértices son todas las cadenas binarias de longitud `n` (`0 <= a, b < 2^n`).
Existe una arista entre dos vértices si y solo si difieren en exactamente un bit.
Los costos de las aristas se definen recursivamente:
- En `H_1`: `c_1(0, 1) = 1`.
- En `H_{n+1}`:
  - `c_{n+1}(xu, xv) = c_n(u, v)` para `x in {0, 1}`, `u, v in V_n`.
  - `c_{n+1}(xu, yu) = n + 1` para `x != y`, `u in V_n`.

Dados `n` y dos vértices `a` y `b` expresados en base decimal, se debe hallar el **costo mínimo de un camino de comunicación** entre `a` y `b` en `H_n`.
La entrada finaliza con la línea `0 0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`n <= 20`:** El grafo del hipercubo tiene `2^n <= 10^6` vértices. Aplicar Dijkstra o BFS con `10^6` nodos y `20 * 10^6` aristas por cada caso de prueba sería sumamente ineficiente y propenso a `TLE`.
- **Definición inductiva del costo de las aristas:** Notar que la arista que conecta `xu` con `yu` (cambiando el bit de orden `n + 1`) tiene costo idéntico `n + 1` para cualquier sufijo común `u`.
- **Independencia de coordenadas:** Cada bit se modifica de forma independiente en una arista a lo largo de esa dimensión.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Interpretación del Costo por Bit
Observemos la regla inductiva del costo:
- Cambiar el bit en la posición `0` (el menos significativo) cuesta `1`.
- Cambiar el bit en la posición `1` cuesta `2`.
- En general, cambiar el bit en la posición `i` (para `0 <= i < n`, indexado desde 0) cuesta exactamente `i + 1`.

### Invariante del Camino de Costo Mínimo
Para ir del vértice `a` al vértice `b`, debemos transformar la cadena binaria de `a` en la de `b`:
- Si el bit `i` difiere entre `a` y `b`, dicho bit debe invertirse un número impar de veces (al menos 1 vez).
- Si el bit `i` coincide entre `a` y `b`, dicho bit debe invertirse un número par de veces (al menos 0 veces).

Dado que todos los costos de arista son estrictamente positivos (`i + 1 >= 1 > 0`), invertir un bit más de una vez solo agregaría un costo adicional de al menos `2 * (i + 1) > 0`, sin aportar ningún beneficio.

Por tanto, **en el camino óptimo cada bit que difiere entre `a` y `b` se invierte exactamente una vez, y ningún otro bit se modifica**:
`costo_minimo = sum_{i=0}^{n-1} (( (a ^ b) >> i ) & 1) * (i + 1)`

- **Complejidad Temporal:** `O(n)` por caso de prueba.
- **Complejidad Espacial:** `O(1)`.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long a, b;
    while (cin >> n >> a >> b && (n != 0 || a != 0 || b != 0)) {
        // x contiene un 1 en cada posición de bit donde a y b difieren
        long long x = a ^ b;
        long long cost = 0;

        for (int i = 0; i < n; i++) {
            if ((x >> i) & 1) {
                cost += i + 1; // Invertir el bit en la posición i cuesta i + 1
            }
        }

        cout << cost << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Modelar el Hipercubo como Grafo Explícito con Dijkstra:**
   Construir listas de adyacencia para `2^{20} ~ 10^6` nodos y ejecutar Dijkstra. El consumo de memoria superaría los límites y provocaría *Time Limit Exceeded*.
2. **Confusión en la Indexación de Bits (1-indexado vs 0-indexado):**
   Confundir la posición del bit menos significativo (índice 0, costo 1) con índice 1, provocando desfases en el costo total.
3. **Desbordamiento en Operaciones de Desplazamiento de Bits (*Bit Shift Overflow*):**
   Aunque `n <= 20` cabe cómodamente en enteros estándar, para hipercubos de mayor dimensión siempre debe usarse `1LL << i` para evitar comportamientos indefinidos con `1 << 31`.
