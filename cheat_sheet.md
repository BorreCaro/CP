# CP Master Cheat Sheet (C++17)

Guía de referencia rápida, autocontenida y lista para competencias oficiales (ICPC, RPC, Codeforces). Diseñada para máxima velocidad de consulta y copia directa durante concursos.

---

## Índice General

1. [Plantilla Base & Fast I/O](#1-plantilla-base--fast-io)
2. [Teoría de Números & Aritmética](#2-teoría-de-números--aritmética)
   - [2.1 GCD & LCM (Euclides & std::gcd)](#21-gcd--lcm-máximo-común-divisor-y-mínimo-común-múltiplo)
   - [2.2 Prueba de Primalidad Unitaria (is_prime_single)](#22-prueba-de-primalidad-unitaria-is_prime_single)
   - [2.3 Criba de Eratóstenes Clásica (sieve_of_eratosthenes)](#23-criba-de-eratóstenes-clásica-sieve_of_eratosthenes)
   - [2.4 Criba Lineal de Euler & Menor Factor Primo (linear_sieve_spf)](#24-criba-lineal-de-euler--menor-factor-primo-linear_sieve_spf)
   - [2.5 Criba de Divisores: Conteo y Suma (criba_divisores)](#25-criba-de-divisores-criba_divisores)
   - [2.6 MCD de Diferencias de un Arreglo (array_diff_gcd)](#26-mcd-de-diferencias-de-un-arreglo-array_diff_gcd)
   - [2.7 Diferencia de Cuadrados Enteros (solve_difference_of_squares)](#27-diferencia-de-cuadrados-enteros-solve_difference_of_squares)
   - [2.8 División de Entero Gigante en String (divide_large_number)](#28-división-de-entero-gigante-en-string-divide_large_number)
3. [Aritmética Modular & Combinatoria](#3-aritmética-modular--combinatoria)
   - [3.1 Operaciones Modulares Básicas (add, sub, mul)](#31-operaciones-modulares-básicas-add_mod-sub_mod-mul_mod)
   - [3.2 Exponenciación Binaria Modular (binpow)](#32-exponenciación-binaria-modular-binpow)
   - [3.3 Algoritmo Extendido de Euclides (extgcd)](#33-algoritmo-extendido-de-euclides-extgcd)
   - [3.4 Inverso Modular: Teorema de Fermat (inv_fermat)](#34-inverso-modular-pequeño-teorema-de-fermat-inv_fermat)
   - [3.5 Inverso Modular: Euclides Extendido (inv_extgcd)](#35-inverso-modular-euclides-extendido-inv_extgcd)
   - [3.6 Precálculo de Factoriales e Inversos (init_fact)](#36-precálculo-de-factoriales-e-inversos-init_fact)
   - [3.7 Coeficientes Binomiales y Permutaciones (nCr, nPr)](#37-combinatoria-modular-ncr-y-npr-en-o1)
4. [Bit Manipulation, Submáscaras & Teoría de Juegos](#4-bit-manipulation-submáscaras--teoría-de-juegos)
   - [4.1 GCC Builtins Esenciales & log2_floor](#41-gcc-builtins-esenciales--log2_floor)
   - [4.2 Enumeración y Recorrido de Submáscaras](#42-enumeración-y-recorrido-de-submáscaras)
   - [4.3 Conversión Entero a Binario (to_binary_string)](#43-conversión-entero-a-binario-to_binary_string)
   - [4.4 Prefijo y Rango XOR en O(1) (xor_n, xor_range)](#44-prefijo-y-rango-xor-en-o1-xor_n-xor_range)
   - [4.5 Cálculo de MEX (mex)](#45-cálculo-de-mex-mex---minimum-excluded-value)
   - [4.6 Juego de Nim Clásico (nim_is_winning)](#46-juego-de-nim-clásico-nim_is_winning)
5. [Arreglos, Rangos, Two Pointers & Greedy](#5-arreglos-rangos-two-pointers--greedy)
   - [5.1 Sumas de Prefijos 1D (0-idx y 1-idx)](#51-sumas-de-prefijos-1d-0-indexed--1-indexed)
   - [5.2 Arreglo de Diferencias 1D (Difference Array)](#52-arreglo-de-diferencias-1d-difference-array-1d)
   - [5.3 Doble Arreglo de Diferencias (PA 1D y Matriz 2D)](#53-doble-arreglo-de-diferencias)
   - [5.4 Two Pointers / Ventana Deslizante Bounded Sum (max_subarray_sum_bound)](#54-two-pointers--ventana-deslizante-bounded-sum-max_subarray_sum_bound)
   - [5.5 Ventana Deslizante con hasta K Modificaciones (max_window_k_changes)](#55-ventana-deslizante-con-hasta-k-cambios-max_window_k_changes)
   - [5.6 Compresión de Coordenadas (Coordinate Compression)](#56-compresión-de-coordenadas-coordinate-compression)
   - [5.7 Conteo de Parejas Idénticas (count_equal_pairs)](#57-conteo-de-parejas-idénticas-count_equal_pairs)
   - [5.8 Buy-and-Regret Greedy con Priority Queue](#58-buy-and-regret-greedy-con-priority-queue)
6. [Búsqueda Binaria](#6-búsqueda-binaria)
   - [6.1 Búsqueda Binaria para Máximo (TTT...FFF)](#61-búsqueda-binaria-para-máximo-predicado-tttfff)
   - [6.2 Búsqueda Binaria para Mínimo (FFF...TTT)](#62-búsqueda-binaria-para-mínimo-predicado-fffttt)
   - [6.3 Búsqueda Binaria en Espacio Continuo / Reales](#63-búsqueda-binaria-en-espacio-continuo--reales)
7. [Estructuras de Datos](#7-estructuras-de-datos)
   - [7.1 Disjoint Set Union (DSU)](#71-disjoint-set-union-dsu)
   - [7.2 Fenwick Tree / Binary Indexed Tree (BIT)](#72-fenwick-tree--binary-indexed-tree-bit)
8. [Grafos & Árboles](#8-grafos--árboles)
   - [8.1 Grid BFS / Flood Fill con Etiquetado de Componentes](#81-grid-bfs--flood-fill-con-etiquetado-de-componentes)
   - [8.2 Multi-Source BFS con Inversión de Aristas](#82-multi-source-bfs-con-inversión-de-aristas)
   - [8.3 0-1 BFS con std::deque](#83-0-1-bfs-con-stddeque)
   - [8.4 Dijkstra con Reconstrucción de Camino Más Corto](#84-dijkstra-con-reconstrucción-de-camino-más-corto)
   - [8.5 Diámetro de un Árbol con Doble BFS](#85-diámetro-de-un-árbol-con-doble-bfs)
   - [8.6 Dinic's Algorithm (Flujo Máximo & Corte Mínimo)](#86-dinics-algorithm-flujo-máximo--corte-mínimo)
9. [Strings & Geometría Computacional 2D](#9-strings--geometría-computacional-2d)
   - [9.1 Rotación Mínima Lexicográfica de un String (Booth)](#91-rotación-mínima-lexicográfica-de-un-string-algoritmo-de-booth)
   - [9.2 Geometría 2D: Estructura Point, Producto Cruz y Giro CCW](#92-geometría-2d-estructura-point-producto-cruz-y-giro-ccw)
   - [9.3 Envolvente Convexa / Convex Hull (Monotone Chain de Andrew)](#93-envolvente-convexa--convex-hull-monotone-chain-de-andrew)

---

## 1. Plantilla Base & Fast I/O

```cpp
#include <bits/stdc++.h>
using namespace std;

// Alias de conveniencia
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// Constantes estándar
const ll INF64 = 1e18;
const int INF32 = 1e9;
const ll MOD = 1e9 + 7; // o 998244353

int main() {
    // Fast I/O obligatoria en CP (desvincula flujos C/C++ y vaciado automático de cout)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
```

---

## 2. Teoría de Números & Aritmética

### 2.1 GCD & LCM (Máximo Común Divisor y Mínimo Común Múltiplo)
- **Complejidad:** `O(log(min(a, b)))` tiempo, `O(1)` espacio.
- **En C++17:** `<numeric>` provee nativamente `std::gcd(a, b)` y `std::lcm(a, b)`.
- **Invariante clave:** Dividir antes de multiplicar en LCM para prevenir desbordamiento de 64 bits: `lcm(a, b) = (a / gcd(a, b)) * b`.

```cpp
long long gcd_custom(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long lcm_custom(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd_custom(a, b)) * b;
}
```

---

### 2.2 Prueba de Primalidad Unitaria (`is_prime_single`)
- **Propósito:** Determinar si un entero individual `n <= 10^12` es primo.
- **Complejidad:** `O(sqrt(N))` tiempo, `O(1)` espacio.
- **Optimización de paso 6:** Todo primo mayor a 3 es de la forma `6k +- 1`. Saltamos de 6 en 6 probando divisores `i` e `i + 2`.

```cpp
bool is_prime_single(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
```

---

### 2.3 Criba de Eratóstenes Clásica (`sieve_of_eratosthenes`)
- **Propósito:** Marcar todos los números primos hasta `N` (típicamente `N <= 10^7`).
- **Complejidad:** `O(N log(log N))` tiempo, `O(N)` espacio (`vector<bool>` usa 1 bit por elemento).

```cpp
vector<bool> sieve_of_eratosthenes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= n; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                is_prime[i] = false;
            }
        }
    }
    return is_prime;
}
```

---

### 2.4 Criba Lineal de Euler & Menor Factor Primo (`linear_sieve_spf`)
- **Propósito:** Computar el Menor Factor Primo (`spf[i]`) para todo `i <= N` en exactamente `O(N)` tiempo lineal estricto. Cada número compuesto es visitado exactamente una vez por su factor primo más pequeño.
- **Factorización instantánea:** Cualquier número `x <= N` se factoriza en `O(log X)` tiempo.

```cpp
vector<int> primes, spf;

void linear_sieve_spf(int n) {
    spf.assign(n + 1, 0);
    primes.clear();
    for (int i = 2; i <= n; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > n) break;
            spf[i * p] = p;
        }
    }
}

// Factorización prima completa en O(log X) mediante saltos de SPF
vector<pair<int, int>> factorize_spf(int x) {
    vector<pair<int, int>> factors;
    while (x > 1) {
        int p = spf[x];
        int count = 0;
        while (x % p == 0) {
            count++;
            x /= p;
        }
        factors.push_back({p, count});
    }
    return factors;
}
```

---

### 2.5 Criba de Divisores (`criba_divisores`)
- **Propósito:** Precalcular la cantidad de divisores `num_div[i]` (`d(i)`) y la suma de divisores `sum_div[i]` (`sigma(i)`) para todos los enteros hasta `N`.
- **Complejidad:** `O(N log N)` tiempo, `O(N)` espacio.

```cpp
void criba_divisores(int n, vector<int> &num_div, vector<long long> &sum_div) {
    num_div.assign(n + 1, 0);
    sum_div.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            num_div[j]++;
            sum_div[j] += i;
        }
    }
}
```

---

### 2.6 MCD de Diferencias de un Arreglo (`array_diff_gcd`)
- **Problema clásico:** Hallar el mayor entero `k` tal que `a[i] == a[j] (mod k)` para todo par `(i, j)` en el arreglo.
- **Invariante:** `a[i] == a[0] (mod k) <=> k | (a[i] - a[0])`.
- **Resultado:** `k = gcd(|a[1] - a[0]|, |a[2] - a[0]|, ..., |a[n - 1] - a[0]|)`. Si `k == 0`, todos los elementos son idénticos y cualquier número entero divide la diferencia.

```cpp
long long array_diff_gcd(const vector<long long> &a) {
    if (a.empty()) return 0;
    long long g = 0;
    for (size_t i = 1; i < a.size(); ++i) {
        g = std::gcd(g, std::abs(a[i] - a[0]));
    }
    return g;
}
```

---

### 2.7 Diferencia de Cuadrados Enteros (`solve_difference_of_squares`)
- **Problema:** Encontrar todas las parejas de enteros positivos `(x, y)` tales que `x^2 - y^2 = n`.
- **Estrategia:** Factorizar `n = u * v` con `1 <= u <= v`. Como `(x - y)(x + y) = n`, asignamos `u = x - y` y `v = x + y`.
- **Solución:** `x = (u + v) / 2` e `y = (v - u) / 2`. Para que sean enteros, `u` y `v` deben tener la misma paridad (`(u + v) % 2 == 0`).
- **Propiedad:** Si `n % 4 == 2`, nunca hay soluciones enteras.
- **Complejidad:** `O(sqrt(N))` tiempo.

```cpp
vector<pair<long long, long long>> solve_difference_of_squares(long long n) {
    vector<pair<long long, long long>> solutions;
    if (n <= 0) return solutions;
    for (long long u = 1; u * u <= n; ++u) {
        if (n % u == 0) {
            long long v = n / u;
            if ((u + v) % 2 == 0) {
                long long x = (u + v) / 2;
                long long y = (v - u) / 2;
                if (y > 0) { // Enteros positivos estrictos
                    solutions.push_back({x, y});
                }
            }
        }
    }
    return solutions;
}
```

---

### 2.8 División de Entero Gigante en String (`divide_large_number`)
- **Propósito:** Dividir un entero de longitud arbitraria (representado como `string`, hasta `10^6` caracteres) entre un divisor `long long`.
- **Retorno:** Par `{cociente_en_string, residuo_entero}`.
- **Complejidad:** `O(L)` donde `L = num.size()`.

```cpp
pair<string, long long> divide_large_number(const string &num, long long divisor) {
    string quotient = "";
    long long rem = 0;
    for (char c : num) {
        rem = rem * 10 + (c - '0');
        quotient.push_back(rem / divisor + '0');
        rem %= divisor;
    }
    size_t first_non_zero = quotient.find_first_not_of('0');
    if (first_non_zero != string::npos) {
        quotient = quotient.substr(first_non_zero);
    } else {
        quotient = "0";
    }
    return {quotient, rem};
}
```

---

## 3. Aritmética Modular & Combinatoria

### 3.1 Operaciones Modulares Básicas (`add_mod`, `sub_mod`, `mul_mod`)
- Manejo riguroso de negativos y prevención de desbordamiento de 64 bits utilizando `__int128`.

```cpp
long long add_mod(long long a, long long b, long long m) {
    return (a % m + b % m) % m;
}

long long sub_mod(long long a, long long b, long long m) {
    return ((a % m - b % m) % m + m) % m;
}

long long mul_mod(long long a, long long b, long long m) {
    return (long long)((__int128)(a % m + m) % m * ((b % m + m) % m) % m);
}
```

---

### 3.2 Exponenciación Binaria Modular (`binpow`)
- **Propósito:** Calcular `(a^b) % m` en `O(log b)` pasos de multiplicación.

```cpp
long long binpow(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (long long)((__int128)res * a % m);
        a = (long long)((__int128)a * a % m);
        b >>= 1;
    }
    return res;
}
```

---

### 3.3 Algoritmo Extendido de Euclides (`extgcd`)
- **Propósito:** Hallar enteros `x, y` tales que `a * x + b * y = gcd(a, b)`.
- **Complejidad:** `O(log(min(a, b)))`.

```cpp
long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
```

---

### 3.4 Inverso Modular: Pequeño Teorema de Fermat (`inv_fermat`)
- **Condición estricta:** Requiere que `m` sea **primo** y `gcd(a, m) == 1`.
- **Fórmula:** `a^(m - 1) == 1 (mod m) => a^(-1) == a^(m - 2) (mod m)`.

```cpp
long long inv_fermat(long long a, long long m) {
    return binpow(a, m - 2, m);
}
```

---

### 3.5 Inverso Modular: Euclides Extendido (`inv_extgcd`)
- **Condición:** Funciona para **cualquier módulo m** (primo o compuesto), siempre y cuando `gcd(a, m) == 1`.
- Si `gcd(a, m) != 1`, el inverso no existe y retorna `-1`.

```cpp
long long inv_extgcd(long long a, long long m) {
    long long x, y;
    long long g = extgcd(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}
```

---

### 3.6 Precálculo de Factoriales e Inversos (`init_fact`)
- **Propósito:** Precalcular `fact[i]` e `inv_fact[i]` para `0 <= i <= N` en `O(N)` tiempo total con módulo primo `m`.
- **Optimización:** Calcula el inverso de `fact[n]` una sola vez con `inv_fermat`, luego retrocede en `O(1)` por paso: `inv_fact[i] = inv_fact[i + 1] * (i + 1) % m`.

```cpp
vector<long long> fact, inv_fact;

void init_fact(int n, long long m) {
    fact.assign(n + 1, 1);
    inv_fact.assign(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fact[i] = (long long)((__int128)fact[i - 1] * i % m);
    }
    inv_fact[n] = inv_fermat(fact[n], m);
    for (int i = n - 1; i >= 0; --i) {
        inv_fact[i] = (long long)((__int128)inv_fact[i + 1] * (i + 1) % m);
    }
}
```

---

### 3.7 Combinatoria Modular: `nCr` y `nPr` en `O(1)`
```cpp
long long nCr(int n, int r, long long m) {
    if (r < 0 || r > n) return 0;
    return (long long)((__int128)fact[n] * inv_fact[r] % m * inv_fact[n - r] % m);
}

long long nPr(int n, int r, long long m) {
    if (r < 0 || r > n) return 0;
    return (long long)((__int128)fact[n] * inv_fact[n - r] % m);
}
```

---

## 4. Bit Manipulation, Submáscaras & Teoría de Juegos

### 4.1 GCC Builtins Esenciales & `log2_floor`
- Instrucciones nativas de hardware en tiempo constante `O(1)`. En variables de 64 bits (`long long`), usar el sufijo `ll`.

```cpp
// Conteo de bits encendidos (1s)
int cnt = __builtin_popcountll(x);

// Cantidad de ceros iniciales a la izquierda (leading zeros) para x > 0
int lz = __builtin_clzll(x);

// Cantidad de ceros finales a la derecha (trailing zeros / posición del LSB) para x > 0
int tz = __builtin_ctzll(x);

// Piso de log2(x) para x > 0 en O(1)
int log2_floor(unsigned long long x) {
    return 63 - __builtin_clzll(x);
}

// Aislar el bit menos significativo encendido (LSB)
long long lsb = x & -x;

// Apagar el bit menos significativo encendido
long long cleared_lsb = x & (x - 1);
```

---

### 4.2 Enumeración y Recorrido de Submáscaras
- **Recorrido de submáscaras de una máscara fija `mask`:**
  Itera todas las submáscaras no vacías en orden descendente. Si se requiere incluir la máscara vacía (`s = 0`), procesar `s = 0` al finalizar.

```cpp
for (int s = mask; s > 0; s = (s - 1) & mask) {
    // Procesar submáscara no vacía s
}
```

- **Recorrido de todas las submáscaras de todas las máscaras hasta `2^N`:**
  Complejidad matemática exacta: `sumatorio sobre k de C(N, k) * 2^k = 3^N`. Para `N = 15`, `3^15 ~= 1.43 * 10^7` operaciones (ejecución casi instantánea).

```cpp
for (int mask = 0; mask < (1 << n); ++mask) {
    for (int s = mask; s > 0; s = (s - 1) & mask) {
        // Ejecución global en O(3^N)
    }
}
```

---

### 4.3 Conversión Entero a Binario (`to_binary_string`)
- Genera la representación binaria exacta como `string`, con relleno opcional de ceros a la izquierda (`min_bits`).

```cpp
string to_binary_string(long long n, int min_bits = 0) {
    if (n == 0) return string(max(1, min_bits), '0');
    string s = "";
    while (n > 0) {
        s.push_back((n & 1) ? '1' : '0');
        n >>= 1;
    }
    while ((int)s.size() < min_bits) s.push_back('0');
    reverse(s.begin(), s.end());
    return s;
}
```

---

### 4.4 Prefijo y Rango XOR en `O(1)` (`xor_n`, `xor_range`)
- **Propiedad periódica:** La suma XOR acumulada de `1 ^ 2 ^ ... ^ n` tiene período 4:
  - `n % 4 == 0 => n`
  - `n % 4 == 1 => 1`
  - `n % 4 == 2 => n + 1`
  - `n % 4 == 3 => 0`
- **Consulta de intervalo:** `xor_range(l, r) = xor_n(r) ^ xor_n(l - 1)`.

```cpp
long long xor_n(long long n) {
    long long rem = n % 4;
    if (rem == 0) return n;
    if (rem == 1) return 1;
    if (rem == 2) return n + 1;
    return 0;
}

long long xor_range(long long l, long long r) {
    if (l > r) return 0;
    return xor_n(r) ^ xor_n(l - 1);
}
```

---

### 4.5 Cálculo de MEX (`mex` - Minimum Excluded Value)
- Encuentra el menor entero no negativo (`>= 0`) ausente en una colección de valores.
- **Complejidad:** `O(K)` lineal estricto donde `K = vals.size()`.

```cpp
int mex(const vector<int> &vals) {
    int k = vals.size();
    vector<bool> present(k + 1, false);
    for (int x : vals) {
        if (x >= 0 && x <= k) present[x] = true;
    }
    for (int i = 0; i <= k; ++i) {
        if (!present[i]) return i;
    }
    return k + 1;
}
```

---

### 4.6 Juego de Nim Clásico (`nim_is_winning`)
- **Teorema de Bouton / Sprague-Grundy:** En un juego imparcial donde cada jugador retira cualquier cantidad de fichas de una sola pila, la posición es ganadora para el primer jugador si y solo si el Nim-Sum (`xor` de los tamaños de las pilas) es distinto de cero.

```cpp
bool nim_is_winning(const vector<long long> &piles) {
    long long nim_sum = 0;
    for (long long x : piles) nim_sum ^= x;
    return nim_sum != 0;
}
```

---

## 5. Arreglos, Rangos, Two Pointers & Greedy

### 5.1 Sumas de Prefijos 1D (0-indexed & 1-indexed)
- **Consulta en rango:** `O(1)` tras precálculo `O(N)`.

```cpp
// 0-indexed: pre[i + 1] = pre[i] + a[i]
// Suma de a[l...r] = pre[r + 1] - pre[l]
vector<long long> build_prefix_0idx(const vector<long long> &a) {
    int n = a.size();
    vector<long long> pre(n + 1, 0);
    for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + a[i];
    return pre;
}

// 1-indexed: pre[i] = pre[i - 1] + a[i]
// Suma de a[l...r] = pre[r] - pre[l - 1]
vector<long long> build_prefix_1idx(const vector<long long> &a) {
    int n = a.size() - 1;
    vector<long long> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i];
    return pre;
}
```

---

### 5.2 Arreglo de Diferencias 1D (Difference Array 1D)
- Aplica múltiples operaciones de rango `a[l...r] += val` en tiempo `O(1)` cada una. Al finalizar, un barrido de prefijo reconstruye el arreglo en `O(N)`.

```cpp
struct DifferenceArray1D {
    int n;
    vector<long long> diff;
    DifferenceArray1D(int n) : n(n), diff(n + 2, 0) {}

    void add_range(int l, int r, long long val) { // 1-indexed
        diff[l] += val;
        diff[r + 1] -= val;
    }

    vector<long long> build() {
        vector<long long> res(n + 1, 0);
        long long current = 0;
        for (int i = 1; i <= n; ++i) {
            current += diff[i];
            res[i] = current;
        }
        return res;
    }
};
```

---

### 5.3 Doble Arreglo de Diferencias

#### A) Progresión Aritmética en 1D (Segunda Diferencia)
- Suma una progresión aritmética `v, 2v, 3v, ..., k*v` en el intervalo `[l, r]` en `O(1)`.
- Reconstrucción en `O(N)` aplicando dos barridos acumulativos consecutivos.

```cpp
struct ArithmeticProgressionDiff1D {
    int n;
    vector<long long> d2;
    ArithmeticProgressionDiff1D(int n) : n(n), d2(n + 3, 0) {}

    void add_progression(int l, int r, long long v) {
        long long len = r - l + 1;
        d2[l] += v;
        d2[r + 1] -= (len + 1) * v;
        d2[r + 2] += len * v;
    }

    vector<long long> build() {
        vector<long long> d1(n + 2, 0), res(n + 1, 0);
        long long run = 0;
        for (int i = 1; i <= n; ++i) {
            run += d2[i];
            d1[i] = run;
        }
        run = 0;
        for (int i = 1; i <= n; ++i) {
            run += d1[i];
            res[i] = run;
        }
        return res;
    }
};
```

#### B) Arreglo de Diferencias 2D (Submatriz Range Add)
- Actualiza submatrices rectangulares `[r1, c1]` a `[r2, c2]` con `val` en `O(1)`. Reconstrucción en `O(R * C)`.

```cpp
struct DifferenceArray2D {
    int R, C;
    vector<vector<long long>> diff;
    DifferenceArray2D(int R, int C) : R(R), C(C), diff(R + 2, vector<long long>(C + 2, 0)) {}

    void add_rect(int r1, int c1, int r2, int c2, long long val) {
        diff[r1][c1] += val;
        diff[r1][c2 + 1] -= val;
        diff[r2 + 1][c1] -= val;
        diff[r2 + 1][c2 + 1] += val;
    }

    vector<vector<long long>> build() {
        vector<vector<long long>> grid(R + 1, vector<long long>(C + 1, 0));
        for (int r = 1; r <= R; ++r) {
            for (int c = 1; c <= C; ++c) {
                grid[r][c] = diff[r][c] + grid[r - 1][c] + grid[r][c - 1] - grid[r - 1][c - 1];
            }
        }
        return grid;
    }
};
```

---

### 5.4 Two Pointers / Ventana Deslizante Bounded Sum (`max_subarray_sum_bound`)
- **Problema:** Encontrar la máxima suma de un subarreglo con restricción de longitud en el rango `[min_len, max_len]`.
- **Estrategia:** Sumas de prefijo `pre[i] - pre[j]` con `i - max_len <= j <= i - min_len`. Optimizamos el mínimo `pre[j]` con un `deque` monótono en tiempo total `O(N)`.

```cpp
long long max_subarray_sum_bound(const vector<long long> &a, int min_len, int max_len) {
    int n = a.size();
    vector<long long> pre(n + 1, 0);
    for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + a[i];

    long long best = -1e18;
    deque<int> dq; // Mantiene candidatos j con pre[j] creciente

    for (int i = min_len; i <= n; ++i) {
        int add_idx = i - min_len;
        while (!dq.empty() && pre[dq.back()] >= pre[add_idx]) {
            dq.pop_back();
        }
        dq.push_back(add_idx);

        while (!dq.empty() && dq.front() < i - max_len) {
            dq.pop_front();
        }

        best = max(best, pre[i] - pre[dq.front()]);
    }
    return best;
}
```

---

### 5.5 Ventana Deslizante con hasta K Cambios (`max_window_k_changes`)
- **Problema:** Longitud de la mayor ventana contigua que contiene a lo sumo `k` elementos indeseados (por ejemplo, a lo sumo `k` ceros sustituibles por unos).
- **Complejidad:** `O(N)` tiempo amortizado, `O(1)` espacio.

```cpp
int max_window_k_changes(const vector<int> &a, int k) {
    int n = a.size(), l = 0, zeros = 0, best = 0;
    for (int r = 0; r < n; ++r) {
        if (a[r] == 0) zeros++;
        while (zeros > k) {
            if (a[l] == 0) zeros--;
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}
```

---

### 5.6 Compresión de Coordenadas (`Coordinate Compression`)
- Mapea valores dispersos (e.g. hasta `10^18`) a un rango compacto `[0, K - 1]` en `O(N log N)`.

```cpp
template <typename T>
struct CoordinateCompression {
    vector<T> coords;
    void add(T x) { coords.push_back(x); }
    void build() {
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
    }
    int get(T x) const {
        return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
    }
    T original(int idx) const { return coords[idx]; }
    int size() const { return coords.size(); }
};
```

---

### 5.7 Conteo de Parejas Idénticas (`count_equal_pairs`)
- Cuenta pares de índices `(i, j)` con `i < j` tales que `a[i] == a[j]`. Implementación determinista en `O(N log N)` sin colisiones de hash.

```cpp
long long count_equal_pairs(vector<long long> a) {
    sort(a.begin(), a.end());
    long long total = 0, count = 1;
    for (size_t i = 1; i <= a.size(); ++i) {
        if (i < a.size() && a[i] == a[i - 1]) {
            count++;
        } else {
            total += count * (count - 1) / 2;
            count = 1;
        }
    }
    return total;
}
```

---

### 5.8 Buy-and-Regret Greedy con Priority Queue
- **Patrón Greedy con Arrepentimiento:** Tomar una decisión voraz de inmediato y almacenarla en una `priority_queue`. Si más adelante se viola una restricción (e.g. presupuesto o fecha límite), revertimos la peor decisión previa en `O(log N)`.

```cpp
long long buy_and_regret_max_items(const vector<long long> &cost, long long budget) {
    priority_queue<long long> pq; // Max-heap con costos pagados
    long long total_spent = 0;
    for (long long c : cost) {
        total_spent += c;
        pq.push(c);
        if (total_spent > budget) {
            total_spent -= pq.top(); // Nos arrepentimos del ítem más caro
            pq.pop();
        }
    }
    return pq.size();
}
```

---

## 6. Búsqueda Binaria

### 6.1 Búsqueda Binaria para Máximo (Predicado `TTT...FFF`)
- Busca el **mayor** valor entero `x` en `[low, high]` tal que `check(x) == true`. Si ningún elemento cumple, retorna `low - 1`.

```cpp
long long bsearch_max(long long low, long long high, const function<bool(long long)> &check) {
    long long ans = low - 1;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            low = mid + 1; // Probar si un valor mayor es posible
        } else {
            high = mid - 1;
        }
    }
    return ans;
}
```

---

### 6.2 Búsqueda Binaria para Mínimo (Predicado `FFF...TTT`)
- Busca el **menor** valor entero `x` en `[low, high]` tal que `check(x) == true`. Si ningún elemento cumple, retorna `high + 1`.

```cpp
long long bsearch_min(long long low, long long high, const function<bool(long long)> &check) {
    long long ans = high + 1;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1; // Probar si un valor menor es posible
        } else {
            low = mid + 1;
        }
    }
    return ans;
}
```

---

### 6.3 Búsqueda Binaria en Espacio Continuo / Reales
- Usa un número fijo de iteraciones (e.g. 100 pasos). 100 iteraciones reducen el rango por `2^100 ~= 10^30`, garantizando precisión óptima sin bucles infinitos por redondeo de punto flotante.

```cpp
double bsearch_continuous(double low, double high, const function<bool(double)> &check, int iters = 100) {
    for (int iter = 0; iter < iters; ++iter) {
        double mid = low + (high - low) / 2.0;
        if (check(mid)) {
            low = mid; // Cambiar a high = mid según la dirección del predicado
        } else {
            high = mid;
        }
    }
    return low;
}
```

---

## 7. Estructuras de Datos

### 7.1 Disjoint Set Union (`DSU`)
- Conjuntos disjuntos con compresión de caminos y unión por tamaño. Tiempo casi constante `O(alpha(N))` por operación.

```cpp
struct DSU {
    int n, num_sets;
    vector<int> parent, sz;

    DSU(int n) : n(n), num_sets(n), parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j) return false;
        if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
        parent[root_j] = root_i;
        sz[root_i] += sz[root_j];
        num_sets--;
        return true;
    }

    bool same(int i, int j) {
        return find(i) == find(j);
    }

    int size(int i) {
        return sz[find(i)];
    }
};
```

---

### 7.2 Fenwick Tree / Binary Indexed Tree (`BIT`)
- Estructura 1-indexada para actualización puntual y consulta de suma en rango en `O(log N)` tiempo y `O(N)` memoria con constante ultra-ligera.

```cpp
template <typename T>
struct Fenwick {
    int n;
    vector<T> tree;

    Fenwick(int n) : n(n), tree(n + 1, 0) {}

    void add(int i, T delta) { // i en rango [1, n]
        for (; i <= n; i += i & -i) tree[i] += delta;
    }

    T query(int i) { // Suma acumulada en [1, i]
        T sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }

    T query(int l, int r) { // Suma en [l, r]
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};
```

---

## 8. Grafos & Árboles

### 8.1 Grid BFS / Flood Fill con Etiquetado de Componentes
- Recorre cuadrículas 2D etiquetando cada celda alcanzable con su ID de componente conexa y computando el tamaño total de cada componente en `O(R * C)`.

```cpp
const int DR[] = {-1, 1, 0, 0};
const int DC[] = {0, 0, -1, 1};

void grid_flood_fill(const vector<string> &grid, vector<vector<int>> &comp_id, vector<int> &comp_sz) {
    int R = grid.size(), C = grid[0].size();
    comp_id.assign(R, vector<int>(C, -1));
    comp_sz.clear();
    int current_id = 0;

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] == '#' || comp_id[r][c] != -1) continue;
            int sz = 0;
            queue<pair<int, int>> q;
            comp_id[r][c] = current_id;
            q.push({r, c});

            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();
                sz++;
                for (int d = 0; d < 4; ++d) {
                    int nr = cr + DR[d], nc = cc + DC[d];
                    if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#' && comp_id[nr][nc] == -1) {
                        comp_id[nr][nc] = current_id;
                        q.push({nr, nc});
                    }
                }
            }
            comp_sz.push_back(sz);
            current_id++;
        }
    }
}
```

---

### 8.2 Multi-Source BFS con Inversión de Aristas
- Modela problemas donde invertir el sentido de una arista dirigida cuesta 1 y recorrerla en su sentido natural cuesta 0 (o búsqueda de distancia mínima desde múltiples fuentes iniciales simultáneas).

```cpp
vector<int> multi_source_edge_inversion_bfs(int n, const vector<vector<pair<int, int>>> &adj, const vector<int> &sources) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    deque<int> dq;

    for (int s : sources) {
        dist[s] = 0;
        dq.push_back(s);
    }

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto &[v, cost] : adj[u]) {
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                if (cost == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}
```

---

### 8.3 0-1 BFS con `std::deque`
- Camino más corto en grafos donde el peso de cada arista es estrictamente 0 o 1. Complejidad `O(V + E)` lineal.

```cpp
vector<int> bfs_01(int n, int start, const vector<vector<pair<int, int>>> &adj) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    deque<int> dq;

    dist[start] = 0;
    dq.push_back(start);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}
```

---

### 8.4 Dijkstra con Reconstrucción de Camino Más Corto
- Camino más corto en grafos con pesos no negativos en `O((V + E) log V)`. Reconstrucción directa del camino mediante el vector `parent`.

```cpp
pair<vector<long long>, vector<int>> dijkstra(int n, int start, const vector<vector<pair<int, long long>>> &adj) {
    const long long INF = 1e18;
    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);
    using pli = pair<long long, int>;
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return {dist, parent};
}

vector<int> reconstruct_path(int target, const vector<int> &parent) {
    vector<int> path;
    for (int curr = target; curr != -1; curr = parent[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());
    return path;
}
```

---

### 8.5 Diámetro de un Árbol con Doble BFS
- Encuentra la máxima distancia entre cualquier par de nodos en un árbol y sus dos extremos `(u, v)` en `O(V + E)`.
- **Propiedad:** El nodo más lejano a cualquier nodo arbitrario siempre es uno de los extremos del diámetro.

```cpp
pair<int, pair<int, int>> tree_diameter(int n, const vector<vector<int>> &adj) {
    auto bfs = [&](int start) -> pair<int, int> {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        int farthest = start;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] > dist[farthest]) farthest = u;
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return {farthest, dist[farthest]};
    };

    int u = bfs(0).first;
    auto [v, diameter] = bfs(u);
    return {diameter, {u, v}};
}
```

---

### 8.6 Dinic's Algorithm (Flujo Máximo & Corte Mínimo)
- Algoritmo estándar para Flujo Máximo y Corte Mínimo.
- **Complejidad:** `O(V^2 * E)` en redes generales y `O(E * sqrt(V))` en redes con capacidades unitarias (e.g. Bipartite Matching).

```cpp
struct Dinic {
    struct Edge {
        int to;
        long long cap;
        long long flow;
        int rev;
    };
    int n, s, t;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;

    Dinic(int n, int s, int t) : n(n), s(s), t(t), adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, long long cap) {
        adj[from].push_back({to, cap, 0, (int)adj[from].size()});
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &edge : adj[v]) {
                if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0 || v == t) return pushed;
        for (int &cid = ptr[v]; cid < (int)adj[v].size(); ++cid) {
            auto &edge = adj[v][cid];
            int tr = edge.to;
            if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
            long long tr_pushed = dfs(tr, min(pushed, edge.cap - edge.flow));
            if (tr_pushed == 0) continue;
            edge.flow += tr_pushed;
            adj[tr][edge.rev].flow -= tr_pushed;
            return tr_pushed;
        }
        return 0;
    }

    long long max_flow() {
        long long flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, 1e18)) {
                flow += pushed;
            }
        }
        return flow;
    }

    // Vértices alcanzables desde 's' en el grafo residual componen la partición S del Min-Cut
    vector<bool> min_cut() {
        vector<bool> in_s(n, false);
        queue<int> q;
        q.push(s);
        in_s[s] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &edge : adj[v]) {
                if (edge.cap - edge.flow > 0 && !in_s[edge.to]) {
                    in_s[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
        return in_s;
    }
};
```

---

## 9. Strings & Geometría Computacional 2D

### 9.1 Rotación Mínima Lexicográfica de un String (Algoritmo de Booth)
- **Problema:** Encontrar el índice inicial `k` de la rotación cíclica lexicográficamente menor de un string `s`.
- **Complejidad:** Estrictamente `O(N)` tiempo y espacio mediante función de fallo de KMP.

```cpp
int booth_min_rotation(string s) {
    s += s;
    int n = s.size();
    vector<int> f(n, -1);
    int k = 0;
    for (int j = 1; j < n; ++j) {
        char sj = s[j];
        int i = f[j - k - 1];
        while (i != -1 && sj != s[k + i + 1]) {
            if (sj < s[k + i + 1]) {
                k = j - i - 1;
            }
            i = f[i];
        }
        if (sj != s[k + i + 1]) {
            if (sj < s[k]) {
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}
```

---

### 9.2 Geometría 2D: Estructura `Point`, Producto Cruz y Giro CCW
- Representación entera de puntos y vectores 2D sin imprecisiones flotantes.

```cpp
struct Point {
    long long x, y;
    Point() : x(0), y(0) {}
    Point(long long x, long long y) : x(x), y(y) {}
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator==(const Point &p) const { return x == p.x && y == p.y; }
};

long long cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

// Producto cruz con respecto a un origen pivote 'o':
// > 0 : Giro a la izquierda (Counter-Clockwise / CCW)
// < 0 : Giro a la derecha (Clockwise / CW)
// = 0 : Puntos colineales
long long cross_product(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}

long long dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
```

---

### 9.3 Envolvente Convexa / Convex Hull (Monotone Chain de Andrew)
- Construye el polígono convexo mínimo que encierra un conjunto de `N` puntos en `O(N log N)`.
- Si se desean puntos colineales en el borde, cambiar `<= 0` por `< 0` en las condiciones de desapilado.

```cpp
vector<Point> convex_hull(vector<Point> pts) {
    int n = pts.size();
    if (n <= 2) return pts;
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() <= 2) return pts;

    vector<Point> hull;
    // Lower hull
    for (const Point &p : pts) {
        while (hull.size() >= 2 && cross_product(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    // Upper hull
    size_t lower_size = hull.size();
    for (int i = (int)pts.size() - 2; i >= 0; --i) {
        const Point &p = pts[i];
        while (hull.size() > lower_size && cross_product(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    hull.pop_back(); // Eliminar duplicado del nodo inicial
    return hull;
}
```
