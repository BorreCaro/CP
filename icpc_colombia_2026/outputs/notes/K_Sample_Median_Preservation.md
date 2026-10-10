# Problema K: Sample Median Preservation

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Edwin Niño
- **Dificultad Estimada:** Media-Alta (Div 2D / Div 1B)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [K_Sample_Median_Preservation.cpp](../../inputs/solutions/K_Sample_Median_Preservation.cpp)

---

## 1. Deconstrucción del Enunciado

Un instituto de metrología evalúa un conjunto de `N` mediciones enteras `A_1, A_2, ..., A_N` (`-10^9 <= A_i <= 10^9`), donde `N` es un entero **impar** (`1 <= N <= 10^6`).
La mediana verdadera de la población es el valor en la posición central `(N + 1) / 2` al ordenar los datos de forma no decreciente.

Por limitaciones computacionales, se extrae una muestra aleatoria uniforme sin reemplazo de `K` elementos (`K` impar, `1 <= K <= N`). La mediana muestral es el elemento en la posición central `(K + 1) / 2` de la muestra ordenada.
Se pide calcular la probabilidad exacta de que la mediana muestral coincida con la mediana verdadera de la población.
La probabilidad se expresa como una fracción irreducible `P / Q`, y se debe imprimir el valor entero:
`P * Q^(-1) mod (10^9 + 7)`

