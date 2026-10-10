# ICPC 2026 C - Into the Onion

**Type:** DP / Linear Progression
**Rating / Context:** Div 2D / Div 1B (ICPC Colombia 2026)
**Tag:** monotone-chain-hull-peeling-layer-dp

## Key Insight

💡 Pelar cascos convexos sucesivos (*Onion Peeling*) segmenta `N` puntos en capas ordenadas `L_1, ..., L_K`, permitiendo propagar valores óptimos con DP unidireccional y comparaciones de distancias al cuadrado `4 * dist^2 <= 9 * d^2` sin errores de punto flotante.

## Pattern Trigger

"`N <= 3000` puntos en capas concéntricas formadas por cascos convexos sucesivos, con transiciones permitidas solo hacia la siguiente capa si la distancia es `<= 1.5 * d_{min}`."

## Breakthrough

Elevar al cuadrado la condición `dist <= 1.5 * d` a `4 * dist^2 <= 9 * d^2` elimina por completo el uso de números flotantes y raíces cuadradas, operando con exactitud entera pura de 64 bits.

## Code Spotlight

```cpp
for (int v : B) {
    ll bp = -1;
    for (int u : A) {
        if (best[u] < 0) continue;
        ll dx = pt[u].x - pt[v].x, dy = pt[u].y - pt[v].y;
        if (4 * (dx * dx + dy * dy) <= 9 * d2) bp = max(bp, best[u]);
    }
    best[v] = (bp < 0) ? -1 : bp + w[v];
}
```

## Example

Input: 7 celdas formando cuadrado exterior y triángulo interior
Output: `9`
Why: La distancia mínima entre capas es `d = 1.0` (entre `c3` y `c7`), radio máximo `1.5`. El camino óptimo transiciona de `c3` (`w=1`) a `c7` (`w=8`), sumando `1 + 8 = 9`.

---

**Generated:** 2026-10-10
