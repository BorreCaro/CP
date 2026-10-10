# ICPC 2026 B - Bankey

**Type:** Greedy / Boundary Testing
**Rating / Context:** Div 3A / Div 2A (ICPC Colombia 2026)
**Tag:** parity-prefix-sums-sliding-window

## Key Insight

💡 Desacoplar la cadena en dos subsecuencias por paridad de índice (`..., i - 4, i - 2, i`) permite calcular la suma de cualquier ventana de `M` términos en `O(1)` restando prefijos separados por paso 2.

## Pattern Trigger

"Suma máxima de `M` dígitos en posiciones consecutivas de la misma paridad en una cadena de `N <= 10^5` dígitos."

## Breakthrough

Calcular `pre[i] = d[i] + pre[i-2]` desacopla las posiciones pares e impares, reduciendo una ventana fija de paso 2 a una simple resta `pre[i] - pre[i - 2*M]` con guardia para índices `< 1`.

## Code Spotlight

```cpp
for (int i = 1; i <= n; i++) {
    pre[i] = (s[i - 1] - '0') + (i >= 2 ? pre[i - 2] : 0);
    int j = i - 2 * m;
    long long sum = pre[i] - (j >= 1 ? pre[j] : 0);
    best = max(best, sum);
}
```

## Example

Input: `N = 7, M = 3`, `s = "7210396"`
Output: `17`
Why: En la ventana de posiciones impares terminando en `i = 5` ('3'), los dígitos son `7 + 1 + 3 = 11`. Terminando en `i = 6` ('9'), posiciones pares `2 + 0 + 9 = 11`. Para `M = 4`, posiciones `7 + 1 + 3 + 6 = 17`.

---

**Generated:** 2026-10-10
