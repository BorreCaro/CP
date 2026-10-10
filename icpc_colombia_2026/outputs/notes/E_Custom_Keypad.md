# Problema E: Custom Keypad

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Edwin Niño
- **Dificultad Estimada:** Media (Div 2C / Div 1A)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [E_Custom_Keypad.cpp](../../inputs/solutions/E_Custom_Keypad.cpp)

---

## 1. Deconstrucción del Enunciado

Un fabricante de hardware diseña teclados numéricos para teléfonos móviles con `B` botones dedicados (`1 <= B <= 26`).
Las 26 letras del alfabeto latino ('a' a 'z') deben particionarse en `B` bloques alfabéticos disjuntos y consecutivos:
- Cada botón contiene al menos una letra.
- Las letras asignadas al botón `i` deben preceder alfabéticamente a las letras asignadas al botón `i + 1`.
- Para escribir una letra asignada en la posición `k` (1-indexada) dentro de su botón, el usuario debe presionarlo `k` veces.
- Los espacios no se cuentan en el costo (tienen botón separado).

Dado un texto de prueba de longitud hasta `10^5`, se debe encontrar la partición de las 26 letras en `B` botones que minimice el total acumulado de pulsaciones.
**Regla de Desempate Estricta:** Si existen múltiples particiones con el mismo costo mínimo, se debe elegir aquella que sitúe los separadores (`|`) lo más a la derecha posible (priorizando el separador más a la derecha; si persiste el empate, el segundo más a la derecha, y así sucesivamente).

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **Partición en bloques contiguos de un alfabeto de 26 letras:** El número de elementos a particionar es fijo e ínfimo: `N = 26` letras y `B <= 26` botones.
- **Costo aditivo separable:** El costo de asignar el rango de letras de `l` a `r` a un botón es puramente una función de las frecuencias de las letras en dicho intervalo:
  `cost(l, r) = sum_{k=0}^{r - l} (k + 1) * freq[l + k]`
- **Estructura Óptima de Subproblemas:** Clásica **Programación Dinámica de Partición en Intervalos** (*Partition DP*) de `j` bloques sobre un prefijo de longitud `p`.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Precomputación de Costos de Bloque
Primero, contamos las frecuencias `f[c]` de cada letra `'a' <= c <= 'z'` en el texto de entrada.
Para cada par de índices `0 <= l <= r < 26`, el costo de agrupar las letras desde `l` hasta `r` en un único botón es:
`cost[l][r] = sum_{i=l}^r f[i] * (i - l + 1)`
Esta tabla de tamaño `26 x 26` se calcula en `O(26^2)` operaciones.

### Estado y Transición de DP
Definimos:
`dp[j][p]`: el costo mínimo de particionar las primeras `p` letras (`0 <= p <= 26`) utilizando exactamente `j` botones (`1 <= j <= B`).

- **Caso Base:**
  `dp[0][0] = 0`, y `dp[j][p] = INF` para todos los demás estados.
- **Transición:**
  Para asignar `p` letras en `j` botones, el último botón contendrá las letras desde el índice `s` hasta `p - 1` (donde `j - 1 <= s < p`):
  `dp[j][p] = min_{s = j - 1}^{p - 1} (dp[j - 1][s] + cost[s][p - 1])`

### Reconstrucción con Prioridad de Desempate a la Derecha
La regla del enunciado exige:
*"maximize the position of the rightmost separator; if still tied, the second rightmost, and so on."*

Para implementar esto elegantemente:
Reconstruimos hacia atrás desde `j = B` hasta `j = 2`:
- El prefijo actual abarca `p` letras (inicialmente `p = 26`).
- Buscamos el punto de corte `s` en orden **decreciente**, desde `s = p - 1` hacia abajo hasta `s = j - 1`.
- El **primer** `s` que cumpla la igualdad de costo óptimo:
  `dp[j - 1][s] + cost[s][p - 1] == dp[j][p]`
  es necesariamente el separador más a la derecha posible. Guardamos `s`, actualizamos `p = s` y continuamos con `j - 1`.

- **Complejidad Temporal:** `O(|text| + B * 26^2)`. Con `|text| <= 10^5` y `26^3 ~ 17576`, el cálculo es instantáneo (`< 0.01 s`).
- **Complejidad Espacial:** `O(B * 26)` para la tabla de DP.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <set>
#include <limits>

using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max() / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        int B = stoi(line);
        if (B == 0) break;

        string text;
        getline(cin, text);

        // Conteo de frecuencias en el texto de muestra
        array<ll, 26> f{};
        for (char c : text) {
            if (c >= 'a' && c <= 'z') {
                f[c - 'a']++;
            }
        }

        // cost[l][r]: costo de agrupar letras l..r en un solo botón
        array<array<ll, 26>, 26> cost{};
        for (int l = 0; l < 26; l++) {
            ll s = 0;
            for (int r = l; r < 26; r++) {
                s += f[r] * (r - l + 1);
                cost[l][r] = s;
            }
        }

        // dp[j][p] = costo mínimo para las p primeras letras usando j botones
        vector<vector<ll>> dp(B + 1, vector<ll>(27, INF));
        dp[0][0] = 0;

        for (int j = 1; j <= B; j++) {
            for (int p = j; p <= 26; p++) {
                for (int s = j - 1; s < p; s++) {
                    if (dp[j - 1][s] < INF) {
                        dp[j][p] = min(dp[j][p], dp[j - 1][s] + cost[s][p - 1]);
                    }
                }
            }
        }

        // Reconstrucción de derecha a izquierda maximizando s (separadores más a la derecha)
        set<int> sep;
        int p = 26;
        for (int j = B; j >= 2; j--) {
            for (int s = p - 1; s >= j - 1; s--) {
                if (dp[j - 1][s] < INF && dp[j - 1][s] + cost[s][p - 1] == dp[j][p]) {
                    sep.insert(s);
                    p = s;
                    break; // Tomamos el s más grande posible
                }
            }
        }

        // Generar salida formateada con barras verticales '|'
        string out;
        for (int i = 0; i < 26; i++) {
            if (sep.count(i)) out += '|';
            out += static_cast<char>('a' + i);
        }
        cout << out << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Inversión de la Regla de Desempate Lexicográfica:**
   Iterar `s` de menor a mayor en la reconstrucción coloca los separadores lo más a la izquierda posible (*leftmost separators*), violando directamente la especificación del juez. La iteración debe ser estrictamente descendente desde `s = p - 1`.
2. **Lectura Incompleta de Líneas con Espacios:**
   Usar `cin >> text` en lugar de `getline(cin, text)` trunca la cadena en el primer espacio en blanco, perdiendo gran parte del texto de entrada.
3. **Manejo de Retornos de Carro `\r\n` (CRLF):**
   En archivos de prueba generados en Windows o plataformas híbridas, `getline()` puede dejar un carácter `\r` al final de la línea. Comprobar `line.back() == '\r'` y eliminarlo evita errores al parsear el entero `B`.
