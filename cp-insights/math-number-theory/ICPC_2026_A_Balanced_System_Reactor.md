# ICPC 2026 A - Balanced System Reactor

**Type:** Math / Number Theory
**Rating / Context:** Div 2C / Div 1A (ICPC Colombia 2026)
**Tag:** bounded-search-diophantine-despeje

## Key Insight

💡 En una ecuación con `n - 3` unos donde `a*b*c - (a+b+c) = m`, fijar `a <= m^(1/3)` y `b >= a` despeja unívocamente la variable restante `c = (m + a + b) / (a * b - 1)`, reduciendo el espacio de búsqueda a complejidad `O(m^(2/3))`.

## Pattern Trigger

"Encontrar `a <= b <= c` tales que el producto de `n` números iguale a su suma sabiendo que `n - 3` son unos, con `n <= 10^7`."

## Breakthrough

En lugar de factorizar o buscar las tres incógnitas, despejar `c` como función entera de `(a, b)` convierte una búsqueda tridimensional en una iteración acotada con interrupción inmediata en cuanto `c < b`.

## Code Spotlight

```cpp
for (long long a = 2; !found && a * a * a - 3 * a <= m; a++) {
    for (long long b = a; ; b++) {
        if (m + a + b < b * (a * b - 1)) break;
        long long num = m + a + b, den = a * b - 1;
        if (num % den == 0 && num / den >= b) {
            cout << a << ' ' << b << ' ' << num / den << '\n';
            found = true; break;
        }
    }
}
```

## Example

Input: `n = 8`
Output: `2 2 3`
Why: `m = 5`. Para `a = 2, b = 2`, `c = (5 + 2 + 2) / (4 - 1) = 9 / 3 = 3 >= 2`.

---

**Generated:** 2026-10-10
