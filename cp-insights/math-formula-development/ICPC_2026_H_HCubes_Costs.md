# ICPC 2026 H - HCubes Costs

**Type:** Math / Formula Development
**Rating / Context:** Div 3A (ICPC Colombia 2026)
**Tag:** hypercube-metric-xor-bit-cost

## Key Insight

💡 En el hipercubo inductivo donde cambiar el bit `i` (0-indexado) tiene costo estricto `i + 1`, el camino más corto entre `a` y `b` invierte exactamente una vez cada bit activo en `a ^ b`, acumulando `cost = sum_{i} (( (a ^ b) >> i ) & 1) * (i + 1)`.

## Pattern Trigger

"Costo recursivo de aristas en hipercubo de dimensión `n <= 20`, calcular camino mínimo entre vértices enteros `a` y `b`."

## Breakthrough

Ignorar completamente la estructura de grafo: como cada bit requerido debe invertirse al menos una vez y todo costo es positivo (`i + 1 > 0`), cualquier inversión extra es un desperdicio estricto.

## Code Spotlight

```cpp
long long x = a ^ b, cost = 0;
for (int i = 0; i < n; i++) {
    if ((x >> i) & 1) {
        cost += i + 1;
    }
}
cout << cost << '\n';
```

## Example

Input: `n = 3, a = 6, b = 2`
Output: `3`
Why: `6 = 110_2`, `2 = 010_2`. `a ^ b = 100_2` (difieren únicamente en el bit 2). Costo: `2 + 1 = 3`.

---

**Generated:** 2026-10-10
