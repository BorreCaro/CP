# ICPC 2026 L - Don't Ask Why 2D

**Type:** Brute Force / Exhaustive Search
**Rating / Context:** Div 1B / Div 2D (ICPC Colombia 2026)
**Tag:** self-avoiding-walk-symmetry-pruning-sos-bitmask

## Key Insight

💡 En una retícula 2D, generar caminos autoevitantes de longitud `N <= 15` rompiendo simetrías ortogonales produce grafos de contacto con grado a lo sumo 2, donde el subconjunto óptimo de `B` aminoácidos hidrofóbicos se resuelve en precomputación mediante Bitmask DP.

## Pattern Trigger

"Plegar una cadena de `N <= 15` aminoácidos con `B <= N` hidrofóbicos en retícula 2D maximizando contactos no consecutivos, con a lo sumo `T <= 60` casos."

## Breakthrough

Fijar el primer paso como 'R' y el primer desvío como 'U' colapsa las 8 simetrías del plano; cada nodo en la retícula tiene a lo sumo 2 contactos no consecutivos, permitiendo precomputar todas las respuestas en `< 0.2` segundos.

## Code Spotlight

```cpp
for (int S = 1; S < full; S++) {
    low[S] = (S & 1) ? 0 : low[S >> 1] + 1;
    pc[S] = pc[S >> 1] + (S & 1);
    int R = S & (S - 1);
    e[S] = e[R] + static_cast<int>(bitset<16>(ca[low[S]] & R).count());
}
for (int S = 0; S < full; S++)
    if (e[S] > bk[pc[S]]) { bk[pc[S]] = e[S]; bm[pc[S]] = S; }
```

## Example

Input: `N = 4, B = 2`
Output: `1 HPPH RUL`
Why: La cadena HPPH doblada con direcciones RUL forma un bucle donde los dos H en los extremos quedan adyacentes a distancia 1 en la retícula, generando 1 contacto hidrofóbico.

---

**Generated:** 2026-10-10
