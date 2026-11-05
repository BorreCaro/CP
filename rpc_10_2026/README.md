# RPC 10 (Octubre 31, 2026) — Reporte Maestro y Editorial de Estudio

Bienvenido al repositorio de análisis técnico, notas de estudio, autopsia de código y catalogación de patrones de la **10ª Actividad de la Red de Programación Competitiva (RPC 10 - Octubre 31, 2026)**.

Este paquete reúne la autopsia técnica de los 6 problemas resueltos en vivo por el equipo (**E, F, G, J, K, L**), las guías pedagógicas profundas de upsolving para los 6 problemas completados post-concurso (**A, B, C, D, H, I**), la deconstrucción matemática de los modelos y la catalogación de antipatrones cognitivos.

---

## 1. Cuadro de Honor y Métricas del Problemset

| ID | Problema | Estado en Concurso | Dificultad | Paradigma / Algoritmo Principal | Complejidad Temporal |
| :---: | :--- | :---: | :---: | :--- | :---: |
| **A** | [Accident](outputs/notes/A_Accident.md) | *Upsolved* | Div 2B | Geometría Analítica (Proyección Ortogonal + Círculo de Thales) | `O(1)` |
| **B** | [Birthday](outputs/notes/B_Birthday.md) | *Upsolved* | Div 2C | Digit DP Inside-Out sobre Núcleos Palindrómicos (`mod p`) | `O(10 * k * p)` |
| **C** | [Cables](outputs/notes/C_Cables.md) | *Upsolved* | Div 1B | Álgebra Lineal Online (Base Gaussiana con Timestamps `mod 10^9 + 7`) | `O(sum &#124;E_q&#124; + k * n^2)` |
| **D** | [Housing](outputs/notes/D_Housing.md) | *Upsolved* | Div 2D | Barrido de Mediana `+1/-1` + Segment Tree + Darboux Discreto | `O(n log n)` |
| **E** | [Memories of Passport Control](outputs/notes/E_Memories_Of_Passport_Control.md) | **AC en Vivo** | Div 3A / Div 2A | Aritmética Modular / Cambio de Monedas Canónico `{1, k}` | `O(1)` |
| **F** | [Milky way](outputs/notes/F_Milky_Way.md) | **AC en Vivo** | Div 2A | Sumas Prefijas de Caídas Adyacentes (`a[i] < a[i-1]`) | `O(n + q)` |
| **G** | [Nightmare](outputs/notes/G_Nightmare.md) | **AC en Vivo** | Div 2B | Conectividad Bicolor con Doble DSU (Ciclos `1` vs `>= 2`) | `O((n + m) alpha(n))` |
| **H** | [Park](outputs/notes/H_Park.md) | *Upsolved* | Div 2D | Centroid Decomposition + Ordenamiento por Belleza Máxima | `O(N log^2 N)` |
| **I** | [Rope](outputs/notes/I_Rope.md) | *Upsolved* | Div 1B | Envolvente Convexa de Perímetro Mínimo + DP Angular por Triángulos | `O(n^4)` |
| **J** | [Shopping](outputs/notes/J_Shopping.md) | **AC en Vivo** | Div 2B | Invariante de Acarreo Binario (*Bitwise Carry over Subset Sums*) | `O(62 * n)` |
| **K** | [Trains](outputs/notes/K_Trains.md) | **AC en Vivo** | Div 3B / Div 2A | Simulación Cinemática 1D de Intervalos Trasladados | `O(n * m)` |
| **L** | [Vampires](outputs/notes/L_Vampires.md) | **AC en Vivo** | Div 3B / Div 2A | Validación Aritmética y Permutación Canónica de Dígitos | `O(t * d log d)` |

- **Resumen Ejecutivo:**
  - **Resueltos en Vivo en Concurso:** 6 / 12 (E, F, G, J, K, L) -> 50.0% de efectividad en vivo.
  - **Upsolved Post-Concurso:** 6 / 12 (A, B, C, D, H, I) -> Cobertura total del 100% (12/12 cubiertos al 100%, 0 pendientes).
  - **Pendiente de Solución en Código:** 0 / 12 (Todos resueltos y verificados).
  - **Lenguajes Empleados:** C++17 (12 soluciones).

