# ICPC 2026 K - Sample Median Preservation

**Type:** Math / Combinatorics
**Rating / Context:** Div 2D / Div 1B (ICPC Colombia 2026)
**Tag:** disjoint-complementary-combinatorics-median

## Key Insight

💡 Para una muestra de tamaño impar `K`, los eventos "elegir al menos `h + 1` elementos menores que la mediana" y "elegir al menos `h + 1` mayores" son mutuamente excluyentes porque `2*(h + 1) = K + 1 > K`, permitiendo calcular el complemento sumando ambos casos disjuntos sin intersección.

## Pattern Trigger

"Calcular la probabilidad de que la mediana de una muestra aleatoria de tamaño impar `K` extraída de `N <= 10^6` elementos coincida con la mediana verdadera, mod `10^9 + 7`."

## Breakthrough

Notar la disyunción estricta de los dos casos desfavorables: una muestra de tamaño `K` nunca puede tener simultáneamente mayoría de menores y mayoría de mayores, transformando un problema multivariado en dos sumas binomiales independientes.

## Code Spotlight

```cpp
int h = (K - 1) / 2;
ll total = C(N, K);
ll bad = (atLeast(N, K, L, h + 1) + atLeast(N, K, G, h + 1)) % MOD;
ll good = ((total - bad) % MOD + MOD) % MOD;
cout << good * power(total, MOD - 2) % MOD << '\n';
```

## Example

Input: `N = 5, K = 3`, datos `[1, 2, 3, 4, 5]`
Output: `800000006`
Why: Mediana verdadera es 3. Muestras favorables son 4 de 10 (`4/10 = 2/5`). `2 * 5^(-1) mod (10^9 + 7) = 2 * 400000003 = 800000006`.

---

**Generated:** 2026-10-10
