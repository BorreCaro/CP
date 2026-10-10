# ICPC 2026 F - Heist

**Type:** Binary Search / Answer on Range
**Rating / Context:** Div 1C / Div 2E (ICPC Colombia 2026)
**Tag:** sutherland-hodgman-inscribed-circle-bsta

## Key Insight

💡 Partir el cuarto rectangular con cada recta láser mediante recorte de polígonos de Sutherland-Hodgman y hallar el círculo inscrito máximo en cada celda convexa mediante búsqueda binaria de radio con contracción de semiplanos.

## Pattern Trigger

"Encontrar el punto dentro de una habitación `W x L` más alejado de `Z <= 100` segmentos láser y paredes, desempatando por mayor área y cercanía a `(0, 0)`."

## Breakthrough

El punto más seguro de un polígono convexo es su centro de Chebyshev: contraer las aristas hacia adentro una distancia `r` define una función monótona factible para búsqueda binaria de 60 pasos.

## Code Spotlight

```cpp
auto shrink = [&](D r) {
    Poly q = c;
    for (size_t i = 0; i < c.size() && !q.empty(); i++) {
        Pt a = c[i], ab = c[(i + 1) % c.size()] - a;
        D len = sqrt(dot(ab, ab));
        q = clip(q, [&](Pt p) { return cross(ab, p - a) / len - r; });
    }
    return q;
};
```

## Example

Input: Cuarto `2 x 2`, 4 láseres formando un diamante central
Output: `1.00 1.00 0.71`
Why: El centro del diamante `(1.00, 1.00)` tiene distancia `sqrt(2) / 2 ~ 0.71` a las 4 aristas que lo rodean.

---

**Generated:** 2026-10-10
