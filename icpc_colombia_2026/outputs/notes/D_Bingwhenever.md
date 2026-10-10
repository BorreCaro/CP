# Problema D: Bingwhenever

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Rafael García
- **Dificultad Estimada:** Fácil-Media (Div 3B / Div 2A)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [D_Bingwhenever.cpp](../../inputs/solutions/D_Bingwhenever.cpp)

---

## 1. Deconstrucción del Enunciado

Un grupo de `N` amigos (`1 <= N <= 10^3`) juega al *Bingwhenever*, una variante asíncrona de bingo por correo electrónico.
- Cada jugador recibe un cartón con `K` números enteros distintos (`1 <= K <= 10^3`) en el rango de 1 a `M = 10^9`.
- Se genera una secuencia de `B` bolas numeradas distintas (`K <= B <= 10^5`), también en el rango de 1 a `M`. Se garantiza que todo número presente en algún cartón aparece en la secuencia de bolas.
- Un jugador completa su cartón en el paso `s` en el cual se extrae la última bola requerida por su cartón.
- Gana el jugador (o los jugadores, en caso de empate) que complete su cartón en el menor paso `s` posible.

Se deben determinar e imprimir los nombres de todos los ganadores en orden lexicográfico ascendente, separados por espacios. La entrada finaliza con la línea `0 0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`M = 10^9`:** Los números en los cartones alcanzan `10^9`, por lo que **no** se pueden indexar directamente en un arreglo directo `int step[M]`. Se requiere una tabla hash (`std::unordered_map`) o compresión de coordenadas.
- **`B <= 10^5` y `N * K <= 10^6`:** Simular paso a paso la extracción de cada bola y actualizar a todos los jugadores tomaría `O(B * N) = 10^8` operaciones pesadas.
- **Consultas Estáticas de Pasos de Extracción:** El paso en que se extrae cada bola es fijo. Almacenar el mapa inverso `número -> paso` permite consultar en `O(1)` el momento de marcado de cualquier número del cartón.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Invariante del Paso de Finalización
Para el jugador `i`, su cartón contiene el conjunto de números `card[i] = {x_{i,1}, x_{i,2}, ..., x_{i,K}}`.
Sea `when[x]` el índice (`1 <= step <= B`) en el cual el número `x` fue extraído en la tómbola.
El jugador completa su cartón exactamente cuando se ha extraído el último de sus números:
`finish[i] = max_{x in card[i]} when[x]`

El juego es ganado en el paso global mínimo:
`best = min_{1 <= i <= N} finish[i]`

Los ganadores corresponden a todos los jugadores cuyo `finish[i] == best`.

### Estructura de Datos y Complejidad
1. **Lectura y Mapeo:** Insertar cada bola `x` en un `unordered_map<int, int> when` reservando memoria previa (`when.reserve(2 * B)`) para evitar rehashings. Complejidad: `O(B)` promedio.
2. **Evaluación de Jugadores:** Para cada uno de los `N` jugadores, iterar sobre sus `K` números y tomar el máximo. Complejidad: `O(N * K)`.
3. **Filtrado y Ordenamiento:** Filtrar los nombres con `finish[i] == best` y ordenar con `std::sort`. Complejidad: `O(N log N)`.
- **Complejidad Temporal Global:** `O(B + N * K + N log N)`.
- **Complejidad Espacial:** `O(B + N * K)`.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, b;
    while (cin >> n >> k >> b && (n != 0 || k != 0 || b != 0)) {
        vector<string> name(n);
        vector<vector<int>> card(n, vector<int>(k));

        for (int i = 0; i < n; i++) {
            cin >> name[i];
            for (int& x : card[i]) {
                cin >> x;
            }
        }

        // Mapeo: número de bola -> paso en el que es extraída (1-indexado)
        unordered_map<int, int> when;
        when.reserve(2 * b);
        for (int s = 1; s <= b; s++) {
            int x;
            cin >> x;
            when[x] = s;
        }

        // finish[i]: paso en el que el jugador i completa todos sus K números
        vector<int> finish(n, 0);
        int best = numeric_limits<int>::max();

        for (int i = 0; i < n; i++) {
            for (int x : card[i]) {
                finish[i] = max(finish[i], when[x]);
            }
            best = min(best, finish[i]);
        }

        // Recolectar a todos los empatados en el primer lugar
        vector<string> winners;
        for (int i = 0; i < n; i++) {
            if (finish[i] == best) {
                winners.push_back(name[i]);
            }
        }

        sort(winners.begin(), winners.end());

        // Impresión en formato requerido: separados por espacios con salto final
        for (size_t i = 0; i < winners.size(); i++) {
            cout << winners[i] << (i + 1 == winners.size() ? '\n' : ' ');
        }
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Simulación Inversa en Línea (*Event-Driven Step Simulation*):**
   Iterar paso a paso sobre las `B` bolas y en cada paso descontar contadores a los jugadores hasta encontrar el primer ganador. Si bien es intuitiva, esta simulación en línea requiere listas invertidas (`número -> lista de jugadores`) con mayor overhead de punteros y memoria. La formulación estática `finish[i] = max(when[x])` es puramente funcional, limpia y `O(1)` por celda.
2. **Degradación Cuadrática de `unordered_map` por Colisiones:**
   Sin `when.reserve()`, un `unordered_map` puede experimentar múltiples realocaciones y colisiones si no se reserva el factor de carga adecuado.
3. **Formato de Salida y Espacios Finales:**
   Olvidar imprimir los ganadores en orden alfabético estricto o dejar un espacio en blanco sobrante al final de la línea.
