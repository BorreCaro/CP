# Problema A: Balanced System Reactor

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Rafael García
- **Dificultad Estimada:** Media (Div 2C / Div 1A)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [A_Balanced_System_Reactor.cpp](../../inputs/solutions/A_Balanced_System_Reactor.cpp)

---

## 1. Deconstrucción del Enunciado

Un reactor industrial contiene una cadena de `n` módulos con factores de potencia enteros positivos `x_1, x_2, ..., x_n >= 1`.
El sistema se considera perfectamente balanceado si y solo si la salida lineal total es igual a la amplificación compuesta:
`x_1 + x_2 + ... + x_n = x_1 * x_2 * ... * x_n`

Por restricciones de estabilidad física para `n > 3`, exactamente `n - 3` módulos deben tener factor de potencia igual a 1.
Los 3 módulos restantes tendrán factores de potencia mayores o iguales a 2:
`2 <= a <= b <= c`

Se debe determinar si existe una configuración válida para un valor de `n` dado (`4 <= n <= 10^7`). En caso afirmativo, imprimir los tres factores `a, b, c` en orden no decreciente. En caso contrario, imprimir `IMPOSSIBLE`.
La entrada finaliza con una línea que contiene `0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`n <= 10^7` con múltiples casos de prueba:** Una búsqueda exhaustiva de ternas `(a, b, c)` en `O(n^3)` o pares `(a, b)` en `O(n^2)` resulta completamente inviable (`TLE`).
- **Exactamente `n - 3` unos:** La presencia de `n - 3` unos transforma la ecuación multivariable en una ecuación diofántica fija con exactamente tres incógnitas `a, b, c >= 2`.
- **Crecimiento cúbico de `a * b * c` vs crecimiento lineal:** La cota inferior `a * a * a <= m + 3a` fuerza a que `a` no pueda superar la raíz cúbica de `m = n - 3`. Para `m = 10^7`, `a <= (10^7)^(1/3) ~ 215`. Esto es una señal inequívoca de **Búsqueda Acotada por Despeje Diofántico**.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Reducción Algebraica
Sustituyendo los `n - 3` unos en la ecuación de balance:
`sum x_i = (n - 3) * 1 + a + b + c = (n - 3) + a + b + c`
`prod x_i = 1^(n - 3) * a * b * c = a * b * c`

Igualando suma y producto:
`(n - 3) + a + b + c = a * b * c`

Definiendo la constante `m = n - 3`:
`m + a + b + c = a * b * c`
`a * b * c - c = m + a + b`
`c * (a * b - 1) = m + a + b`

Como `a >= 2` y `b >= 2`, tenemos `a * b >= 4`, por lo que `a * b - 1 >= 3 > 0`. Podemos despejar `c` de forma unívoca:
`c = (m + a + b) / (a * b - 1)`

### Condiciones de Validez
Para que una terna `(a, b, c)` sea una solución válida:
1. `c` debe ser un número entero: `(m + a + b) % (a * b - 1) == 0`.
2. Se debe respetar el orden `b <= c`:
   `(m + a + b) / (a * b - 1) >= b`
   Multiplicando por `(a * b - 1) > 0`:
   `m + a + b >= b * (a * b - 1)`

### Acotamiento del Espacio de Búsqueda
- **Cota para `a`:** En el caso simétrico `a = b = c`, tenemos `a^3 - 3*a <= m`. En cuanto `a^3 - 3*a > m`, no existe ninguna terna ordenada con `a <= b <= c`. Por tanto, `a <= (m)^(1/3) + 1 <= 216`.
- **Cota para `b`:** Para un `a` fijo, iteramos `b >= a`. La condición `m + a + b >= b * (a * b - 1)` puede reescribirse como:
  `b^2 * a - 2*b - a <= m`
  En cuanto `b * (a * b - 1) > m + a + b`, la cota `c >= b` deja de ser posible, y podemos interrumpir el bucle de `b` mediante un `break` inmediato.
- **Complejidad total por caso de prueba:**
  `sum_{a=2}^{m^(1/3)} sqrt(m / a) = O(m^(2/3))`.
  Para `m = 10^7`, la suma de pasos del bucle interior no supera las `3 * 10^4` iteraciones, ejecutándose en fracciones de milisegundo.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>

using namespace std;

int main() {
    // Optimización de E/S estándar para CP
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    while (cin >> n && n != 0) {
        long long m = n - 3;
        bool found = false;

        // a <= m^(1/3), ya que a * a * a - 3 * a <= m
        for (long long a = 2; !found && a * a * a - 3 * a <= m; a++) {
            for (long long b = a; ; b++) {
                // Condición de parada: si c < b, ningún b mayor podrá cumplir c >= b
                if (m + a + b < b * (a * b - 1)) break;

                long long num = m + a + b;
                long long den = a * b - 1;

                // Verificamos divisibilidad entera exacta y condición c >= b
                if (num % den == 0 && num / den >= b) {
                    cout << a << ' ' << b << ' ' << num / den << '\n';
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Búsqueda Trivalente No Acotada (`O(N^3)` o `O(N^2)`):**
   Intentar iterar sobre `a, b, c` o buscar factores mediante fuerza bruta sobre `c`. Despejar la variable dependiente `c = (m + a + b) / (a * b - 1)` reduce la dimensionalidad del espacio de búsqueda de 3 a 1.5 dimensiones.
2. **Desbordamiento de 32 bits (*Integer Overflow*):**
   Aunque `n <= 10^7` cabe en un entero con signo de 32 bits, el producto `b * (a * b - 1)` o las expresiones intermedias `a * a * a` pueden desbordar `2^31 - 1` si `b` llegara a ser grande. Utilizar estrictamente `long long` previene comportamientos indefinidos.
3. **Omisión de la Condición `c >= b`:**
   Aceptar cualquier entero positivo `c` que satisfaga la divisibilidad sin exigir `c >= b` generaría ternas desordenadas o duplicadas con `c < b`, violando la monotonicidad supuesta en la búsqueda.
