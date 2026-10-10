# Problema B: Bankey

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Rodrigo Cardoso
- **Dificultad Estimada:** Fácil (Div 3A / Div 2A)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [B_Bankey.cpp](../../inputs/solutions/B_Bankey.cpp)

---

## 1. Deconstrucción del Enunciado

Pedro busca ocultar su contraseña bancaria dentro de una secuencia de `N` dígitos decimales (`0 < N < 10^5`, indexados de 1 a `N`).
Dado un entero `M` (`1 <= M <= N`), la clave bancaria es la **suma máxima posible de `M` dígitos en posiciones consecutivas de la misma paridad** (es decir, posiciones separadas por paso de 2: `..., i - 4, i - 2, i`).
Las posiciones antes del primer dígito (`< 1`) o después del último (`> N`) se consideran rellenas con ceros (`0`).
Se deben procesar múltiples casos de prueba hasta encontrar la línea `0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`N <= 10^5`:** Sumas en ventanas de longitud hasta `10^5`. Calcular cada ventana sumando elemento por elemento tomaría `O(N * M) = O(N^2)` en el peor caso (`10^{10}` operaciones), resultando en `TLE`.
- **Acceso por misma paridad (`i, i-2, i-4, ...`):** La secuencia se desacopla naturalmente en dos subsecuencias independientes entrelazadas: los índices impares (`1, 3, 5, ...`) y los índices pares (`2, 4, 6, ...`).
- **Suma de ventana fija:** Clásico disparador de **Sumas de Prefijos con Salto 2** (*Parity Prefix Sums*) o **Ventana Deslizante** en tiempo `O(N)`.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Definición del Prefijo por Paridad
Definimos el arreglo de sumas de prefijos acumuladas por paridad `pre[i]` para `1 <= i <= N`:
`pre[i] = d[i] + (i >= 2 ? pre[i - 2] : 0)`

Esto significa:
- Para `i` impar: `pre[i] = d[i] + d[i-2] + ... + d[1]`
- Para `i` par: `pre[i] = d[i] + d[i-2] + ... + d[2]`

### Cálculo en Tiempo Constante `O(1)` por Posición
Consideremos cualquier ventana de `M` elementos de la misma paridad que termina en la posición `i`.
Dicha ventana abarca los elementos en las posiciones:
`i, i - 2, i - 4, ..., i - 2*(M - 1)`

La posición anterior al inicio de esta ventana dentro de la misma paridad es:
`j = i - 2 * M`

- Si `j >= 1`, el valor acumulado hasta `j` en esa paridad es `pre[j]`.
- Si `j < 1`, la ventana se extiende hacia el relleno virtual de ceros a la izquierda, por lo que no hay elementos válidos que restar (el valor que se resta es `0`).

Por consiguiente, la suma de la ventana que termina en `i` es exactamente:
`sum(i) = pre[i] - (j >= 1 ? pre[j] : 0)`

### Invariante de Maximización
Recorriendo `i` de `1` a `N`, mantenemos `best = max(best, sum(i))`.
El relleno con ceros a la derecha equivale simplemente a que ventanas que terminan en posiciones más allá de `N` no pueden aportar valores mayores que las ventanas truncadas en el límite, por lo que basta evaluar todos los puntos finales `1 <= i <= N`.

- **Complejidad Temporal:** `O(N)` por caso de prueba.
- **Complejidad Espacial:** `O(N)` para almacenar los dígitos y el arreglo de prefijos.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        string s;
        cin >> s;

        // pre[i] acumula d[i] + d[i-2] + d[i-4] + ...
        vector<long long> pre(n + 1, 0);
        long long best = 0;

        for (int i = 1; i <= n; i++) {
            pre[i] = (s[i - 1] - '0') + (i >= 2 ? pre[i - 2] : 0);

            // La ventana de M términos de igual paridad inicia en i - 2*(m - 1).
            // El elemento previo a restar en la misma paridad es j = i - 2*m.
            int j = i - 2 * m;
            long long sum = pre[i] - (j >= 1 ? pre[j] : 0);

            best = max(best, sum);
        }

        cout << best << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Simulación Manual de Ventana con Bucle Interno (`O(N * M)`):**
   Re-sumar los `M` dígitos en cada posición `i` mediante un ciclo anidado. Con `N = 10^5` y `M = 10^5`, el tiempo de ejecución excede por varios órdenes de magnitud el límite de 1 segundo.
2. **Error de Salto de Paridad (*Parity Bleed*):**
   Sumar prefijos lineales continuos `pre[i] = pre[i-1] + d[i]` en lugar de saltar de 2 en 2 (`pre[i-2]`), mezclando posiciones pares e impares dentro de la misma ventana.
3. **Manejo Incorrecto de Índices Negativos (*Out-of-Bounds*):**
   Intentar acceder a `pre[i - 2 * m]` directamente sin validar `j >= 1`, lo que provoca violaciones de segmento de memoria (*SIGSEGV*).
