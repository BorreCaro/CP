# Problema L: Vampires

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Fácil (Div 3B / Div 2A - Implementación y Validación de Cadenas)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución del Equipo: [L_Vampires.cpp](../../inputs/solutions/L_Vampires.cpp)

---

## 1. Insight Clave

💡 Un entero `n` de `2k` dígitos es un número vampiro con colmillos `a` y `b` si y solo si se cumplen simultáneamente las 4 condiciones: (1) `len(a) == len(b) == k` y `len(n) == 2k`, (2) `a * b == n`, (3) `!(a % 10 == 0 && b % 10 == 0)`, y (4) `sort(str(n)) == sort(str(a) + str(b))`.

---

## 2. Localización del Detalle Latente en Vivo

En la solución escrita en vivo (`solslive/Vampires.cpp`):
- En la línea 42 se escribió la condición de longitud como `if (x / 2 == y && y == z)` usando **división entera**.
- Si `x` fuera impar (por ejemplo, `x = 5, y = 2, z = 2`), en C++ `5 / 2 == 2` evalúa a `true` aunque `x != 2 * y`.
- Afortunadamente, líneas más abajo el código concatenó `string s = a + b;` (de longitud `y + z = 4`) y comparó `if (n != s) return false;` contra `n` (de longitud `5`), lo cual atrapó cualquier discrepancia de paridad en `x`.
- En la versión limpia se reemplaza `x / 2 == y` por `x == 2 * y` y se elimina el `unordered_map<char, int> freq;` no utilizado.

---

## 3. Patrón de Recurrencia / Sesgo Cognitivo

- **Trampa de Truncamiento en División Entera (*Integer Division Truncation*):** Escribir `x / 2 == y` para verificar `x = 2y` ignora el bit de paridad de `x`. Siempre debe verificarse multiplicando (`x == 2 * y`).

---

## 4. Lógica Correcta & Código Limpio

- **Complejidad Temporal:** `O(t * d log d)` donde `d <= 8` es el número de dígitos.
- **Complejidad Espacial:** `O(d)`.

```cpp
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool solve() {
    string n, a, b;
    cin >> n >> a >> b;

    if (n.length() != 2 * a.length() || a.length() != b.length()) {
        return false;
    }

    long long vn = stoll(n), va = stoll(a), vb = stoll(b);
    if (va * vb != vn) return false;
    if (va % 10 == 0 && vb % 10 == 0) return false;

    string s = a + b;
    sort(s.begin(), s.end());
    sort(n.begin(), n.end());
    return n == s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        cout << (solve() ? "YES\n" : "NO\n");
    }
    return 0;
}
```
