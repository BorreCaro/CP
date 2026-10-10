# ICPC 2026 J - Courage is Contagious

**Type:** Math / Formula Development
**Rating / Context:** Div 2B / Div 2C (ICPC Colombia 2026)
**Tag:** monotone-dynamical-system-fixed-points

## Key Insight

💡 La función de soldados combatientes `f(c) = count(k_i <= c)` es monótona no decreciente, por lo que toda dinámica iterativa converge monótonamente al punto fijo más cercano: el menor punto fijo `>= c_0` si `f(c_0) >= c_0`, o el mayor `<= c_0` en caso contrario.

## Pattern Trigger

"`N <= 10^5` soldados con umbrales `k_i`, rondas repetidas donde luchan los de umbral `<= c_{actual}` hasta estabilizarse, con `Q <= 10^5` consultas."

## Breakthrough

Precalcular los puntos fijos `f(c) == c` y propagar los arreglos `up[c]` y `down[c]` en `O(N)` responde cualquier consulta en `O(1)` inmediato sin simular iteraciones.

## Code Spotlight

```cpp
for (int c = n; c >= 0; c--) up[c] = (f[c] == c) ? c : up[c + 1];
for (int c = 0; c <= n; c++) down[c] = (f[c] == c) ? c : (c > 0 ? down[c - 1] : 0);
while (q--) {
    int c0; cin >> c0;
    cout << (f[c0] >= c0 ? up[c0] : down[c0]) << '\n';
}
```

## Example

Input: `N = 4`, umbrales `[1, 2, 2, 3]`, consultas `c_0 = 2`, `c_0 = 0`
Output: `4`, `0`
Why: Para `c_0 = 2`: `f(2) = 3`, `f(3) = 4`, punto fijo en 4. Para `c_0 = 0`: `f(0) = 0`, punto fijo inmediato en 0.

---

**Generated:** 2026-10-10
