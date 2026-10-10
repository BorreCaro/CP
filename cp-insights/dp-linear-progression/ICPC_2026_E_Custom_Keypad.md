# ICPC 2026 E - Custom Keypad

**Type:** DP / Linear Progression
**Rating / Context:** Div 2C / Div 1A (ICPC Colombia 2026)
**Tag:** partition-dp-rightmost-tie-breaking

## Key Insight

💡 Particionar 26 letras en `B` botones consecutivos se resuelve mediante DP de partición de intervalos `dp[j][p] = min(dp[j-1][s] + cost[s][p-1])`, y el desempate estricto a la derecha se garantiza reconstruyendo hacia atrás y tomando el primer índice `s` decreciente que preserve la igualdad óptima.

## Pattern Trigger

"Distribuir las 26 letras en `B <= 26` botones alfabéticos contiguos minimizando pulsaciones `sum (pos * freq)`, priorizando separadores lo más a la derecha posible."

## Breakthrough

En la reconstrucción, iterar el corte `s` en sentido estrictamente descendente desde `p - 1` hacia abajo: el primer `s` que cumpla la relación óptima de costo es necesariamente el separador más a la derecha.

## Code Spotlight

```cpp
for (int j = 1; j <= B; j++)
    for (int p = j; p <= 26; p++)
        for (int s = j - 1; s < p; s++)
            if (dp[j - 1][s] < INF)
                dp[j][p] = min(dp[j][p], dp[j - 1][s] + cost[s][p - 1]);
```

## Example

Input: `B = 3`, text = `"hello world"`
Output: `abcdefghijk|lmnopq|rstuvwxyz`
Why: Costo mínimo de 35 pulsaciones. Empata con `abcdefghijk|lmn|opqrstuvwxyz`, pero se elige el primer corte porque su separador derecho ('q') está más a la derecha que ('n').

---

**Generated:** 2026-10-10
