# Problema J: Shopping

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Media (Div 2B / Greedy Bitwise + Acarreo Binario)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución del Equipo: [J_Shopping.cpp](../../inputs/solutions/J_Shopping.cpp)

---

## 1. Insight Clave

💡 El `i`-ésimo bit (`2^i`) puede encenderse en la suma de algún subconjunto de `A` si y solo si la suma de las partes bajas de todos los números truncados a los primeros `i + 1` bits alcanza al menos `2^i`, es decir:
`sum_{j = 1}^n (a_j mod 2^(i + 1)) >= 2^i`.
Esta condición equivale exactamente a mantener un acumulador de acarreo `carry` bit a bit desde `i = 0` hasta `61`: en el paso `i`, se suma el `i`-ésimo bit de todos los `a_j` a `carry`; el bit `i` del resultado es `1` si y solo si `carry > 0`, y luego `carry /= 2`.

---

## 2. Análisis de la Solución en Vivo y Demostración

La solución enviada en vivo (`Shopping.cpp`) implementó este criterio directamente en `O(60 * n)`:
- **¿Por qué siempre existe un subconjunto con el bit `i` encendido cuando `carry > 0`?**
  Sea `b_j = a_j mod 2^(i + 1) < 2^(i + 1)`. Notemos que `carry` en la etapa `i` vale exactamente `floor((sum_{j=1}^n b_j) / 2^i)`.
  1. Si algún elemento individual tiene `b_j >= 2^i`, el subconjunto unitario `{a_j}` ya tiene encendido el bit `i`.
  2. Si todos los elementos tienen `b_j < 2^i` pero `sum b_j >= 2^i`, entonces al partir de `0` e ir sumando los valores `b_j` uno por uno, como cada salto es estrictamente menor que la longitud `2^i` del intervalo `[2^i, 2^(i + 1) - 1]`, es imposible saltar por encima del intervalo sin caer dentro de él. Por tanto, alguna suma prefija cae en `[2^i, 2^(i + 1) - 1]` y tiene su `i`-ésimo bit igual a `1`.
- **Detalle de cota superior de bits:** Como `sum a_i <= 10^18 < 2^60 = 1.1529 * 10^18`, `60` bits (`0..59`) bastaron exactamente en el concurso (usar `62` bits ofrece margen adicional de seguridad).

---

## 3. Patrón de Recurrencia / Sesgo Cognitivo

- **Trampa de Mochila Exponencial (*Subset Sum DP Trap*):** Al leer *"bitwise OR of all subset sums"*, el primer impulso suele ser plantear un `bitset` de mochila de tamaño `sum(a_i)`, lo cual es inviable para `10^18`. La clave es que no se pide el conjunto de todas las sumas posibles, sino **únicamente si cada bit `i` individual puede ser `1`**, desacoplando los bits mediante el invariante de salto acotado `b_j < 2^i`.

---

## 4. Lógica Correcta & Código Limpio

- **Complejidad Temporal:** `O(62 * n)`.
- **Complejidad Espacial:** `O(n)` (o `O(1)` acumulando conteos de bits al leer).

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<unsigned long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    unsigned long long ans = 0;
    unsigned long long carry = 0;

    for (int bit = 0; bit < 62; ++bit) {
        for (int j = 0; j < n; ++j) {
            carry += (a[j] >> bit) & 1ULL;
        }
        if (carry > 0) {
            ans |= (1ULL << bit);
        }
        carry >>= 1;
    }

    cout << ans << "\n";
    return 0;
}
```