---

## 2. Catálogo de Errores y Antipatrones en Vivo

A partir de la autopsia de las soluciones desarrolladas en vivo por el equipo (Problemas E, F, G, J, K, L):

### 2.1. Acceso Fuera de Rango por Asimetría 1-Based y Comparación Fantasma (Problema F - Resuelto en Vivo)
- **Manifestación:** En `Milkyway.cpp` se declaró `vi vt(n + 1);` pero `vll diff(n);` y luego se iteró `for (int i = 1; i <= n; i++)`, escribiendo en `diff[n]` (fuera de rango) y comparando en `i = 1` `vt[1] < vt[0]` contra la posición centinela `0`.
- **Causa Raíz:** Mezclar dimensionamiento 0-based (`n`) y 1-based (`n + 1`) en arreglos paralelos, además de iniciar el barrido de diferencias adyacentes en `i = 1` en lugar de `i = 2`.
- **Lección del Concurso:** El envío pasó porque `diff[1]` sumaba una constante que se cancelaba en `diff[a] != diff[b]` para `1 <= a <= b` y el heap toleró un *out-of-bounds* de 1 posición sin segfault. En producción de CP, si se indexa en `[1..n]`, **todo** vector debe dimensionarse como `n + 1` y las diferencias adyacentes deben iniciar en `i = 2`.

### 2.2. Trampa de Truncamiento en División Entera `x / 2 == y` (Problema L - Resuelto en Vivo)
- **Manifestación:** Verificar que la longitud `x` de `n` sea el doble de la longitud `y` de `a` escribiendo `if (x / 2 == y && y == z)`.
- **Causa Raíz:** La división entera en C++ trunca hacia cero: si `x = 5` y `y = 2`, entonces `5 / 2 == 2` es verdadero aunque `x != 2 * y`.
- **Lección del Concurso:** El código sobrevivió porque más adelante comparó `n != s` tras concatenar `s = a + b` (longitud `4` vs `5`). Siempre debe reemplazarse `x / 2 == y` por `x == 2 * y`.

### 2.3. Cota Ajustada de Bits en Acarreo de Subconjuntos (Problema J - Resuelto en Vivo)
- **Manifestación:** Iterar `for (int i = 0; i < 60; i++)` cuando la suma de los elementos alcanza `10^{18}`.
- **Causa Raíz:** Como `2^{59} = 5.76 * 10^{17}` y `2^{60} = 1.15 * 10^{18}`, `60` bits (`0..59`) bastan por un margen mínimo para `10^{18}`, pero fallarían si la suma alcanzara `1.2 * 10^{18}`.
- **Lección del Concurso:** Extender el bucle hasta `62` bits con `unsigned long long` (`1ULL << bit`) elimina cualquier riesgo de pérdida de acarreo en el bit más significativo.

---

## 3. Síntesis Técnica y Guía Pedagógica de Upsolving (Problemas A, B, C, D, H, I)

### A. Geometría Computacional (Problemas A e I)
- **Lugares Geométricos de Triángulos Rectángulos (Problema A):** Al fijar dos vértices `P, Q` y mover `R -> R'`, el ángulo recto puede estar en `P` (recta perpendicular a `PQ` por `P`, distancia `|dot(R - P, Q - P)| / |Q - P|`), en `Q` (recta perpendicular a `PQ` por `Q`), o en `R'` (circunferencia de Thales con centro `M = (P + Q) / 2` y radio `|P - Q| / 2`, distancia `||R - M| - rad|`). Evaluar las `3 * 3 = 9` combinaciones resuelve el problema en `O(1)`.
- **DP de Polígono Convexo de Perímetro Mínimo por Triangulación en Abanico (Problema I):** La curva cerrada más corta que rodea un conjunto de puntos es su envolvente convexa. Fijando el punto más bajo `p_0`, ordenando los demás por ángulo polar antihorario y precalculando `inside[i][j]` (puntos estrictamente dentro de `Delta(p_0, pts[i], pts[j])`), el estado `dp[i][c]` halla el perímetro mínimo para encerrar `c` puntos en `O(n^4)` con factor constante `1 / 24`.

