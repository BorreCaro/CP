# XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026) — Reporte Maestro y Editorial de Estudio

Bienvenido al paquete oficial de análisis técnico, notas pedagógicas de estudio, código de referencia y catalogación de patrones de la **XL Maratón Nacional de Programación Colombia (ICPC / ACIS / REDIS / CCPL 2026)**.

Este documento consolida la deconstrucción matemática y algorítmica de los 13 problemas del problemset oficial (letras **A** a la **M**), presentando las soluciones de referencia autorizadas por el comité científico, el catálogo integral de patrones y el análisis preventivo de antipatrones cognitivos.

---

## 1. Cuadro de Honor y Matriz General del Problemset

| Letra | Problema | Autor | Categoría / Paradigma Principal | Restricción Clave | Complejidad Temporal | Guía de Estudio |
| :---: | :--- | :--- | :--- | :--- | :---: | :---: |
| **A** | [Balanced System Reactor](outputs/notes/A_Balanced_System_Reactor.md) | Rafael García | Teoría de Números / Despeje Diofántico | `n <= 10^7`, `n - 3` unos | `O(m^(2/3))` | [Nota A](outputs/notes/A_Balanced_System_Reactor.md) |
| **B** | [Bankey](outputs/notes/B_Bankey.md) | Rodrigo Cardoso | Prefijos por Paridad / Ventana Deslizante | `N <= 10^5`, `M <= N` | `O(N)` | [Nota B](outputs/notes/B_Bankey.md) |
| **C** | [Into the Onion](outputs/notes/C_Into_The_Onion.md) | Rafael García | Pelado de Cascos Convexos + DP de Capas | `N <= 3000`, `dist <= 1.5 d` | `O(N^2)` | [Nota C](outputs/notes/C_Into_The_Onion.md) |
| **D** | [Bingwhenever](outputs/notes/D_Bingwhenever.md) | Rafael García | Simulación Asíncrona / Hash Map Temporal | `B <= 10^5`, `N * K <= 10^6` | `O(B + N*K + N log N)` | [Nota D](outputs/notes/D_Bingwhenever.md) |
| **E** | [Custom Keypad](outputs/notes/E_Custom_Keypad.md) | Edwin Niño | DP de Partición + Desempate a la Derecha | `B <= 26`, `\|text\| <= 10^5` | `O(\|text\| + B * 26^2)` | [Nota E](outputs/notes/E_Custom_Keypad.md) |
| **F** | [Heist](outputs/notes/F_Heist.md) | Julián Badillo | Sutherland-Hodgman + Búsqueda Binaria de Radio | `W, L <= 1000`, `Z <= 100` | `O(Z * celdas * 60)` | [Nota F](outputs/notes/F_Heist.md) |
| **G** | [Math United FC](outputs/notes/G_Math_United_FC.md) | Juan Corena | Voraz con Arrepentimiento (*Buy-and-Regret Heap*) | `P <= 200000`, `B <= 10^9` | `O(P log P)` | [Nota G](outputs/notes/G_Math_United_FC.md) |
| **H** | [HCubes Costs](outputs/notes/H_HCubes_Costs.md) | Rodrigo Cardoso | Métrica en Hipercubo / Suma Ponderada de Bits XOR | `n <= 20`, `a, b < 2^n` | `O(n)` | [Nota H](outputs/notes/H_HCubes_Costs.md) |
| **I** | [Fair Workload Distribution](outputs/notes/I_Fair_Workload_Distribution.md) | Edwin Niño | Compresión de Coordenadas + Fenwick Tree Offline | `N <= 10^9`, `D, Q <= 100000` | `O((D + Q) log Q)` | [Nota I](outputs/notes/I_Fair_Workload_Distribution.md) |
| **J** | [Courage is Contagious](outputs/notes/J_Courage_Is_Contagious.md) | David Yepes | Sistemas Dinámicos Monótonos / Puntos Fijos | `N, Q <= 10^5`, sumas `<= 10^6` | `O(N + Q)` | [Nota J](outputs/notes/J_Courage_Is_Contagious.md) |
| **K** | [Sample Median Preservation](outputs/notes/K_Sample_Median_Preservation.md) | Edwin Niño | Combinatoria Disjunta por Complemento mod `10^9 + 7` | `N, K <= 10^6` impares | `O(N log N + K)` | [Nota K](outputs/notes/K_Sample_Median_Preservation.md) |
| **L** | [Don't Ask Why 2D](outputs/notes/L_Dont_Ask_Why_2D.md) | David Yepes | Caminos Autoevitantes (SAW) + Bitmask SOS DP | `N <= 15`, `B <= N` | `O(SAW_15)` offline | [Nota L](outputs/notes/L_Dont_Ask_Why_2D.md) |
| **M** | [Byte Flu](outputs/notes/M_Byte_Flu.md) | Rafael García | Levenshtein en Banda + Corte Mínimo de Dinic | `N <= 1000`, `\|s\| <= 20`, `K <= 20` | `O(N^2 * K * \|S\| + Flujo)` | [Nota M](outputs/notes/M_Byte_Flu.md) |

- **Resumen Estadístico del Problemset:**
  - **Problemas Totales:** 13 (A, B, C, D, E, F, G, H, I, J, K, L, M).
  - **Cobertura Editorial:** 13 / 13 (100% documentados con notas pedagógicas y código C++17).
  - **Distribución de Paradigmas:** Geometría Computacional (C, F), Matemáticas / Combinatoria / Bits (A, H, K), Programación Dinámica (E, L), Grafos / Flujo (M, J), Estructuras de Datos / Voraz (B, D, G, I).

---

## 2. Catálogo Preventivo de Antipatrones Cognitivos

A partir del análisis profundo de los enunciados oficiales, trampas de implementación y casos frontera:

### 2.1. Desbordamiento Silencioso de Enteros de 32 bits (*Silent Integer Overflow*)
- **Problema A (Balanced System Reactor):** Las expresiones intermedias `b * (a * b - 1)` y `a * a * a` pueden superar `2 * 10^9` a pesar de que `n <= 10^7`.
- **Problema G (Math United FC):** El presupuesto acumulado y los costos de los jugadores pueden alcanzar `2 * 10^{14}`. Declarar `B` como `int` corrompe las decisiones de compra.
- **Problema I (Fair Workload Distribution):** El total de tareas recibidas por un trabajador alcanza `D * M_i = 10^5 * 10^9 = 10^{14}`. Todos los acumuladores, respuestas y arreglos del Fenwick Tree deben ser `long long`.

### 2.2. Pérdida de Precisión por Operaciones de Punto Flotante
- **Problema C (Into the Onion):** Evaluar `dist(u, v) <= 1.5 * d` mediante llamadas directas a `hypot()` o `sqrt()` introduce discrepancias de redondeo en pares cuya distancia coincide exactamente con el umbral. Multiplicar cruzado en aritmética entera de 64 bits `4 * dist^2 <= 9 * d^2` asegura exactitud analítica absoluta.
- **Problema F (Heist):** En Sutherland-Hodgman, recortes sucesivos en esquinas agudas crean vértices redundantes separados por distancias infinitesimales `< EPS`. No colapsar vértices casi idénticos induce divisiones por cero en el cálculo de vectores unitarios normales.

### 2.3. Asignación Monolítica de Memoria Desproporcionada (*Scale Hallucination*)
- **Problema I (Fair Workload Distribution):** Intentar instanciar estructuras de datos indexadas directamente por el ID del trabajador (`N <= 10^9`) provoca colapso inmediato de memoria (*MLE*). Comprimir exclusivamente sobre las `Q` consultas reduce la dimensión a `10^5`.
- **Problema H (HCubes Costs):** Intentar instanciar el hipercubo como un grafo explícito y aplicar Dijkstra con `2^{20} ~ 10^6` nodos y `20 * 10^6` aristas cuando el resultado analítico directo es simplemente la suma ponderada de bits XOR en `O(n)`.

### 2.4. Inversión o Violación de Criterios de Desempate
- **Problema E (Custom Keypad):** La regla del problema exige colocar los separadores lo más a la derecha posible (*rightmost separators*). Reconstruir la DP iterando cortes en orden ascendente (hacia la izquierda) genera una partición matemáticamente óptima en costo pero rechazada por el juez (*Wrong Answer*).
- **Problema F (Heist):** No evaluar los criterios secundarios (mayor área del polígono) y terciarios (cercanía al origen `(0, 0)`) conduce a respuestas divergentes en celdas simétricas.

### 2.5. La Trampa de la Mutua Inclusión en Combinatoria
- **Problema K (Sample Median Preservation):** Intentar aplicar el Principio de Inclusión-Exclusión suponiendo que una muestra puede tener simultáneamente al menos `h + 1` elementos menores que la mediana y al menos `h + 1` elementos mayores. La cota `2*(h + 1) = K + 1 > K` prueba que ambos eventos son mutuamente excluyentes, permitiendo sumar sus conteos directamente por complemento.

---

## 3. Estructura del Paquete Local

```text
icpc_colombia_2026/
├── README.md                              # Reporte maestro y dashboard general
├── inputs/
│   ├── problemset/
│   │   └── Problemset_ICPC_Colombia_2026.pdf  # PDF oficial de enunciados (29 páginas)
│   └── solutions/                         # Soluciones C++17 limpias estandarizadas [Letra]_[Titulo].cpp
│       ├── A_Balanced_System_Reactor.cpp
│       ├── B_Bankey.cpp
│       ├── C_Into_The_Onion.cpp
│       ├── D_Bingwhenever.cpp
│       ├── E_Custom_Keypad.cpp
│       ├── F_Heist.cpp
│       ├── G_Math_United_FC.cpp
│       ├── H_HCubes_Costs.cpp
│       ├── I_Fair_Workload_Distribution.cpp
│       ├── J_Courage_Is_Contagious.cpp
│       ├── K_Sample_Median_Preservation.cpp
│       ├── L_Dont_Ask_Why_2D.cpp
│       └── M_Byte_Flu.cpp
└── outputs/
    └── notes/                             # Guías pedagógicas individuales de estudio
        ├── A_Balanced_System_Reactor.md
        ├── B_Bankey.md
        ├── C_Into_The_Onion.md
        ├── D_Bingwhenever.md
        ├── E_Custom_Keypad.md
        ├── F_Heist.md
        ├── G_Math_United_FC.md
        ├── H_HCubes_Costs.md
        ├── I_Fair_Workload_Distribution.md
        ├── J_Courage_Is_Contagious.md
        ├── K_Sample_Median_Preservation.md
        ├── L_Dont_Ask_Why_2D.md
        └── M_Byte_Flu.md
```
