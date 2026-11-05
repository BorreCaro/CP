# Problema F: Milky way

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Fácil (Div 2A / Prefix Sums de Inversiones Adyacentes)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución del Equipo: [F_Milky_Way.cpp](../../inputs/solutions/F_Milky_Way.cpp)

---

## 1. Insight Clave

💡 Un subarreglo `a[l..r]` es no decreciente (`a_l <= a_{l+1} <= ... <= a_r`) si y solo si la cantidad de caídas adyacentes `a_i < a_{i-1}` para `i in [l + 1, r]` es exactamente `0`. Con un arreglo de sumas prefijas `diff[i]` que acumula los índices `k <= i` donde `a_k < a_{k-1}`, cada consulta `(l, r)` se responde en `O(1)` verificando `diff[r] == diff[l]`.

---

## 2. Localización del Error Latente en Vivo

En el código original escrito durante el concurso (`solslive/Milkyway.cpp`):

1. **Acceso Fuera de Rango (*Out-of-Bounds Write/Read*):**
   Se declaró `vi vt(n + 1);` pero `vll diff(n);` (de tamaño `n`, índices válidos `0 .. n - 1`), y enseguida el bucle ejecutó `for (int i = 1; i <= n; i++)` escribiendo en `diff[n]` y leyendo `diff[b]` con `b = n`. El envío sobrevivió en el juez por la capacidad extra de reserva o memoria contigua del heap sin disparar `SIGSEGV`, pero bajo sanitizadores (`-fsanitize=address`) constituye *Undefined Behavior* inmediato.
2. **Comparación Fantasma en `i = 1`:**
   El bucle comenzaba en `i = 1` evaluando `if (vt[1] < vt[0]) diff[1]++;` contra el centinela no leído `vt[0] = 0`. Esto no alteró las respuestas únicamente porque toda consulta satisface `1 <= a <= b <= n`, por lo que el desplazamiento inicial en `diff[1]` se cancelaba en ambos lados de `diff[a] != diff[b]`.
3. **Uso de `endl` en `10^5` consultas:**
   Imprimir con `endl` fuerza un `flush` del buffer de salida en cada una de las `q = 10^5` líneas. Debe usarse `'\n'`.

---

## 3. Patrón de Recurrencia / Sesgo Cognitivo

- **Asimetría de Indexación 1-Based (*1-Based Allocation Mismatch*):** Al mezclar vectores 1-indexados (`vt(n + 1)`) con vectores dimensionados por reflejo como `diff(n)`, el último elemento `diff[n]` queda fuera de los límites asignados. Regla de oro: si los bucles usan `1 <= i <= n`, **todos** los vectores deben dimensionarse con `n + 1`.

---

## 4. Lógica Correcta & Código Limpio

- **Complejidad Temporal:** `O(n + q)`.
- **Complejidad Espacial:** `O(n)`.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> diff(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        diff[i] = diff[i - 1] + (a[i] < a[i - 1] ? 1 : 0);
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << (diff[l] == diff[r] ? "YES\n" : "NO\n");
    }

    return 0;
}
```
