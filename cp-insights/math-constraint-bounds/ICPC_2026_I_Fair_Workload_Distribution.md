# ICPC 2026 I - Fair Workload Distribution

**Type:** Math / Constraint Bounds
**Rating / Context:** Div 2D / Div 1B (ICPC Colombia 2026)
**Tag:** offline-coordinate-compression-fenwick-round-robin

## Key Insight

💡 Descomponer la asignación cíclica en rondas completas `floor(M/N)` aplicables a todos y residuos circulares `M mod N` actualizados como intervalos `+1` en un Árbol de Fenwick sobre las `Q` consultas comprimidas fuera de línea.

## Pattern Trigger

"`N <= 10^9` trabajadores, `D <= 10^5` días con asignación round-robin y `Q <= 10^5` consultas de carga acumulada para el trabajador `w` al día `d`."

## Breakthrough

`N = 10^9` es una ilusión: comprimir las coordenadas espaciales únicamente sobre los `Q` trabajadores consultados y ordenar las consultas por día permite barrer el tiempo de 1 a `D` en `O((D + Q) log Q)`.

## Code Spotlight

```cpp
while (day < qd[id]) {
    day++;
    base += M[day] / N;
    ll r = M[day] % N;
    if (r > 0) {
        ll l = k[day], e = k[day] + r - 1;
        if (e <= N) rangeAdd(l, e);
        else { rangeAdd(l, N); rangeAdd(1, e - N); }
    }
}
ans[id] = base + get(lower_bound(xs.begin(), xs.end(), qw[id]) - xs.begin());
```

## Example

Input: `N = 5, D = 3, Q = 4`. Días: `(2, 7), (4, 3), (1, 10)`. Consulta: día 1, trabajador 2.
Output: `2`
Why: En el día 1, tareas `k=2, M=7` van a `[2, 3, 4, 5, 1, 2, 3]`. El trabajador 2 recibe exactamente 2 tareas.

---

**Generated:** 2026-10-10