La suma de `N` en todos los casos de prueba no excede `10^6`. La entrada finaliza con `0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`N <= 10^6` y módulo primo `10^9 + 7`:** Conteo combinatorio clásico con factoriales y sus inversos modulares precomputados en `O(MAXN)`.
- **`K` y `N` impares:** La mediana está unívocamente determinada en un índice central exacto:
  `h = (K - 1) / 2`.
  Para que un elemento sea la mediana de una muestra de tamaño `K`, debe haber a lo sumo `h` elementos menores que él y a lo sumo `h` elementos mayores que él.
- **Valores duplicados permitidos:** Puede haber múltiples ocurrencias del valor de la mediana. Esto hace crucial clasificar los elementos estrictamente en tres grupos respecto al valor de la mediana verdadera `med`:
  - `L`: elementos estrictamente menores que `med` (`A_i < med`).
  - `E`: elementos iguales a `med` (`A_i == med`).
  - `G`: elementos estrictamente mayores que `med` (`A_i > med`).

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### El Evento Complementario y la Mutua Exclusión
Ordenamos el arreglo `A`. Sea `med = A[(N - 1) / 2]` la mediana poblacional verdadera.
Contamos:
- `L = lower_bound(A.begin(), A.end(), med) - A.begin()` (elementos estrictamente menores).
- `G = A.end() - upper_bound(A.begin(), A.end(), med)` (elementos estrictamente mayores).

El espacio muestral total consta de elegir cualquier subconjunto de tamaño `K`:
`total = C(N, K) = N! / (K! * (N - K)!)`

¿Cuándo la mediana muestral **NO** es igual a `med`?
1. Si elegimos demasiados elementos estrictamente menores que `med`: es decir, si tomamos al menos `h + 1` elementos de `L`. En este caso, la posición central de la muestra estará ocupada por un valor `< med`.
2. Si elegimos demasiados elementos estrictamente mayores que `med`: es decir, si tomamos al menos `h + 1` elementos de `G`. En este caso, la posición central estará ocupada por un valor `> med`.

**El Descubrimiento Clave (Disyunción Estricta):**
¿Es posible que una muestra de tamaño `K` contenga simultáneamente al menos `h + 1` elementos de `L` Y al menos `h + 1` elementos de `G`?
Sumemos la cantidad mínima de elementos requeridos:
`(h + 1) + (h + 1) = 2*h + 2 = 2 * ((K - 1) / 2) + 2 = (K - 1) + 2 = K + 1 > K`
Como el tamaño total de la muestra es exactamente `K`, **es físicamente imposible satisfacer ambas condiciones simultáneamente**.
¡Los dos eventos desfavorables son **estrictamente disjuntos**!

### Conteo Directo por Complemento
Por tanto, la cantidad de muestras desfavorables (*bad*) es simplemente la suma directa de ambos casos, sin necesidad de aplicar el Principio de Inclusión-Exclusión:
`bad = atLeast(N, K, L, h + 1) + atLeast(N, K, G, h + 1) mod MOD`

Donde `atLeast(N, K, g, t)` cuenta las formas de elegir `K` elementos de una población de tamaño `N` conteniendo al menos `t` elementos de un grupo específico de tamaño `g`:
`atLeast(N, K, g, t) = sum_{a = t}^{min(g, K)} C(g, a) * C(N - g, K - a)`

Finalmente:
`good = (total - bad + MOD) mod MOD`
`probabilidad = (good * inv(total)) mod MOD`

- **Complejidad Temporal:** `O(N log N)` para ordenar el arreglo, más `O(K)` para evaluar la suma combinatoria. Sumando sobre todos los casos de prueba: `O(sum N log N)`.
- **Complejidad Espacial:** `O(MAXN)` para factoriales precalculados.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const ll MOD = 1'000'000'007LL;
const int MX = 1'000'005;

vector<ll> fact(MX), invFact(MX);

// Exponenciación binaria modular
ll power(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    for (; e > 0; e >>= 1) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
    }
    return r;
}

// Coeficiente binomial C(n, k) mod 10^9 + 7
ll C(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

// Formas de elegir K elementos con al menos t provenientes de un grupo de tamaño g
ll atLeast(int N, int K, int g, int t) {
    ll s = 0;
    for (int a = t; a <= min(g, K); a++) {
        s = (s + C(g, a) * C(N - g, K - a)) % MOD;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precomputación de factoriales e inversos modulares
    fact[0] = 1;
    for (int i = 1; i < MX; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    invFact[MX - 1] = power(fact[MX - 1], MOD - 2);
    for (int i = MX - 1; i > 0; i--) {
        invFact[i - 1] = invFact[i] * i % MOD;
    }

    int N, K;
    while (cin >> N >> K && (N != 0 || K != 0)) {
        vector<int> A(N);
        for (int& x : A) cin >> x;

        sort(A.begin(), A.end());
        int med = A[(N - 1) / 2];

        // L: conteo de elementos estrictamente menores que la mediana
        // G: conteo de elementos estrictamente mayores que la mediana
        int L = lower_bound(A.begin(), A.end(), med) - A.begin();
        int G = A.end() - upper_bound(A.begin(), A.end(), med);

        int h = (K - 1) / 2;
        ll total = C(N, K);

        // Los eventos "al menos h+1 menores" y "al menos h+1 mayores" son disjuntos
        ll bad = (atLeast(N, K, L, h + 1) + atLeast(N, K, G, h + 1)) % MOD;
        ll good = ((total - bad) % MOD + MOD) % MOD;

        cout << good * power(total, MOD - 2) % MOD << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Complejidad Cuadrática al Tratar Casos con Repetición:**
   Intentar iterar sobre cuántos elementos menores, cuántos iguales y cuántos mayores se seleccionan (`O(K^2)`). El cálculo complementario reduce la expresión a dos sumas lineales independientes de tamaño `O(K)`.
2. **Olvidar la Resta Modular Negativa:**
   En aritmética modular, `(total - bad)` puede resultar negativo. Olvidar sumar `MOD` antes del operador residuo (`(total - bad % MOD + MOD) % MOD`) genera números negativos o errores de desbordamiento.
3. **Confundir Índices de Mediana (1-indexado vs 0-indexado):**
   Para un arreglo ordenado de tamaño `N` impar, la mediana en índice 0 es `(N - 1) / 2`, no `N / 2` o `(N + 1) / 2`.