### B. Programación Dinámica de Dígitos Inside-Out (Problema B)
- **Expansión Central de Palíndromos (`L - 2 -> L`):** En vez de construir palíndromos de afuera hacia adentro para cada longitud fija `L` (lo cual costaría `O(k^2 * p)`), expandimos un núcleo palindrómico de longitud `L - 2` envolviéndolo con el dígito `d` en ambos extremos: `nr = (10 * r + d * (10^{L-1} + 1)) % p`. Esto acumula todos los palíndromos válidos de longitud `1 .. k` en una sola pasada de `O(10 * k * p)`.

### C. Álgebra Lineal Online con Timestamps (Problema C)
- **Flujo Cero Neto = Dependencia Lineal en `R^{n-1}`:** Cada tipo de cable `q` induce un vector de balance neto `d^{(q)}_v = indeg(v) - outdeg(v)`. Un bloque contiguo `[i, j]` admite un flujo balanceado no nulo si y solo si `d^{(i)}, ..., d^{(j)}` son linealmente dependientes. Mantener una base escalonada de dimensión `n - 1` que siempre prioriza el vector con mayor índice temporal `pos[c]` permite hallar para cada `j` el máximo `i <= j` dependiente en `O(k * n^2)`.

### D. Estructuras de Datos y Continuidad Discreta (Problema D)
- **Teorema del Valor Intermedio Discreto en Medianas:** Al codificar `< x` como `-1` y `> x` como `+1`, los balances de sufijos izquierdos y prefijos derechos forman intervalos enteros conexos `[minL, maxL]` y `[minR, maxR]`. Por tanto, `x` es mediana de algún subarreglo de longitud `>= 3` si y solo si `0 in [minL, maxL]`, `0 in [minR, maxR]`, `(maxL > 0 && minR < 0)`, o `(minL < 0 && maxR > 0)`. Un Segment Tree con actualizaciones puntuales responde para toda la permutación en `O(n log n)`.

### E. Descomposición por Centroide en Árboles (Problema H)
- **Acoplamiento `dist(u, v) * max_b(u, v)`:** Al descomponer el árbol por centroides, cada camino que cruza el centroide `c` se parte en dos semirrayos con pares `(m_i, d_i)`. Ordenando los pares por `m` ascendente, el máximo queda fijo en `m_j` para todo `i < j` y la suma `sum_{i < j} (d_i + d_j) * m_j` se evalúa en tiempo lineal, logrando `O(N log^2 N)` total.

---

## 4. Estructura de Archivos del Paquete

```text
rpc_10_2026/
├── README.md                                        # Reporte maestro, matriz completa y catálogo de antipatrones
├── inputs/
│   ├── problemset/
│   │   └── ProblemsetRPC10.pdf                      # Cuadernillo oficial de problemas RPC 10 (2026)
│   └── solutions/                                   # Soluciones aceptadas (AC) en vivo y upsolved (A - L)
│       ├── A_Accident.cpp
│       ├── B_Birthday.cpp
│       ├── C_Cables.cpp
│       ├── D_Housing.cpp
│       ├── E_Memories_Of_Passport_Control.cpp
│       ├── F_Milky_Way.cpp
│       ├── G_Nightmare.cpp
│       ├── H_Park.cpp
│       ├── I_Rope.cpp
│       ├── J_Shopping.cpp
│       ├── K_Trains.cpp
│       └── L_Vampires.cpp
└── outputs/
    └── notes/                                       # Notas individuales y autopsias técnicas (A - L)
        ├── A_Accident.md                            # [Upsolved]
        ├── B_Birthday.md                            # [Upsolved]
        ├── C_Cables.md                              # [Upsolved]
        ├── D_Housing.md                             # [Upsolved]
        ├── E_Memories_Of_Passport_Control.md        # [AC en Vivo]
        ├── F_Milky_Way.md                           # [AC en Vivo]
        ├── G_Nightmare.md                           # [AC en Vivo]
        ├── H_Park.md                                # [Upsolved]
        ├── I_Rope.md                                # [Upsolved]
        ├── J_Shopping.md                            # [AC en Vivo]
        ├── K_Trains.md                              # [AC en Vivo]
        └── L_Vampires.md                            # [AC en Vivo]
```
