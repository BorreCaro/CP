# Problema B: Birthday

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Media (Div 2C / Digit DP)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución: [B_Birthday.cpp](../../inputs/solutions/B_Birthday.cpp)

---

## 1. Deconstrucción del Enunciado

Dados un entero `k` y un número primo `p` (`1 <= k, p <= 2000`), calcular cuántos enteros no negativos distintos de **a lo sumo `k` dígitos** son simultáneamente **palíndromos** (sin ceros a la izquierda, salvo el propio número `0`) y **divisibles por `p`**, módulo `10^9 + 7`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- `k, p <= 2000`: Si se ejecutara una DP de dígitos independiente para cada longitud fija `L in [1, k]` desde los extremos hacia el centro, el costo sería `O(k^2 * p) ~ 4 * 10^9` operaciones, excediendo el límite de tiempo.
- **Invariante de expansión desde el centro hacia afuera (*Inside-Out Palindrome DP*):** Si en lugar de construir el palíndromo de afuera hacia adentro lo expandimos **del centro hacia afuera**, un núcleo palindrómico `X` de longitud `L - 2` (permitiendo ceros a la izquierda en el núcleo interno) al ser envuelto por el dígito `d` en ambos extremos se transforma en:
  `X_nuevo = d * 10^(L - 1) + 10 * X + d = 10 * X + d * (10^(L - 1) + 1)`.
  Esta transición permite reutilizar la tabla de programación dinámica a través de **todas** las longitudes `L = 1 .. k` en una sola pasada de complejidad `O(k * p)`.

---

## 3. Técnicas y Conceptos Teóricos

Separamos los núcleos palindrómicos según la paridad de su longitud `L`:

1. **Longitudes pares (`L = 0, 2, 4, ...`):**
   - Estado base `L = 0`: el núcleo vacío representa el valor `0`, por lo que `dp_even[0] = 1`.
   - Para pasar de `L - 2` a `L`, cada resto `r` transiciona con cada dígito `d in [0, 9]` hacia `nr = (10 * r + d * (10^(L - 1) + 1)) % p`.
   - Si `d >= 1` (sin cero inicial en la capa exterior de longitud `L`) y `nr == 0`, sumamos `dp_even[r]` a la respuesta global acumulada.

2. **Longitudes impares (`L = 1, 3, 5, ...`):**
   - Estado base `L = 1`: los dígitos `d in [0, 9]` forman palíndromos válidos de 1 dígito (incluyendo el `0`). Para cada `d`, incrementamos `dp_odd[d % p]` y, si `d % p == 0`, sumamos `1` a la respuesta global.
   - Para pasar de `L - 2` a `L` (`L = 3, 5, ...`), aplicamos exactamente la misma regla de envoltura `nr = (10 * r + d * (10^(L - 1) + 1)) % p`, sumando a la respuesta cuando `d >= 1` y `nr == 0`.

---

## 4. Estrategia de Implementación Limpia

- **Complejidad Temporal:** `O(10 * k * p)` (`~4 * 10^7` operaciones elementales, `< 0.05 s`).
- **Complejidad Espacial:** `O(p + k)` usando arreglos rodantes para `dp_even` y `dp_odd`.

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, p;
    if (!(cin >> k >> p)) return 0;

    vector<int> pow10(k + 1, 1 % p);
    for (int i = 1; i <= k; ++i) {
        pow10[i] = (pow10[i - 1] * 10) % p;
    }

    long long ans = 0;
    vector<int> dp_even(p, 0), dp_odd(p, 0);

    dp_even[0] = 1;
    for (int d = 0; d <= 9; ++d) {
        int r = d % p;
        dp_odd[r] = (dp_odd[r] + 1) % MOD;
        if (r == 0) ans = (ans + 1) % MOD;
    }

    for (int L = 2; L <= k; ++L) {
        const vector<int>& prev_dp = (L % 2 == 0) ? dp_even : dp_odd;
        vector<int> next_dp(p, 0);
        int coeff = (pow10[L - 1] + 1) % p;

        for (int r = 0; r < p; ++r) {
            int ways = prev_dp[r];
            if (!ways) continue;
            int base_r = (r * 10) % p;

            for (int d = 0; d <= 9; ++d) {
                int nr = (base_r + d * coeff) % p;
                next_dp[nr] += ways;
                if (next_dp[nr] >= MOD) next_dp[nr] -= MOD;

                if (d >= 1 && nr == 0) {
                    ans += ways;
                    if (ans >= MOD) ans -= MOD;
                }
            }
        }

        if (L % 2 == 0) dp_even = move(next_dp);
        else dp_odd = move(next_dp);
    }

    cout << ans << "\n";
    return 0;
}
```
